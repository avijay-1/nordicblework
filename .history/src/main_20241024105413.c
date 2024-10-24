#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/adc.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/hci.h>
#include <zephyr/bluetooth/gatt.h>
#include <zephyr/bluetooth/services/hrs.h>

/* Constants for heart rate calculation */
#define SAMPLE_RATE 1000  // 1000 Hz sampling rate (1ms per sample)
#define PEAK_THRESHOLD 2000  // Adjust this based on your sensor's signal
#define MIN_PEAK_DISTANCE 600  // Minimum time between peaks (600 ms, ~100 BPM max)

static const struct adc_dt_spec adc_channel = ADC_DT_SPEC_GET(DT_PATH(zephyr_user));

LOG_MODULE_REGISTER(HeartRateMonitor, LOG_LEVEL_DBG);

/* Bluetooth Advertising Data */
static const struct bt_data ad[] = {
    BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR)),
    BT_DATA_BYTES(BT_DATA_UUID16_ALL, BT_UUID_16_ENCODE(BT_UUID_HRS_VAL))
};

/* Callback for Bluetooth connection */
static void connected(struct bt_conn *conn, uint8_t err) {
    if (err) {
        LOG_ERR("Connection failed (err %u)", err);
    } else {
        LOG_INF("Connected");
    }
}

/* Callback for Bluetooth disconnection */
static void disconnected(struct bt_conn *conn, uint8_t reason) {
    LOG_INF("Disconnected (reason %u)", reason);
}

BT_CONN_CB_DEFINE(conn_callbacks) = {
    .connected = connected,
    .disconnected = disconnected,
};

/* Function to initialize BLE */
static void bt_ready(void) {
    int err;

    err = bt_le_adv_start(BT_LE_ADV_CONN_NAME, ad, ARRAY_SIZE(ad), NULL, 0);
    if (err) {
        LOG_ERR("Advertising failed to start (err %d)", err);
    } else {
        LOG_INF("Advertising successfully started");
    }
}

int main(void) {
    int err;
    int16_t adc_value;
    uint32_t last_peak_time = 0;  // Timestamp of the last detected peak
    uint32_t current_time;
    uint32_t bpm = 0;  // To store calculated BPM

    struct adc_sequence sequence = {
        .buffer = &adc_value,
        .buffer_size = sizeof(adc_value),
    };

    /* Initialize Bluetooth */
    err = bt_enable(NULL);
    if (err) {
        LOG_ERR("Bluetooth init failed (err %d)", err);
        return 0;
    }
    bt_ready();

    if (!adc_is_ready_dt(&adc_channel)) {
        LOG_ERR("ADC device not ready.");
        return 0;
    }

    err = adc_channel_setup_dt(&adc_channel);
    if (err < 0) {
        LOG_ERR("Could not set up ADC channel (%d)", err);
        return 0;
    }

    err = adc_sequence_init_dt(&adc_channel, &sequence);
    if (err < 0) {
        LOG_ERR("Could not initialize ADC sequence.");
        return 0;
    }

    /* Heart rate measurement loop */
    while (1) {
        err = adc_read(adc_channel.dev, &sequence);
        if (err < 0) {
            LOG_ERR("ADC read error (%d)", err);
            continue;
        }

        current_time = k_uptime_get_32();  // Get current time in ms

        // Check if the ADC value exceeds the threshold, indicating a peak
        if (adc_value > PEAK_THRESHOLD) {
            if (current_time - last_peak_time > MIN_PEAK_DISTANCE) {
                // A peak is detected, calculate BPM
                uint32_t time_diff = current_time - last_peak_time;  // Time between two peaks
                bpm = (60000 / time_diff);  // Calculate BPM

                LOG_INF("Heartbeat detected! BPM: %d", bpm);

                // Notify the BLE heart rate service with the new value
                bt_hrs_notify(bpm);

                last_peak_time = current_time;  // Update last peak time
            }
        }

        k_sleep(K_MSEC(1000 / SAMPLE_RATE));  // Sleep to achieve the desired sampling rate
    }

    return 0;
}

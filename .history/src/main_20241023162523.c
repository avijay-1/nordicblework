/* main.c - Application main entry point */

#include <zephyr/types.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys/byteorder.h>
#include <zephyr/drivers/adc.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/conn.h>
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/bluetooth/gatt.h>
#include <zephyr/bluetooth/services/hrs.h>

/* Logging module for debugging */
LOG_MODULE_REGISTER(heart_rate, LOG_LEVEL_DBG);

/* Constants for heart rate calculation */
#define SAMPLE_RATE 1000  // 1000 Hz sampling rate (1ms per sample)
#define PEAK_THRESHOLD 2000  // Adjust this based on your sensor's signal
#define MIN_PEAK_DISTANCE 600  // Minimum time between peaks (600 ms, ~100 BPM max)

/* ADC configuration */
static const struct adc_dt_spec adc_channel = ADC_DT_SPEC_GET_BY_IDX(DT_NODELABEL(adc), 0);



static int16_t adc_value;  // Variable to store ADC value
static uint32_t last_peak_time = 0;  // Timestamp of the last detected peak
static uint32_t bpm = 0;  // To store calculated BPM

static void hrs_notify(void);

/* Bluetooth connection callbacks */
static void connected(struct bt_conn *conn, uint8_t err)
{
    if (err) {
        LOG_ERR("Connection failed (err 0x%02x)", err);
    } else {
        LOG_INF("Connected");
    }
}

static void disconnected(struct bt_conn *conn, uint8_t reason)
{
    LOG_INF("Disconnected (reason 0x%02x)", reason);
}

BT_CONN_CB_DEFINE(conn_callbacks) = {
    .connected = connected,
    .disconnected = disconnected,
};

/* Bluetooth initialization */
static void bt_ready(void)
{
    int err;

    LOG_INF("Bluetooth initialized");

    err = bt_le_adv_start(BT_LE_ADV_CONN_NAME, NULL, 0, NULL, 0);
    if (err) {
        LOG_ERR("Advertising failed to start (err %d)", err);
        return;
    }

    LOG_INF("Advertising successfully started");
}

/* ADC reading function */
static int read_heart_rate_sensor()
{
    struct adc_sequence sequence = {
        .buffer = &adc_value,
        .buffer_size = sizeof(adc_value),
    };

    int err = adc_read(adc_channel.dev, &sequence);
    if (err < 0) {
        LOG_ERR("ADC read error (%d)", err);
        return 0;
    }

    LOG_INF("ADC raw value: %d", adc_value);  // Log raw ADC value for debugging

    uint32_t current_time = k_uptime_get_32();  // Get current time in ms

    // Check if the ADC value exceeds the threshold, indicating a peak
    if (adc_value > PEAK_THRESHOLD) {
        if (current_time - last_peak_time > MIN_PEAK_DISTANCE) {
            // A peak is detected, calculate BPM
            uint32_t time_diff = current_time - last_peak_time;  // Time between two peaks
            bpm = (60000 / time_diff);  // Calculate BPM

            LOG_INF("Heartbeat detected! BPM: %d", bpm);

            last_peak_time = current_time;  // Update last peak time
        }
    }

    return bpm;  // Return the calculated BPM
}

/* Function to send heart rate over BLE */
static void hrs_notify(void)
{
    int heart_rate = read_heart_rate_sensor();  // Read the heart rate from the sensor

    if (heart_rate > 0) {
        LOG_INF("Sending Heart Rate over BLE: %d BPM", heart_rate);
        bt_hrs_notify(heart_rate);  // Send the heart rate via BLE
    }
}

/* Main function */
int main(void)
{
    int err;

    /* Bluetooth initialization */
    err = bt_enable(NULL);
    if (err) {
        LOG_ERR("Bluetooth init failed (err %d)", err);
        return 0;
    }

    bt_ready();

    /* ADC setup */
    if (!adc_is_ready_dt(&adc_channel)) {
        LOG_ERR("ADC device not ready.");
        return 0;
    }

    err = adc_channel_setup_dt(&adc_channel);
    if (err < 0) {
        LOG_ERR("Could not set up ADC channel (%d)", err);
        return 0;
    }

    /* Infinite loop to read heart rate and notify over BLE */
    while (1) {
        k_sleep(K_SECONDS(1));

        /* Notify the heart rate over BLE */
        hrs_notify();
    }

    return 0;
}

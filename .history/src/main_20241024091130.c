#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/adc.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/conn.h>
#include <zephyr/bluetooth/gatt.h>
#include <zephyr/bluetooth/services/bas.h>
#include <zephyr/bluetooth/services/hrs.h>

LOG_MODULE_REGISTER(HeartRateMonitor, LOG_LEVEL_DBG);

/* Constants for heart rate calculation */
#define SAMPLE_RATE 1000  // 1000 Hz sampling rate (1ms per sample)
#define PEAK_THRESHOLD 2000  // Adjust this based on your sensor's signal
#define MIN_PEAK_DISTANCE 600  // Minimum time between peaks (600 ms, ~100 BPM max)

static const struct adc_dt_spec adc_channel = ADC_DT_SPEC_GET(DT_PATH(zephyr_user));

static uint32_t last_peak_time = 0;  // Timestamp of the last detected peak

// Bluetooth advertising data
static const struct bt_data ad[] = {
	BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR)),
	BT_DATA_BYTES(BT_DATA_UUID16_ALL,
		      BT_UUID_16_ENCODE(BT_UUID_HRS_VAL),
		      BT_UUID_16_ENCODE(BT_UUID_BAS_VAL))
};

// Callback for successful connection
static void connected(struct bt_conn *conn, uint8_t err)
{
	if (err) {
		printk("Connection failed (err 0x%02x)\n", err);
	} else {
		printk("Connected\n");
	}
}

// Callback for disconnection
static void disconnected(struct bt_conn *conn, uint8_t reason)
{
	printk("Disconnected (reason 0x%02x)\n", reason);
}

// Connection callbacks structure
BT_CONN_CB_DEFINE(conn_callbacks) = {
	.connected = connected,
	.disconnected = disconnected,
};

// Initialize Bluetooth
static void bt_ready(void)
{
	int err;

	printk("Bluetooth initialized\n");

	err = bt_le_adv_start(BT_LE_ADV_CONN_NAME, ad, ARRAY_SIZE(ad), NULL, 0);
	if (err) {
		printk("Advertising failed to start (err %d)\n", err);
		return;
	}

	printk("Advertising successfully started\n");
}

// Send battery level notification
static void bas_notify(void)
{
	uint8_t battery_level = bt_bas_get_battery_level();

	battery_level--;

	if (!battery_level) {
		battery_level = 100U;
	}

	bt_bas_set_battery_level(battery_level);
}

// Send heart rate notification using ADC readings
static void hrs_notify(void)
{
	int err;
	int16_t adc_value;
	uint32_t current_time;
	uint8_t bpm = 0;

	struct adc_sequence sequence = {
		.buffer = &adc_value,
		.buffer_size = sizeof(adc_value),
	};

	// Read ADC value from the heart rate sensor
	err = adc_read(adc_channel.dev, &sequence);
	if (err < 0) {
		LOG_ERR("ADC read error (%d)", err);
		return;
	}

	// Check if the ADC value exceeds the threshold, indicating a peak
	current_time = k_uptime_get_32();  // Get current time in ms
	if (adc_value > PEAK_THRESHOLD && (current_time - last_peak_time) > MIN_PEAK_DISTANCE) {
		// A peak is detected, calculate BPM
		uint32_t time_diff = current_time - last_peak_time;  // Time between two peaks
		bpm = (60000 / time_diff);  // Calculate BPM

		LOG_INF("Heartbeat detected! BPM: %d", bpm);

		// Send the real BPM value via Bluetooth
		bt_hrs_notify(bpm);

		last_peak_time = current_time;  // Update last peak time
	}
}

int main(void)
{
	int err;

	// Initialize Bluetooth
	err = bt_enable(NULL);
	if (err) {
		printk("Bluetooth init failed (err %d)\n", err);
		return 0;
	}

	bt_ready();

	// Initialize ADC
	if (!adc_is_ready_dt(&adc_channel)) {
		LOG_ERR("ADC device not ready.");
		return 0;
	}

	err = adc_channel_setup_dt(&adc_channel);
	if (err < 0) {
		LOG_ERR("Could not set up ADC channel (%d)", err);
		return 0;
	}

	bt_conn_auth_cb_register(NULL);

	// Notification loop
	while (1) {
		k_sleep(K_SECONDS(1));  // Sleep for 1 second

		// Send heart rate measurements
		hrs_notify();

		// Simulate battery level notification
		bas_notify();
	}

	return 0;
}

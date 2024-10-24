#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/adc.h>

/* Constants for heart rate calculation */
#define SAMPLE_RATE 100  // Lowered sampling rate to 100 Hz for smoother readings
#define PEAK_THRESHOLD 2000  // Adjust this based on your sensor's signal
#define MIN_PEAK_DISTANCE 600  // Minimum time between peaks (600 ms, ~100 BPM max)
#define NO_SIGNAL_TIMEOUT 5000  // 5 seconds to assume no signal if no peaks detected

static const struct adc_dt_spec adc_channel = ADC_DT_SPEC_GET(DT_PATH(zephyr_user));

LOG_MODULE_REGISTER(HeartRateMonitor, LOG_LEVEL_DBG);

int main(void) {
    int err;
    int16_t adc_value;
    uint32_t last_peak_time = 0;  // Timestamp of the last detected peak
    uint32_t current_time;
    uint32_t bpm = 0;  // To store calculated BPM
    uint32_t last_valid_heartbeat_time = 0;  // Tracks the time of last valid heartbeat

    struct adc_sequence sequence = {
        .buffer = &adc_value,
        .buffer_size = sizeof(adc_value),
    };

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

    while (1) {
        err = adc_read(adc_channel.dev, &sequence);
        if (err < 0) {
            LOG_ERR("ADC read error (%d)", err);
            continue;
        }

        current_time = k_uptime_get_32();  // Get current time in ms

        // Check if the ADC value exceeds the threshold, indicating a peak (heartbeat)
        if (adc_value > PEAK_THRESHOLD) {
            if (current_time - last_peak_time > MIN_PEAK_DISTANCE) {
                // Valid heartbeat detected
                uint32_t time_diff = current_time - last_peak_time;  // Time between two peaks
                bpm = (60000 / time_diff);  // Calculate BPM

                LOG_INF("Heartbeat detected! BPM: %d", bpm);

                last_peak_time = current_time;  // Update last peak time
                last_valid_heartbeat_time = current_time;  // Update last valid heartbeat time
            } else {
                LOG_DBG("Peak detected but too close to the last peak.");
            }
        }

        // Check if no heartbeats have been detected for a certain timeout period (no signal)
        if (current_time - last_valid_heartbeat_time > NO_SIGNAL_TIMEOUT) {
            LOG_INF("No heartbeat detected for %d ms. Assuming no signal.", NO_SIGNAL_TIMEOUT);
            bpm = 0;  // Reset BPM to indicate no heartbeats detected
        }

        // Log ADC value (optional: you can remove this if needed)
        LOG_DBG("ADC Value: %d", adc_value);

        k_sleep(K_MSEC(1000 / SAMPLE_RATE));  // Adjusted sleep for smoother operation
    }

    return 0;
}

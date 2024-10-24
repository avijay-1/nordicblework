#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/adc.h>

/* Constants for heart rate calculation */
#define SAMPLE_RATE 1000  // 1000 Hz sampling rate
#define PEAK_THRESHOLD 2000  // Threshold for detecting a peak
#define MIN_PEAK_DISTANCE 600  // Minimum time between peaks (600 ms, ~100 BPM max)
#define NO_HEARTBEAT_BPM 99  // Value to represent no valid heartbeat

static const struct adc_dt_spec adc_channel = ADC_DT_SPEC_GET(DT_PATH(zephyr_user));

LOG_MODULE_REGISTER(HeartRateMonitor, LOG_LEVEL_DBG);

int main(void) {
    int err;
    int16_t adc_value;
    uint32_t last_peak_time = 0;  // Time of last detected peak
    uint32_t current_time;
    uint32_t bpm = NO_HEARTBEAT_BPM;  // Initially set to no heartbeat

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
                // A peak is detected, calculate BPM
                uint32_t time_diff = current_time - last_peak_time;
                bpm = (60000 / time_diff);  // Calculate BPM
                
                // Log valid heartbeat
                LOG_INF("Heartbeat detected! BPM: %d", bpm);

                last_peak_time = current_time;  // Update last peak time
            }
        } else {
            // Log only once for no valid heartbeat
            if (bpm != NO_HEARTBEAT_BPM) {
                bpm = NO_HEARTBEAT_BPM;  // Set BPM to 99 (or another placeholder)
                LOG_INF("No valid heartbeat detected. BPM: %d", bpm);
            }
        }

        k_sleep(K_MSEC(500));  // Sleep for 500ms to slow down the loop
    }

    return 0;
}
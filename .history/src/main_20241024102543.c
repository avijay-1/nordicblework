#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/adc.h>

/* Constants for heart rate calculation */
#define SAMPLE_RATE 200  // Reduced sampling rate to 200 Hz (5ms per sample)
#define PEAK_THRESHOLD 2500  // Adjust this based on your sensor's signal to filter out noise
#define MIN_PEAK_DISTANCE 800  // Increased to 800 ms (~75 BPM max)

#define AVG_WINDOW_SIZE 5  // Size of the moving average window

static const struct adc_dt_spec adc_channel = ADC_DT_SPEC_GET(DT_PATH(zephyr_user));

LOG_MODULE_REGISTER(HeartRateMonitor, LOG_LEVEL_DBG);

int main(void) {
    int err;
    int16_t adc_value;
    int16_t adc_values[AVG_WINDOW_SIZE] = {0};  // Buffer for moving average
    int index = 0;  // Index for moving average buffer
    uint32_t last_peak_time = 0;  // Timestamp of the last detected peak
    uint32_t current_time;
    uint32_t bpm = 0;  // To store calculated BPM

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

        // Insert the latest ADC value into the moving average buffer
        adc_values[index] = adc_value;
        index = (index + 1) % AVG_WINDOW_SIZE;

        // Calculate the moving average of the ADC values
        int32_t avg_adc_value = 0;
        for (int i = 0; i < AVG_WINDOW_SIZE; i++) {
            avg_adc_value += adc_values[i];
        }
        avg_adc_value /= AVG_WINDOW_SIZE;

        LOG_DBG("Filtered ADC value: %d", avg_adc_value);

        current_time = k_uptime_get_32();  // Get current time in ms

        // Check if the filtered ADC value exceeds the threshold, indicating a peak
        if (avg_adc_value > PEAK_THRESHOLD) {
            if (current_time - last_peak_time > MIN_PEAK_DISTANCE) {
                // A peak is detected, calculate BPM
                uint32_t time_diff = current_time - last_peak_time;  // Time between two peaks
                bpm = (60000 / time_diff);  // Calculate BPM

                LOG_INF("Heartbeat detected! BPM: %d", bpm);

                last_peak_time = current_time;  // Update last peak time
            } else {
                LOG_DBG("Peak detected but too close to the last peak.");
            }
        } else {
            LOG_DBG("No peak detected. ADC value: %d", avg_adc_value);
        }

        k_sleep(K_MSEC(1000 / SAMPLE_RATE));  // Sleep to achieve the desired sampling rate
    }

    return 0;
}

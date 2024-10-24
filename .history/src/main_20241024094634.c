#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/adc.h>

/* Constants for heart rate calculation */
#define SAMPLE_RATE 1000  // 1000 Hz sampling rate (1ms per sample)
#define PEAK_THRESHOLD 2000  // Adjust this based on your sensor's signal
#define MIN_PEAK_DISTANCE 600  // Minimum time between peaks (600 ms, ~100 BPM max)

static const struct adc_dt_spec adc_channel = ADC_DT_SPEC_GET(DT_PATH(zephyr_user));

LOG_MODULE_REGISTER(HeartRateMonitor, LOG_LEVEL_DBG);

int main(void) {
    int err;
    int16_t adc_value;
    uint32_t last_peak_time = 0;  // Timestamp of the last detected peak
    uint32_t current_time;
    uint32_t bpm = 0;  // To store calculated BPM

    /* Define the ADC sequence structure */
    struct adc_sequence sequence = {
        .channels    = BIT(adc_channel.channel_id),
        .buffer      = &adc_value,
        .buffer_size = sizeof(adc_value),
        .resolution  = 12,  // Resolution as specified in the overlay
        .oversampling = 4,  // Optional: Adjust oversampling as needed
    };

    /* Ensure the ADC device is ready */
    if (!device_is_ready(adc_channel.dev)) {
        LOG_ERR("ADC device is not ready.");
        return 0;
    }

    /* Set up the ADC channel */
    err = adc_channel_setup_dt(&adc_channel);
    if (err < 0) {
        LOG_ERR("Could not set up ADC channel (error code: %d)", err);
        return 0;
    } else {
        LOG_INF("ADC channel setup complete.");
    }

    /* Initialize the ADC sequence */
    err = adc_sequence_init_dt(&adc_channel, &sequence);
    if (err < 0) {
        LOG_ERR("Could not initialize ADC sequence (error code: %d)", err);
        return 0;
    } else {
        LOG_INF("ADC sequence initialized successfully.");
    }

    /* Main loop to continuously read from ADC */
    while (1) {
        /* Perform an ADC read */
        err = adc_read(adc_channel.dev, &sequence);
        if (err < 0) {
            LOG_ERR("ADC read error (%d)", err);
            continue;  // Retry after error
        } else {
            LOG_INF("ADC read successful. ADC value: %d", adc_value);
        }

        /* Get the current time */
        current_time = k_uptime_get_32();  // Get current time in ms

        /* Check if the ADC value exceeds the threshold, indicating a peak */
        if (adc_value > PEAK_THRESHOLD) {
            if (current_time - last_peak_time > MIN_PEAK_DISTANCE) {
                /* A peak is detected, calculate BPM */
                uint32_t time_diff = current_time - last_peak_time;  // Time between two peaks
                bpm = (60000 / time_diff);  // Calculate BPM

                LOG_INF("Heartbeat detected! BPM: %d", bpm);

                /* Update last peak time */
                last_peak_time = current_time;
            }
        }

        /* Sleep to maintain the sampling rate */
        k_sleep(K_MSEC(1000 / SAMPLE_RATE));  // Sleep to achieve the desired sampling rate
    }

    return 0;
}

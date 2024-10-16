#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/adc.h>

/* Constants for heart rate calculation */
#define SAMPLE_RATE 1000  // Sample every 1ms (1000 Hz)
#define BUFFER_SIZE 100  // Number of ADC readings to buffer
#define PEAK_THRESHOLD 2000  // Adjust based on the sensor's signal characteristics
#define MIN_PEAK_DISTANCE 600  // Minimum time (ms) between peaks (100 BPM limit)

static const struct adc_dt_spec adc_channel = ADC_DT_SPEC_GET(DT_PATH(zephyr_user));
LOG_MODULE_REGISTER(HeartRateMonitor, LOG_LEVEL_DBG);

static int16_t adc_buffer[BUFFER_SIZE];
static uint32_t peak_times[BUFFER_SIZE];  // Store time of detected peaks
static uint32_t last_peak_time = 0;  // Store last peak time
static uint8_t peak_count = 0;

int main(void)
{
    int err;
    uint32_t count = 0;
    int16_t adc_value;
    uint32_t current_time;
    uint32_t bpm = 0;
    
    struct adc_sequence sequence = {
        .buffer = &adc_value,
        .buffer_size = sizeof(adc_value),
    };

    if (!adc_is_ready_dt(&adc_channel)) {
        LOG_ERR("ADC controller device %s not ready", adc_channel.dev->name);
        return 0;
    }

    err = adc_channel_setup_dt(&adc_channel);
    if (err < 0) {
        LOG_ERR("Could not setup channel #%d (%d)", adc_channel.channel_id, err);
        return 0;
    }

    err = adc_sequence_init_dt(&adc_channel, &sequence);
    if (err < 0) {
        LOG_ERR("Could not initialize sequence");
        return 0;
    }

    while (1) {
        err = adc_read(adc_channel.dev, &sequence);
        if (err < 0) {
            LOG_ERR("Could not read ADC value (%d)", err);
            continue;
        }

        // Convert ADC raw value to mV (optional)
        int val_mv = (int)adc_value;
        adc_raw_to_millivolts_dt(&adc_channel, &val_mv);

        // Log raw ADC value (for debugging)
        LOG_INF("ADC Value: %d mV", val_mv);

        // Detect peaks in the pulse signal
        current_time = k_uptime_get_32();
        if (val_mv > PEAK_THRESHOLD) {  // If signal exceeds threshold
            if (current_time - last_peak_time > MIN_PEAK_DISTANCE) {
                // A peak is detected
                last_peak_time = current_time;
                peak_times[peak_count % BUFFER_SIZE] = current_time;
                peak_count++;

                if (peak_count > 1) {
                    // Calculate BPM
                    uint32_t time_diff = peak_times[(peak_count - 1) % BUFFER_SIZE] - peak_times[(peak_count - 2) % BUFFER_SIZE];
                    bpm = (60000 / time_diff);  // Convert time_diff (ms) to BPM
                }

                LOG_INF("Heartbeat detected! BPM: %d", bpm);
            }
        }

        k_sleep(K_MSEC(1000 / SAMPLE_RATE));  // Wait for the next sample (sampling rate = 1000 Hz)
    }

    return 0;
}

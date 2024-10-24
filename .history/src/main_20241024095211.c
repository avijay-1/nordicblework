#define SAMPLE_RATE 1000  // 1000 Hz sampling rate (1ms per sample)
#define PEAK_THRESHOLD 2400  // Adjusted based on your sensor's signal
#define MIN_PEAK_DISTANCE 600  // Minimum time between peaks (600 ms, ~100 BPM max)

while (1) {
    err = adc_read(adc_channel.dev, &sequence);
    if (err < 0) {
        LOG_ERR("ADC read error (%d)", err);
        continue;
    }
    
    LOG_INF("ADC read successful. ADC value: %d", adc_value);
    current_time = k_uptime_get_32();  // Get current time in ms

    // Check if the ADC value exceeds the threshold, indicating a peak
    if (adc_value > PEAK_THRESHOLD) {
        if (current_time - last_peak_time > MIN_PEAK_DISTANCE) {
            // A peak is detected, calculate BPM
            uint32_t time_diff = current_time - last_peak_time;  // Time between two peaks
            bpm = (60000 / time_diff);  // Calculate BPM

            LOG_INF("Heartbeat detected! BPM: %d", bpm);

            last_peak_time = current_time;  // Update last peak time
        } else {
            LOG_DBG("Peak detected but too close to last peak.");
        }
    } else {
        LOG_DBG("No peak detected. ADC value: %d", adc_value);
    }

    k_sleep(K_MSEC(1000 / SAMPLE_RATE));  // Sleep to achieve the desired sampling rate
}

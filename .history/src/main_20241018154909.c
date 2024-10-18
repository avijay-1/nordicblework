#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/device.h>
#include <zephyr/drivers/pwm.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/gatt.h>

LOG_MODULE_REGISTER(PWM_BLE_Control);

/* Define the PWM device and channels */
#define PWM_NODE DT_NODELABEL(pwm0)
#define PWM_CHANNEL_1 0 // Using channel 0 as configured in the overlay for P0.28
#define PWM_CHANNEL_2 1 // Using channel 1 as configured in the overlay for P0.29
#define PWM_FLAGS PWM_POLARITY_INVERTED // Use inverted polarity for active-low LED

static const struct device *pwm_dev;

/* BLE Write Handler */
static ssize_t simple_write_handler(struct bt_conn *conn,
                                    const struct bt_gatt_attr *attr,
                                    const void *buf, uint16_t len,
                                    uint16_t offset, uint8_t flags)
{
    LOG_INF("simple_write_handler invoked");

    if (len == 2) {
        uint8_t led_num = *((const uint8_t *)buf);
        uint8_t received_value = *((const uint8_t *)buf + 1);
        LOG_INF("Received LED number: %d, value: %d", led_num, received_value);

        uint32_t period = 1000U; // 1,000 us (1 ms)

        /* Scale the received value (0-255) to the PWM pulse width */
        uint32_t pulse_width = (received_value * period) / 255;

        int ret;
        if (led_num == 1) {
            ret = pwm_set(pwm_dev, PWM_CHANNEL_1, period, pulse_width, PWM_FLAGS);
            if (ret) {
                LOG_ERR("Error setting PWM for LED1 (P0.28): %d", ret);
            } else {
                LOG_INF("PWM updated for LED1 (P0.28): Pulse width set to %u (out of %u)", pulse_width, period);
            }
        } else if (led_num == 2) {
            ret = pwm_set(pwm_dev, PWM_CHANNEL_2, period, pulse_width, PWM_FLAGS);
            if (ret) {
                LOG_ERR("Error setting PWM for LED2 (P0.29): %d", ret);
            } else {
                LOG_INF("PWM updated for LED2 (P0.29): Pulse width set to %u (out of %u)", pulse_width, period);
            }
        } else {
            LOG_WRN("Invalid LED number: %d", led_num);
        }

    } else {
        LOG_WRN("Received unexpected length: %d", len);
    }

    return len;  // Return the number of bytes consumed
}

/* GATT Service and Characteristic Definition */
BT_GATT_SERVICE_DEFINE(pwm_svc,
    BT_GATT_PRIMARY_SERVICE(BT_UUID_DECLARE_128(
        BT_UUID_128_ENCODE(0x12345678, 0x1234, 0x5678, 0x1234, 0x56789abcdef0))),
    BT_GATT_CHARACTERISTIC(BT_UUID_DECLARE_128(
        BT_UUID_128_ENCODE(0x12345678, 0x1234, 0x5678, 0x1234, 0x56789abcde01)),
        BT_GATT_CHRC_WRITE | BT_GATT_CHRC_WRITE_WITHOUT_RESP,
        BT_GATT_PERM_WRITE,
        NULL, simple_write_handler, NULL),
);

void on_connected(struct bt_conn *conn, uint8_t err)
{
    if (err) {
        LOG_ERR("Failed to connect (err %d)", err);
        return;
    }
    LOG_INF("Connected to BLE device");
}

void on_disconnected(struct bt_conn *conn, uint8_t reason)
{
    LOG_INF("Disconnected from BLE device (reason %d)", reason);
}

static struct bt_conn_cb conn_callbacks = {
    .connected = on_connected,
    .disconnected = on_disconnected,
};

/* Advertising data */
static const struct bt_data ad[] = {
    BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR)),
    BT_DATA_BYTES(BT_DATA_UUID128_ALL,
        BT_UUID_128_ENCODE(0x12345678, 0x1234, 0x5678, 0x1234, 0x56789abcdef0)),
};

int main(void)
{
    int err;

    LOG_INF("Starting PWM BLE Control on LED1 (P0.28) and LED2 (P0.29)");

    /* Initialize PWM Device */
    pwm_dev = DEVICE_DT_GET(PWM_NODE);
    if (!device_is_ready(pwm_dev)) {
        LOG_ERR("PWM device not found");
        return -1;
    }
    LOG_INF("PWM device initialized");

    /* Initialize Bluetooth */
    err = bt_enable(NULL);
    if (err) {
        LOG_ERR("Bluetooth initialization failed (err %d)", err);
        return -1;
    }
    LOG_INF("Bluetooth initialized");

    /* Register Bluetooth connection callbacks */
    bt_conn_cb_register(&conn_callbacks);

    /* Start Bluetooth advertising */
    err = bt_le_adv_start(BT_LE_ADV_CONN_NAME, ad, ARRAY_SIZE(ad), NULL, 0);
    if (err) {
        LOG_ERR("Advertising failed to start (err %d)", err);
        return -1;
    }
    LOG_INF("Advertising started");

    LOG_INF("BLE service and characteristic initialized");

    /* Main loop */
    while (1) {
        k_sleep(K_FOREVER);  // Keep the program running
    }

    return 0;
}

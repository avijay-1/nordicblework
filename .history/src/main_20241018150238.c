#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/device.h>
#include <zephyr/drivers/pwm.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/gatt.h>

LOG_MODULE_REGISTER(PWM_BLE_Control);

/* Define the PWM device and channels */
#define PWM_NODE DT_NODELABEL(pwm0)

#define PWM0_CHANNEL 0  // PWM channel 0 for LED1
#define PWM1_CHANNEL 1  // PWM channel 1 for LED2

#define PWM_FLAGS PWM_POLARITY_INVERTED // Use inverted polarity for active-low LEDs

static const struct device *pwm_dev;

/* BLE Write Handlers */
static ssize_t write_led1(struct bt_conn *conn,
                          const struct bt_gatt_attr *attr,
                          const void *buf, uint16_t len,
                          uint16_t offset, uint8_t flags)
{
    LOG_INF("write_led1 invoked");

    if (len == 1) {
        uint8_t received_value = *((const uint8_t *)buf);
        LOG_INF("Received value for LED1: %d", received_value);

        uint32_t period = 1000U; // 1,000 us (1 ms)
        uint32_t pulse_width = (received_value * period) / 255;

        int ret = pwm_set(pwm_dev, PWM0_CHANNEL, period, pulse_width, PWM_FLAGS);
        if (ret) {
            LOG_ERR("Error setting PWM for LED1: %d", ret);
        } else {
            LOG_INF("LED1 PWM updated: Pulse width set to %u (out of %u)", pulse_width, period);
        }
    } else {
        LOG_WRN("Received unexpected length for LED1: %d", len);
    }

    return len;  // Return the number of bytes consumed
}

static ssize_t write_led2(struct bt_conn *conn,
                          const struct bt_gatt_attr *attr,
                          const void *buf, uint16_t len,
                          uint16_t offset, uint8_t flags)
{
    LOG_INF("write_led2 invoked");

    if (len == 1) {
        uint8_t received_value = *((const uint8_t *)buf);
        LOG_INF("Received value for LED2: %d", received_value);

        uint32_t period = 1000U; // 1,000 us (1 ms)
        uint32_t pulse_width = (received_value * period) / 255;

        int ret = pwm_set(pwm_dev, PWM1_CHANNEL, period, pulse_width, PWM_FLAGS);
        if (ret) {
            LOG_ERR("Error setting PWM for LED2: %d", ret);
        } else {
            LOG_INF("LED2 PWM updated: Pulse width set to %u (out of %u)", pulse_width, period);
        }
    } else {
        LOG_WRN("Received unexpected length for LED2: %d", len);
    }

    return len;  // Return the number of bytes consumed
}

/* UUID Definitions */
#define CUSTOM_SERVICE_UUID  BT_UUID_128_ENCODE(0x12345678, 0x1234, 0x5678, 0x9abc, 0xdef012345678)
#define LED1_CHAR_UUID       BT_UUID_128_ENCODE(0x12345678, 0x1234, 0x5678, 0x9abc, 0xdef012345679)
#define LED2_CHAR_UUID       BT_UUID_128_ENCODE(0x12345678, 0x1234, 0x5678, 0x9abc, 0xdef01234567A)

/* GATT Service Declaration */
BT_GATT_SERVICE_DEFINE(custom_svc,
    BT_GATT_PRIMARY_SERVICE(BT_UUID_DECLARE_128(CUSTOM_SERVICE_UUID)),

    /* LED1 Characteristic */
    BT_GATT_CHARACTERISTIC(BT_UUID_DECLARE_128(LED1_CHAR_UUID),
                           BT_GATT_CHRC_WRITE | BT_GATT_CHRC_WRITE_WITHOUT_RESP,
                           BT_GATT_PERM_WRITE,
                           NULL, write_led1, NULL),
    BT_GATT_CUD("LED1 Control", BT_GATT_PERM_READ),

    /* LED2 Characteristic */
    BT_GATT_CHARACTERISTIC(BT_UUID_DECLARE_128(LED2_CHAR_UUID),
                           BT_GATT_CHRC_WRITE | BT_GATT_CHRC_WRITE_WITHOUT_RESP,
                           BT_GATT_PERM_WRITE,
                           NULL, write_led2, NULL),
    BT_GATT_CUD("LED2 Control", BT_GATT_PERM_READ),
);

/* BLE Connection Callbacks */
void on_connected(struct bt_conn *conn, uint8_t err)
{
    if (err) {
        LOG_ERR("Failed to connect (err %d)", err);
        return;
    }
    LOG_INF("Connected");
}

void on_disconnected(struct bt_conn *conn, uint8_t reason)
{
    LOG_INF("Disconnected (reason %d)", reason);
}

static struct bt_conn_cb conn_callbacks = {
    .connected = on_connected,
    .disconnected = on_disconnected,
};

/* Advertising data */
#define DEVICE_NAME "Nordic_TwoLEDs"
#define DEVICE_NAME_LEN (sizeof(DEVICE_NAME) - 1)

static const struct bt_data ad[] = {
    BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR)),
    BT_DATA(BT_DATA_NAME_COMPLETE, DEVICE_NAME, DEVICE_NAME_LEN),
};

/* Main Function */
int main(void)
{
    int err;

    LOG_INF("Starting PWM BLE Control for Two LEDs");

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
    struct bt_le_adv_param *adv_param = BT_LE_ADV_PARAM(
        BT_LE_ADV_OPT_CONNECTABLE,
        BT_GAP_ADV_FAST_INT_MIN_2,
        BT_GAP_ADV_FAST_INT_MAX_2,
        NULL
    );

    err = bt_le_adv_start(adv_param, ad, ARRAY_SIZE(ad), NULL, 0);
    if (err) {
        LOG_ERR("Advertising failed to start (err %d)", err);
        return -1;
    }
    LOG_INF("Advertising started");

    LOG_INF("BLE service and characteristics initialized");

    /* Main loop */
    while (1) {
        k_sleep(K_FOREVER);  // Keep the program running
    }

    return 0;
}

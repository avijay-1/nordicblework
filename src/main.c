#include <zephyr/types.h>
#include <stddef.h>
#include <errno.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys/byteorder.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/pwm.h>
#include <dk_buttons_and_leds.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/hci.h>
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/bluetooth/gatt.h>

#include <zephyr/settings/settings.h>

#define DEVICE_NAME "Servo_Controller"
#define DEVICE_NAME_LEN (sizeof(DEVICE_NAME) - 1)

#define RUN_STATUS_LED DK_LED1
#define CON_STATUS_LED DK_LED2
#define RUN_LED_BLINK_INTERVAL 100000

/* PWM period for servo control (20ms) */
#define PWM_PERIOD PWM_MSEC(20)
/* Servo pulse widths */
#define SERVO_MIN_PULSE PWM_USEC(1000000) /* 1ms pulse */
#define SERVO_MAX_PULSE PWM_USEC(2000000) /* 2ms pulse */

/* UUID Definitions */
#define CUSTOM_SERVICE_UUID  BT_UUID_128_ENCODE(0x12345678, 0x1234, 0x5678, 0x9abc, 0xdef012345678)
#define SERVO1_CHAR_UUID     BT_UUID_128_ENCODE(0x12345678, 0x1234, 0x5678, 0x9abc, 0xdef012345679)
#define SERVO2_CHAR_UUID     BT_UUID_128_ENCODE(0x12345678, 0x1234, 0x5678, 0x9abc, 0xdef01234567a)

/* Custom Service and Characteristics */
static struct bt_uuid_128 custom_service_uuid = BT_UUID_INIT_128(CUSTOM_SERVICE_UUID);
static struct bt_uuid_128 servo1_char_uuid = BT_UUID_INIT_128(SERVO1_CHAR_UUID);
static struct bt_uuid_128 servo2_char_uuid = BT_UUID_INIT_128(SERVO2_CHAR_UUID);

/* Advertising Data */
static const struct bt_data ad[] = {
    BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR)),
    BT_DATA(BT_DATA_NAME_COMPLETE, DEVICE_NAME, DEVICE_NAME_LEN),
};

#define PWM_SERVO1_NODE DT_NODELABEL(pwm_servo1)
#if !DT_NODE_HAS_STATUS(PWM_SERVO1_NODE, okay)
#error "Unsupported board: pwm_servo1 devicetree node is not defined"
#endif
static const struct pwm_dt_spec pwm_servo1 = PWM_DT_SPEC_GET(PWM_SERVO1_NODE);

#define PWM_SERVO2_NODE DT_NODELABEL(pwm_servo2)
#if !DT_NODE_HAS_STATUS(PWM_SERVO2_NODE, okay)
#error "Unsupported board: pwm_servo2 devicetree node is not defined"
#endif
static const struct pwm_dt_spec pwm_servo2 = PWM_DT_SPEC_GET(PWM_SERVO2_NODE);


/* Function to set servo angle */
static int set_servo_pulse(const struct pwm_dt_spec *pwm, uint32_t pulse_width)
{
    if (!device_is_ready(pwm->dev)) {
        printk("Error: PWM device %s is not ready\n", pwm->dev->name);
        return -ENODEV;
    }

    int ret = pwm_set_dt(pwm, PWM_PERIOD, pulse_width);
    if (ret) {
        printk("Error %d: failed to set pulse width on %s\n", ret, pwm->dev->name);
    }
    return ret;
}

/* Write handler for Servo 1 */
static ssize_t write_servo1(struct bt_conn *conn, const struct bt_gatt_attr *attr,
                            const void *buf, uint16_t len, uint16_t offset, uint8_t flags)
{
    uint8_t value;

    if (len != sizeof(value)) {
        return BT_GATT_ERR(BT_ATT_ERR_INVALID_ATTRIBUTE_LEN);
    }

    memcpy(&value, buf, sizeof(value));

    /* Set Servo 1 position */
    if (value) {
        set_servo_pulse(&pwm_servo1, SERVO_MAX_PULSE);
        printk("Servo 1 activated\n");
    } else {
        set_servo_pulse(&pwm_servo1, SERVO_MIN_PULSE);
        printk("Servo 1 deactivated\n");
    }

    return len;
}

/* Write handler for Servo 2 */
static ssize_t write_servo2(struct bt_conn *conn, const struct bt_gatt_attr *attr,
                            const void *buf, uint16_t len, uint16_t offset, uint8_t flags)
{
    uint8_t value;

    if (len != sizeof(value)) {
        return BT_GATT_ERR(BT_ATT_ERR_INVALID_ATTRIBUTE_LEN);
    }

    memcpy(&value, buf, sizeof(value));

    /* Set Servo 2 position */
    if (value) {
        set_servo_pulse(&pwm_servo2, SERVO_MAX_PULSE);
        printk("Servo 2 activated\n");
    } else {
        set_servo_pulse(&pwm_servo2, SERVO_MIN_PULSE);
        printk("Servo 2 deactivated\n");
    }

    return len;
}

/* GATT Service Declaration */
BT_GATT_SERVICE_DEFINE(custom_svc,
    BT_GATT_PRIMARY_SERVICE(&custom_service_uuid),

    /* Servo 1 Characteristic */
    BT_GATT_CHARACTERISTIC(&servo1_char_uuid.uuid,
                           BT_GATT_CHRC_WRITE,
                           BT_GATT_PERM_WRITE,
                           NULL, write_servo1, NULL),
    BT_GATT_CUD("Servo 1 Control", BT_GATT_PERM_READ),

    /* Servo 2 Characteristic */
    BT_GATT_CHARACTERISTIC(&servo2_char_uuid.uuid,
                           BT_GATT_CHRC_WRITE,
                           BT_GATT_PERM_WRITE,
                           NULL, write_servo2, NULL),
    BT_GATT_CUD("Servo 2 Control", BT_GATT_PERM_READ),
);

/* Bluetooth Callbacks */
static void connected(struct bt_conn *conn, uint8_t err)
{
    if (err) {
        printk("Connection failed (err %u)\n", err);
        return;
    }

    printk("Connected\n");
    dk_set_led_on(CON_STATUS_LED);
}

static void disconnected(struct bt_conn *conn, uint8_t reason)
{
    printk("Disconnected (reason %u)\n", reason);
    dk_set_led_off(CON_STATUS_LED);
}

/* Bluetooth Connection Callbacks Structure */
BT_CONN_CB_DEFINE(conn_callbacks) = {
    .connected = connected,
    .disconnected = disconnected,
};

/* Initialize Bluetooth */
static void bt_ready(int err)
{
    if (err) {
        printk("Bluetooth init failed (err %d)\n", err);
        return;
    }

    printk("Bluetooth initialized\n");

    /* Load settings if enabled */
    if (IS_ENABLED(CONFIG_SETTINGS)) {
        settings_load();
    }

    struct bt_le_adv_param *adv_param = BT_LE_ADV_PARAM(
        BT_LE_ADV_OPT_CONNECTABLE, /* Advertise connectable */
        BT_GAP_ADV_FAST_INT_MIN_2, /* Minimum Advertising Interval */
        BT_GAP_ADV_FAST_INT_MAX_2, /* Maximum Advertising Interval */
        NULL);

    err = bt_le_adv_start(adv_param, ad, ARRAY_SIZE(ad), NULL, 0);
    if (err) {
        printk("Advertising failed to start (err %d)\n", err);
        return;
    }

    printk("Advertising successfully started\n");
}

/* Main Function */
int main(void)
{
    int err;
    int blink_status = 0;

    printk("Starting Servo Control Application\n");

    /* Initialize LEDs */
    err = dk_leds_init();
    if (err) {
        printk("LEDs init failed (err %d)\n", err);
        return -1;
    }

    /* Initialize PWM devices */
    if (!device_is_ready(pwm_servo1.dev)) {
        printk("Error: PWM device %s is not ready\n", pwm_servo1.dev->name);
        return -ENODEV;
    }
    if (!device_is_ready(pwm_servo2.dev)) {
        printk("Error: PWM device %s is not ready\n", pwm_servo2.dev->name);
        return -ENODEV;
    }

    /* Set initial servo positions */
    set_servo_pulse(&pwm_servo1, SERVO_MIN_PULSE);
    set_servo_pulse(&pwm_servo2, SERVO_MIN_PULSE);

    /* Enable Bluetooth */
    err = bt_enable(bt_ready);
    if (err) {
        printk("Bluetooth init failed (err %d)\n", err);
        return -1;
    }

    /* Blink RUN_STATUS_LED in the main loop */
    while (1) {
        dk_set_led(RUN_STATUS_LED, (++blink_status) % 2);
        k_sleep(K_MSEC(RUN_LED_BLINK_INTERVAL));
    }

    return 0;
}

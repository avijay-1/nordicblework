#include <zephyr/types.h>
#include <stddef.h>
#include <errno.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys/byteorder.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/hci.h>
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/bluetooth/gatt.h>

#include <zephyr/settings/settings.h>

#include <dk_buttons_and_leds.h>

#define DEVICE_NAME "Nordic_TwoLEDs"
#define DEVICE_NAME_LEN (sizeof(DEVICE_NAME) - 1)

#define RUN_STATUS_LED DK_LED1
#define CON_STATUS_LED DK_LED2
#define RUN_LED_BLINK_INTERVAL 1000

#define USER_LED DK_LED3   // First LED
#define USER_LED_2 DK_LED4 // Second LED

/* UUID Definitions */
#define CUSTOM_SERVICE_UUID  BT_UUID_128_ENCODE(0x12345678, 0x1234, 0x5678, 0x9abc, 0xdef012345678)
#define LED1_CHAR_UUID       BT_UUID_128_ENCODE(0x12345678, 0x1234, 0x5678, 0x9abc, 0xdef012345679)
#define LED2_CHAR_UUID       BT_UUID_128_ENCODE(0x12345678, 0x1234, 0x5678, 0x9abc, 0xdef01234567a)

/* Custom Service and Characteristics */
static struct bt_uuid_128 custom_service_uuid = BT_UUID_INIT_128(CUSTOM_SERVICE_UUID);
static struct bt_uuid_128 led1_char_uuid = BT_UUID_INIT_128(LED1_CHAR_UUID);
static struct bt_uuid_128 led2_char_uuid = BT_UUID_INIT_128(LED2_CHAR_UUID);

/* Advertising Data */
static const struct bt_data ad[] = {
    BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR)),
    BT_DATA(BT_DATA_NAME_COMPLETE, DEVICE_NAME, DEVICE_NAME_LEN),
};

/* Write handler for LED3 */
static ssize_t write_led1(struct bt_conn *conn, const struct bt_gatt_attr *attr,
                          const void *buf, uint16_t len, uint16_t offset, uint8_t flags)
{
    uint8_t value;

    if (len != sizeof(value)) {
        return BT_GATT_ERR(BT_ATT_ERR_INVALID_ATTRIBUTE_LEN);
    }

    memcpy(&value, buf, sizeof(value));

    /* Turn LED3 on or off */
    if (value) {
        dk_set_led_on(USER_LED);
        printk("LED3 ON\n");
    } else {
        dk_set_led_off(USER_LED);
        printk("LED3 OFF\n");
    }

    return len;
}

/* Write handler for LED4 */
static ssize_t write_led2(struct bt_conn *conn, const struct bt_gatt_attr *attr,
                          const void *buf, uint16_t len, uint16_t offset, uint8_t flags)
{
    uint8_t value;

    if (len != sizeof(value)) {
        return BT_GATT_ERR(BT_ATT_ERR_INVALID_ATTRIBUTE_LEN);
    }

    memcpy(&value, buf, sizeof(value));

    /* Turn LED4 on or off */
    if (value) {
        dk_set_led_on(USER_LED_2);
        printk("LED4 ON\n");
    } else {
        dk_set_led_off(USER_LED_2);
        printk("LED4 OFF\n");
    }

    return len;
}

/* GATT Service Declaration */
BT_GATT_SERVICE_DEFINE(custom_svc,
    BT_GATT_PRIMARY_SERVICE(&custom_service_uuid),

    /* LED1 Characteristic */
    BT_GATT_CHARACTERISTIC(&led1_char_uuid.uuid,
                           BT_GATT_CHRC_WRITE,
                           BT_GATT_PERM_WRITE,
                           NULL, write_led1, NULL),
	BT_GATT_CUD("LED3 Control", BT_GATT_PERM_READ),
    /* LED2 Characteristic */
    BT_GATT_CHARACTERISTIC(&led2_char_uuid.uuid,
                           BT_GATT_CHRC_WRITE,
                           BT_GATT_PERM_WRITE,
                           NULL, write_led2, NULL),
	BT_GATT_CUD("LED4 Control", BT_GATT_PERM_READ),
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

    printk("Starting Two LED Control Application\n");

    /* Initialize LEDs */
    err = dk_leds_init();
    if (err) {
        printk("LEDs init failed (err %d)\n", err);
        return -1;  // Return error code
    }

    /* Enable Bluetooth */
    err = bt_enable(bt_ready);
    if (err) {
        printk("Bluetooth init failed (err %d)\n", err);
        return -1;  // Return error code
    }

    /* Blink RUN_STATUS_LED in the main loop */
    while (1) {
        dk_set_led(RUN_STATUS_LED, (++blink_status) % 2);
        k_sleep(K_MSEC(RUN_LED_BLINK_INTERVAL));
    }

    return 0;  // Return 0 (successful execution)
}

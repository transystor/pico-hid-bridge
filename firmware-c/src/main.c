#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "bsp/board.h"
#include "tusb.h"

#define WIFI_SSID "CHANGE_ME"
#define WIFI_PASSWORD "CHANGE_ME"
#define TCP_PORT 5000
#define STARTUP_LED_BLINK_MS 200
#define DEMO_MOVE_INTERVAL_MS 1500

static void hid_task(void);
static bool wifi_connect_blocking(void);
static void tcp_server_task(void);
static void led_blink_task(void);

static absolute_time_t next_blink_at;
static absolute_time_t next_demo_move_at;
static bool led_state = false;
static bool wifi_connected = false;

int main(void)
{
    stdio_init_all();
    board_init();
    tusb_init();

    if (cyw43_arch_init())
    {
        printf("Failed to init cyw43\n");
        return 1;
    }

    printf("pico-hid-bridge starting...\n");

    next_blink_at = make_timeout_time_ms(STARTUP_LED_BLINK_MS);
    next_demo_move_at = make_timeout_time_ms(DEMO_MOVE_INTERVAL_MS);

    wifi_connected = wifi_connect_blocking();

    while (true)
    {
        tud_task();
        hid_task();
        tcp_server_task();
        led_blink_task();
        sleep_ms(1);
    }
}

static bool wifi_connect_blocking(void)
{
    cyw43_arch_enable_sta_mode();

    printf("Connecting to Wi-Fi: %s\n", WIFI_SSID);

    int result = cyw43_arch_wifi_connect_timeout_ms(
        WIFI_SSID,
        WIFI_PASSWORD,
        CYW43_AUTH_WPA2_AES_PSK,
        30000);

    if (result != 0)
    {
        printf("Wi-Fi connect failed: %d\n", result);
        return false;
    }

    printf("Wi-Fi connected\n");
    return true;
}

static void hid_task(void)
{
    if (!tud_hid_ready())
    {
        return;
    }

    if (absolute_time_diff_us(get_absolute_time(), next_demo_move_at) > 0)
    {
        next_demo_move_at = make_timeout_time_ms(DEMO_MOVE_INTERVAL_MS);

        // Временная демонстрационная проверка HID канала.
        // Двигаем мышь чуть вправо и обратно, чтобы на первом этапе
        // подтвердить, что TinyUSB mouse report реально проходит до ПК.
        tud_hid_mouse_report(0, 0x00, 8, 0, 0, 0);
        sleep_ms(25);
        tud_hid_mouse_report(0, 0x00, -8, 0, 0, 0);
    }
}

static void tcp_server_task(void)
{
    if (!wifi_connected)
    {
        return;
    }

    // Пока placeholder. Следующим шагом добавим lwIP listener.
    (void) TCP_PORT;
}

static void led_blink_task(void)
{
    if (absolute_time_diff_us(get_absolute_time(), next_blink_at) <= 0)
    {
        return;
    }

    next_blink_at = make_timeout_time_ms(STARTUP_LED_BLINK_MS);
    led_state = !led_state;
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, led_state);
}

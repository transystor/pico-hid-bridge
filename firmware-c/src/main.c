#include <stdio.h>
#include <string.h>

#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "bsp/board.h"
#include "tusb.h"

#define WIFI_SSID "CHANGE_ME"
#define WIFI_PASSWORD "CHANGE_ME"
#define TCP_PORT 5000

static void hid_task(void);
static void wifi_connect_task(void);
static void tcp_server_task(void);

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

    wifi_connect_task();

    while (true)
    {
        tud_task();
        hid_task();
        tcp_server_task();
        sleep_ms(1);
    }
}

static void wifi_connect_task(void)
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
        return;
    }

    printf("Wi-Fi connected\n");
}

static void hid_task(void)
{
    // Пока пусто. Здесь будет:
    // - очередь HID-команд,
    // - относительное движение мыши,
    // - клики,
    // - проверка готовности tud_hid_n_ready().
}

static void tcp_server_task(void)
{
    // Пока пусто. Здесь будет:
    // - lwIP TCP listener на TCP_PORT,
    // - приём текстовых команд,
    // - разбор MOVE / CLICK / DOWN / UP,
    // - постановка действий в HID-очередь.
}

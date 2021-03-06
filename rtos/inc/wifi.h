#ifndef __WIFI_H__
#define __WIFI_H__

#include <espressif/esp_common.h>
#include <esp/uart.h>
#include <stdio.h>
#include <ssid_config.h>
#include <esp8266.h>
#include <espressif/esp_sta.h>
#include <espressif/esp_wifi.h>
#include <espressif/esp_common.h>

static int wifi_alive = 0;

void wifi_spin();
void wifi_try_connect();
const char* wifi_get_ip();


const char* wifi_get_ip()
{
    static char ip[16] = "0.0.0.0";
    ip[0] = 0;
    struct ip_info ipinfo;
    (void) sdk_wifi_get_ip_info(STATION_IF, &ipinfo);
    snprintf(ip, sizeof(ip), IPSTR, IP2STR(&ipinfo.ip));
    return (char*) ip;
}


// *******************************************************************************************
// 
void wifi_spin()
{
    struct sdk_station_config config = { .ssid = WIFI_SSID, .password = WIFI_PASS, };

	//configure wifi 
    printf("%s: Connecting to WiFi\n\r", __func__);

    sdk_wifi_set_opmode (STATION_MODE);
    sdk_wifi_station_set_config(&config);

    while (1) {
        wifi_try_connect();
    }
}

// *******************************************************************************************
// 
void wifi_try_connect()
{
    uint8_t status = 0;
    uint8_t retries = 30;
    wifi_alive = 0;

    while ((status != STATION_GOT_IP) && (retries)) {
        status = sdk_wifi_station_get_connect_status();
        printf("%s: status = %d\n\r", __func__, status);
			
        //connection failures 
        if (status == STATION_WRONG_PASSWORD) {
            printf("WiFi: wrong password\n\r");
            break;
        } else if (status == STATION_NO_AP_FOUND) {
            printf("WiFi: AP not found\n\r");
            break;
        } else if (status == STATION_CONNECT_FAIL) {
            printf("WiFi: connection failed\r\n");
            break;
        }
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        --retries;
    }

    while ((status = sdk_wifi_station_get_connect_status()) == STATION_GOT_IP) {
        //connected
        if (wifi_alive == 0) {
            printf("WiFi: Connected\n\r");
            wifi_alive = 1;
        }

        vTaskDelay(500 / portTICK_PERIOD_MS);
    }

    //did not connect 
    wifi_alive = 0;
    printf("WiFi: disconnected\n\r");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
}

#endif 



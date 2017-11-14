
#include <espressif/esp_common.h>
#include <esp/uart.h>
#include <string.h>
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <stdio.h>
#include <esp8266.h>

// this must be ahead of any mbedtls header files so the local mbedtls/config.h can be properly referenced
#include "client_config.h" 
#include "ssl_connection.h"

#include "inc/irsend/futronix.h" 
#include "inc/storage.h" 
#include "inc/parser.h" 
#include "inc/blink.h"
#include "inc/wifi.h"
#include "inc/mqtt.h"
//#include "inc/httpserver.h"

#define USE_IR_PIN 	false
#define USE_LED_PIN	true

/* certs, key, and endpoint */
//extern char *ca_cert, *client_endpoint, *client_cert, *client_key;



// *******************************************************************************************
// 
void mqtt_handle_msg(mqtt_message_t *msg)
{
	//parse the json 
	//int scene = get_scene(msg);
    int scene = 1;

	if (USE_IR_PIN) {
		futronix_irsend(0x17); 
	}

	if (USE_LED_PIN) {
		blink(scene, 500);
	}
}


// *******************************************************************************************
// 
static void mqtt_task(void *pvParameters) {
    mqtt_spin();
}

// *******************************************************************************************
// Connect to wifi, and then loop & continually check that we're still connected.
// 
static void wifi_task(void *pvParameters) {
    wifi_spin();
}

// *******************************************************************************************
// 
void unittest_ir_task(void* pvParameters)
{
    while(1){
        for (int n=0; n<100; n++)
            futronix_irsend(17); 
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
}

// *******************************************************************************************
// 
void unittest_spiffs_task(void* pvParameters)
{
    vTaskDelay(3000 / portTICK_PERIOD_MS);
    //while(1){
        uint8_t buf[] = "Example data, written by ESP8266";
        char* outbuf = "one";   

        int wbytes = storage_write("new.txt", (const uint8_t*)outbuf, sizeof(buf));
        blink(wbytes, 500);

/*
        if (wbytes == 0)
            blink(3, 100);
        else if (wbytes < 0)
            blink(2, 100);
        else 
            blink(wbytes, 100);
*/
    
        vTaskDelay(1000 / portTICK_PERIOD_MS);

        int rbytes = storage_read("new.txt", buf, 100);


        if (rbytes == 0)
            blink(3, 100);
        else if (rbytes < 0)
            blink(2, 100);
        else 
            blink(rbytes, 100);
    //}
    vTaskDelay(10000 / portTICK_PERIOD_MS);
}

// *******************************************************************************************
// Entry point 
// 
void user_init(void) {
    uart_set_baud(0, 9600);
    printf("SDK version: %s, free heap %u\n", sdk_system_get_sdk_version(), xPortGetFreeHeapSize());

	if (USE_IR_PIN) {
    	gpio_enable(IR_SEND_PIN, GPIO_OUTPUT);
    	gpio_write(IR_SEND_PIN, 1);
	}

	if (USE_LED_PIN) {
    	gpio_enable(LED_PIN, GPIO_OUTPUT);
    	gpio_write(LED_PIN, 1);
	}

    storage_init();
    mqtt_init();

    //xTaskCreate(&wifi_task, "wifi_task", 256, NULL, 2, NULL);
    //xTaskCreate(&mqtt_task, "mqtt_task", 2048, NULL, 2, NULL);
    unittest_spiffs_task(0);
}



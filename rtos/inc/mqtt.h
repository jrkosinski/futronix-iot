#ifndef __MQTT_H__
#define __MQTT_H__

#include <espressif/esp_common.h>
#include <esp/uart.h>
#include <string.h>
#include <FreeRTOS.h>
#include <stdio.h>
#include <esp8266.h>
#include <paho_mqtt_c/MQTTESP8266.h>
#include <paho_mqtt_c/MQTTClient.h>

#define MQTT_PUB_TOPIC "$aws/things/pything3/shadow/update/accepted"
#define MQTT_SUB_TOPIC "$aws/things/pything3/shadow/update/accepted"
#define MQTT_PORT 8883

QueueHandle_t publish_queue;
SSLConnection *ssl_conn;
int ssl_reset;

void mqtt_init();
void mqtt_spin();
int mqtt_ssl_read(mqtt_network_t * n, unsigned char* buffer, int len, int timeout_ms);
int mqtt_ssl_write(mqtt_network_t* n, unsigned char* buffer, int len, int timeout_ms);
void mqtt_topic_received(mqtt_message_data_t *md); 
void mqtt_handle_msg(mqtt_message_t* msg); 


// *******************************************************************************************
// Gets MAC address from device 
// 
const char *get_mac_addr(void) {
    // Use MAC address for Station as unique ID
    static char my_id[13];
    static bool my_id_done = false;
    int8_t i;
    uint8_t x;

    if (my_id_done)
        return my_id;
    
    if (!sdk_wifi_get_macaddr(STATION_IF, (uint8_t *) my_id))
        return NULL;

    for (i = 5; i >= 0; --i) {
        x = my_id[i] & 0x0F;
	    if (x > 9)
		   x += 7;
        my_id[i * 2 + 1] = x + '0';
        x = my_id[i] >> 4;
        if (x > 9)
            x += 7;
        my_id[i * 2] = x + '0';
    }

    my_id[12] = '\0';
    my_id_done = true;
    return my_id;
}

// *******************************************************************************************
// 
void mqtt_init()
{
    publish_queue = xQueueCreate(3, 16);
}

// *******************************************************************************************
int mqtt_ssl_read(mqtt_network_t * n, unsigned char* buffer, int len, int timeout_ms) {
    int r = ssl_read(ssl_conn, buffer, len, timeout_ms);
    if (r <= 0 && (r != MBEDTLS_ERR_SSL_WANT_READ
                    && r != MBEDTLS_ERR_SSL_WANT_WRITE
                    && r != MBEDTLS_ERR_SSL_TIMEOUT)) {
	    printf("%s: TLS read error (%d), resetting\n\r", __func__, r);
	    ssl_reset = 1;
	};

    return r;
}

// *******************************************************************************************
// I dont think we're using this 
int mqtt_ssl_write(mqtt_network_t* n, unsigned char* buffer, int len, int timeout_ms) {

    int r = ssl_write(ssl_conn, buffer, len, timeout_ms);
    if (r <= 0 && (r != MBEDTLS_ERR_SSL_WANT_READ && r != MBEDTLS_ERR_SSL_WANT_WRITE)) {
        printf("%s: TLS write error (%d), resetting\n\r", __func__, r);
        ssl_reset = 1;
    }

    return r;
}

// *******************************************************************************************
// Fires when a message is received from the MQTT server 
// 
void mqtt_topic_received(mqtt_message_data_t *md) {
    mqtt_message_t *message = md->message;    	
    int i;

    if (message->payloadlen > 0)
	{
		mqtt_handle_msg(message);
	}

    printf("Received: ");
    for (i = 0; i < md->topic->lenstring.len; ++i)
        printf("%c", md->topic->lenstring.data[i]);

    printf(" = ");
    for (i = 0; i < (int) message->payloadlen; ++i)
        printf("%c", ((char *) (message->payload))[i]);
    printf("\r\n");

    //TODO: parse json
	//jsmn_parser p;
	//jsmntok_t t[128]; 
	//char* JSON_STRING = ((char*)(message->payload)); 
}

// *******************************************************************************************
// 
void mqtt_spin()
{
    int ret = 0;
    struct mqtt_network network;
    mqtt_client_t client = mqtt_client_default;
    char mqtt_client_id[20];
    uint8_t mqtt_buf[100];
    uint8_t mqtt_readbuf[100];
    mqtt_packet_connect_data_t data = mqtt_packet_connect_data_initializer;

	memset(mqtt_client_id, 0, sizeof(mqtt_client_id));
    strcpy(mqtt_client_id, "ESP-");
    strcat(mqtt_client_id, get_mac_addr());

    ssl_conn = (SSLConnection *) malloc(sizeof(SSLConnection));

    while (1) {
        if (!wifi_alive) {
            vTaskDelay(1000 / portTICK_PERIOD_MS);
            continue;
        }

	printf("%s: started\n\r", __func__);
	ssl_reset = 0;
	ssl_init(ssl_conn);
	ssl_conn->ca_cert_str = ca_cert;
	ssl_conn->client_cert_str = client_cert;
	ssl_conn->client_key_str = client_key;

	mqtt_network_new(&network);
	network.mqttread = mqtt_ssl_read;
	network.mqttwrite = mqtt_ssl_write;

	printf("%s: connecting to MQTT server %s ... ", __func__,
        client_endpoint);
	ret = ssl_connect(ssl_conn, client_endpoint, MQTT_PORT);

	if (ret) {
		printf("error: %d\n\r", ret);
		ssl_destroy(ssl_conn);
		continue;
	}
        printf("done\n\r");

	mqtt_client_new(&client, &network, 5000, mqtt_buf, 1000, mqtt_readbuf, 1000);

	data.willFlag = 0;
	data.MQTTVersion = 4;
	data.cleansession = 1;
	data.clientID.cstring = mqtt_client_id;
	data.username.cstring = NULL;
	data.password.cstring = NULL;
	data.keepAliveInterval = 1000;
	printf("Send MQTT connect ... ");
	ret = mqtt_connect(&client, &data);

	if (ret) {
		   printf("error: %d\n\r", ret);
		    ssl_destroy(ssl_conn);
		    continue;
	}

	printf("done\r\n");
	mqtt_subscribe(&client, MQTT_SUB_TOPIC, MQTT_QOS1, mqtt_topic_received);
	xQueueReset(publish_queue);

	while (wifi_alive && !ssl_reset) {
        char msg[64];
            while (xQueueReceive(publish_queue, (void *) msg, 0) == pdTRUE) {
                TickType_t task_tick = xTaskGetTickCount();
                uint32_t free_heap = xPortGetFreeHeapSize();
                uint32_t free_stack = uxTaskGetStackHighWaterMark(NULL);
                snprintf(msg, sizeof(msg), "%u: free heap %u, free stack %u", task_tick, free_heap, free_stack * 4);
                printf("Publishing: %s\r\n", msg);

                mqtt_message_t message;
                message.payload = msg;
                message.payloadlen = strlen(msg);
                message.dup = 0;
                message.qos = MQTT_QOS1;
                message.retained = 0;
                ret = mqtt_publish(&client, MQTT_PUB_TOPIC, &message);
                if (ret != MQTT_SUCCESS) {
                    printf("error while publishing message: %d\n", ret);
                }
                else {
		            //HITTING HERE blink();
                }
            }

            ret = mqtt_yield(&client, 1000);
            if (ret == MQTT_DISCONNECTED)
                break;
        }

        printf("Connection dropped, request restart\n\r");
        ssl_destroy(ssl_conn);
    }
}

#endif


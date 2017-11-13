#ifndef __BLINK_H__
#define __BLINK_H__

#define LED_PIN 2

// *******************************************************************************************
// Blink the LED once. 
// 
static void blink_once(int ms)
{
    gpio_write(LED_PIN, 0);
    vTaskDelay(ms / portTICK_PERIOD_MS);
    gpio_write(LED_PIN, 1);
    vTaskDelay(ms / portTICK_PERIOD_MS);
}

// *******************************************************************************************
// Blink the LED N times. 
// 
static void blink(int count, int ms)
{
	for(int n=0; n<count; n++)
	    blink_once(ms);
}

#endif 


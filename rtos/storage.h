#ifndef __STORAGE_H__
#define __STORAGE_H__

#include "fcntl.h"
#include "unistd.h"

#include "spiffs.h"
#include "esp_spiffs.h" 
#include "blink.h"

const char* wifiPasswdFileName = "wifiPasswd";
const char* wifiUsernameFileName = "wifiUsername"; 

int write_file(const char* filename, const uint8_t* data, uint32_t len); 
int read_file(const char* filename, uint8_t* buf, uint32_t buf_size);

void storage_init()
{
#if SPIFFS_SINGLETON == 1
    esp_spiffs_init();
#else
    // for run-time configuration when SPIFFS_SINGLETON = 0
    esp_spiffs_init(0x200000, 0x10000);
#endif

    if (esp_spiffs_mount() != SPIFFS_OK) {
        printf("Error mount SPIFFS\n");
    }
}

char* storage_get_wifi_passwd() {
    const uint32_t buf_size = 1024;
	uint8_t buf[buf_size];
	int bytes = read_file(wifiPasswdFileName, buf, buf_size); 
	return (bytes ? (char*)buf : 0);
}

char* storage_get_wifi_username() {
    const uint32_t buf_size = 1024;
	uint8_t buf[buf_size];
	int bytes = read_file(wifiUsernameFileName, buf, buf_size); 
	return (bytes ? (char*)buf : 0);
}

int storage_set_wifi_passwd(const char* value, uint32_t len) {
	return write_file(wifiPasswdFileName, (uint8_t*)value, len);
}

int storage_set_wifi_username(const char* value, uint32_t len) {
	return write_file(wifiUsernameFileName, (uint8_t*)value, len);
}

int write_file(const char* filename, const uint8_t* data, uint32_t len)
{
    //uint8_t buf[] = "Example data, written by ESP8266";

    int fd = open(filename, O_WRONLY|O_CREAT, 0);
    if (fd < 0) {
        printf("Error opening file\n");
		return 0;
    }

    int written = write(fd, data, len);
    printf("Written %d bytes\n", written);

    close(fd);
	return written;
}

int read_file(const char* filename, uint8_t* buf, uint32_t buf_size)
{
    spiffs_file fd = SPIFFS_open(&fs, filename, SPIFFS_RDONLY, 0);
    if (fd < 0) {
        printf("Error opening file\n");
		return 0;
    }

    int read_bytes = SPIFFS_read(&fs, fd, buf, buf_size);
    printf("Read %d bytes\n", read_bytes);

    buf[read_bytes] = '\0';    // zero terminate string
    printf("Data: %s\n", buf);

    SPIFFS_close(&fs, fd);
	return read_bytes;
}

#endif 



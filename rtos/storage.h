#ifndef __STORAGE_H__
#define __STORAGE_H__

#include "fcntl.h"
#include "unistd.h"

#include "spiffs.h"
#include "esp_spiffs.h"

const char* wifiPasswdFileName = "wifiPasswd";
const char* wifiUsernameFileName = "wifiUsername"; 

int write_file(const char* filename, const uint8_t* data); 
int read_file(const char* filename, uint8_t* buf);

char* getWifiPasswd() {
	uint8_t buf[1024];
	int bytes = read_file(wifiPasswdFileName, buf); 
	return (bytes ? (char*)buf : 0);
}

char* getWifiUsername() {
	uint8_t buf[1024];
	int bytes = read_file(wifiUsernameFileName, buf); 
	return (bytes ? (char*)buf : 0);
}

int setWifiPasswd(const char* value) {
	return write_file(wifiPasswdFileName, (uint8_t*)value);
}

int setWifiUsername(const char* value) {
	return write_file(wifiUsernameFileName, (uint8_t*)value);
}

int write_file(const char* filename, const uint8_t* data)
{
    	//uint8_t buf[] = "Example data, written by ESP8266";

    	int fd = open(filename, O_WRONLY|O_CREAT, 0);
    	if (fd < 0) {
		printf("Error opening file\n");
		return false;
    	}

    	int written = write(fd, data, sizeof(data));
    	printf("Written %d bytes\n", written);

    	close(fd);
	return written;
}

int read_file(const char* filename, uint8_t* buf)
{
    //const int buf_size = 0xFF;
    //uint8_t buf[buf_size];
    	spiffs_file fd = SPIFFS_open(&fs, filename, SPIFFS_RDONLY, 0);
    	if (fd < 0) {
		printf("Error opening file\n");
		return;
    	}

    	int read_bytes = SPIFFS_read(&fs, fd, buf, buf_size);
    	printf("Read %d bytes\n", read_bytes);

    	buf[read_bytes] = '\0';    // zero terminate string
    	printf("Data: %s\n", buf);

    	SPIFFS_close(&fs, fd);
	return read_bytes;
}

#endif 

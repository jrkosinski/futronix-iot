PROGRAM=futronix-iot

EXTRA_COMPONENTS = extras/paho_mqtt_c extras/mbedtls extras/jsmn extras/spiffs extras/httpd
EXTRA_CFLAGS=-DLWIP_HTTPD_CGI=1 -DLWIP_HTTPD_SSI=1 -I./fsdata

FLASH_SIZE = 32

#Enable debugging
#EXTRA_CFLAGS+=-DLWIP_DEBUG=1 -DHTTPD_DEBUG=LWIP_DBG_ON


include ../../common.mk

$(eval $(call make_spiffs_image,files))

html:
	@echo "Generating fsdata.."
	cd fsdata && ./makefsdata

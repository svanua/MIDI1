#pragma once
#define ESP32_WEB_VersionFirmware 0x01

#define MaxWebSocket_FrameByte 125

//#define SHUTDOWN_NOCLIENT 
#ifdef SHUTDOWN_NOCLIENT
    #define CONST_TIME_WIFI_OFF     60*1000
#endif 

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>

//#include <ESP32httpUpdateServer.h>

//#include <TimeLib.h>

void ESP32_WEB_init();
void ESP32_WEB_Thread(void *pvParameters);



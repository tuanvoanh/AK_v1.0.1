#include <ESPAsyncWebServer.h>
#include <ESPAsyncWiFiManager.h>
#include <WiFi.h>
//#include <HTTPClient.h>
#include <ArduinoJson.h>
//#include <ESP32httpUpdate.h>
#include "ledState.h"

//state
#define NORMAL          0
#define SEND_STATE      1
#define UPDATE_FIRMWARE 2
#define ALERT           3
#define RESET_WIFI      4
//
#define BAUDRATE  115200
#define LED_R 2
#define LED_G 2
#define LED_B 2

#define LED LED_B
#define LEDSYS LED_B

#define USE_SERIAL Serial
#define BTN 18 //Button update firmware
#define RS  19 //Button reset wifi

#define SERVER "cretatech.com"  // chua su dung
#define PORT 8999               // chua su dung
//#define URL "http://cretatech.com:8000/download/creta_G.ino.nodemcu.bin"

//mqtt define
#include <PubSubClient.h>
#define mqtt_server "cretatech.com" // Thay bằng thông tin của bạn
//#define mqtt_server  "iot.eclipse.org"
#define mqtt_port 1883

#define timeReset 120 //minute
//WebSocketsClient webSocket;
void wifiConnect();
void wifiConfig();// khong sai cho 32
//void resetState(); // chuyen sang module test
int rP(uint8_t a);
void beginSmart();// khong sai cho 32
int initWifi();
void initPort();
int initSystem(void);
//void webSocketEvent(WStype_t type, uint8_t * payload, size_t length);


//New function
void checkWifi();
int wifiData_Read(int a);

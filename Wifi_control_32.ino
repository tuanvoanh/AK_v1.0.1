#include "Wifi_control_32.h"

//WebSocketsClient webSocket;
// wifi /////////////////////////////////////////////////////
AsyncWebServer server(80);
DNSServer dns;
void p(String str){
  String str1 = String(millis()) + ": " + str;
  Serial.println(str1);  
}

int rP(uint8_t a){
  return digitalRead(a);
}

/* s3 */ void hP(uint8_t a){
  digitalWrite(a, LOW);
}
/* s4 */ void lP(uint8_t a){
  digitalWrite(a, HIGH);
}

/* s5 */ void tP(uint8_t a){
  digitalWrite(a, digitalRead(a) ^ 0x01);
}
void beginSmart(){
  WiFi.beginSmartConfig();
  while(!WiFi.smartConfigDone()){
         delay(100);
         tP(LED);
         //Kiểm tra kết nối thành công in thông báo
      if(WiFi.smartConfigDone()){
         p("SmartConfig Success");
      }
   }
   return;
}

int initWifi(){
  int cnt = 0;
  p("Connecting to Wifi");
  //WiFi.mode(WIFI_STA);
  WiFi.mode(WIFI_AP_STA);
  beginSmart();
  //WiFi.begin("CRETA-VNPT", "88888888");
  delay(1000);
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    tP(LED);
    Serial.print(".");
    if(cnt++ >= 25){
       beginSmart();
     }
  }
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
  
}
void wifiConnect(){
  Serial.begin(BAUDRATE);
  while(!Serial){
  }
  delay(200);
  AsyncWiFiManager wifiManager(&server,&dns);
  //digitalWrite(LED_R,1);
  wifiManager.autoConnect("Kdrum_monitor","88888888");
  Serial.println("connected...yeey :)");
  //digitalWrite(LED_R,0);
}
void wifiConfig(){
  ledConfig();
  AsyncWiFiManager wifiManager(&server,&dns);
  wifiManager.startConfigPortal("Kdrum_monitor","88888888");
  Serial.println("connected...yeey :)");
  delay(1000);
  //digitalWrite(LED_R,0);  
}

// init System ///////////////

int initSystem(void){
  /*Serial*/
  Serial.begin(BAUDRATE);
  while(!Serial){
  }
  delay(200);
  /*Status Led*/
  for(int i = 0; i < 10; i++){
    lP(LED);
    delay(100);
    p("LED -> OK");
  }
  /*Connect to Wifi*/
  initWifi();
  /**/
}
void initPort(){
    pinMode(RS, INPUT);
    
}
////////////////////////////////////////////////

// http update /////////////////////////
/*void updateFirmware() {
        t_httpUpdate_return ret = ESPhttpUpdate.update(URL); // Bạn cần thay đúng địa chỉ web chứa fw của bạn
        //Ví dụ
        //t_httpUpdate_return ret = ESPhttpUpdate.update("http://hocarm.org/BasicOTA.ino.bin"); // Bạn cần thay đúng địa chỉ web chứa fw của bạn
        //t_httpUpdate_return  ret = ESPhttpUpdate.update("https://server/file.bin");

        switch(ret) {
            case HTTP_UPDATE_FAILED:
                USE_SERIAL.printf("HTTP_UPDATE_FAILD Error (%d): %s", ESPhttpUpdate.getLastError(), ESPhttpUpdate.getLastErrorString().c_str());
                break;

            case HTTP_UPDATE_NO_UPDATES:
                USE_SERIAL.println("HTTP_UPDATE_NO_UPDATES");
                break;

            case HTTP_UPDATE_OK:
                USE_SERIAL.println("HTTP_UPDATE_OK");
                break;
        }
}*/
///////////////////////////
//New code//
int wifiSignal = 0;
void checkWifi(){
  if(WiFi.status() != WL_CONNECTED){
    wifiSignal = 0;
  }
  else{
    long rssi = WiFi.RSSI();
    if((rssi > -76)||(rssi = -76)){
      wifiSignal = 2;
    }
    else if(rssi < -76){
      wifiSignal = 1;
    }
  }
}
int wifiData_Read(int a){
  if (a == 1){
    return wifiSignal;
  }
}


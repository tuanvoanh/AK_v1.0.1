#include "Wifi_control_32.h"
#include "ledState.h"
#include "GPIO.h"
#include "SIM808.h"
#include <SimpleTimer.h>
#include "internet_time.h"

SimpleTimer timer;
DynamicJsonBuffer jsonBuffer(200);
JsonObject& vObj = jsonBuffer.createObject();
JsonObject& data0 = jsonBuffer.createObject();
String a = "";
uint8_t gFunction = 0;
uint8_t gData = 0;
uint8_t gState = 0;
String gSdt="";
WiFiClient ethClient;
PubSubClient client(ethClient);
char topic[20];
String gTopic = "";
int inputLastState = 0;
int alarmFlag = 0;
void stateSend(){
  //tP(LED);
  a = "";
  //vObj["id"] = gTopic;
  vObj["id"] = "espdk001";
  vObj["func"] = 0;
  //vObj["time"] = timeGet();  
  data0["i5"] = inputLastState & 0x01;
  data0["i1"] = (inputLastState >> 1) & 0x01;
  data0["i2"] = (inputLastState >> 2) & 0x01;
  data0["i3"] = (inputLastState >> 3) & 0x01;
  data0["i4"] = (inputLastState >> 4) & 0x01;
  vObj["data"] = data0;
  vObj.printTo(a);
  Serial.println(a);
  //client.publish((gTopic+"/slave").c_str(), a.c_str());
  client.publish("esp/espdk001/status", a.c_str());
  delay(200);
}

void alarmSend(){
  //tP(LED);
  a = "";
  JsonObject& data1 = jsonBuffer.createObject();
  vObj["id"] = "espdk001";
  vObj["func"] = 3; 
  data1["i5"] = 0;
  vObj["data"] = data1;
  vObj.printTo(a);
  Serial.println(a);
  //client.publish((gTopic+"/slave").c_str(), a.c_str());
  client.publish("esp/espdk001/status", a.c_str());
  delay(200);
}

void stateChange(int pChange){
  a = "";
  //vObj["id"] = gTopic;
  vObj["id"] = "espdk001";
  vObj["func"] = 4;
  JsonObject& data1 = jsonBuffer.createObject();
  if(((pChange >> 1) & 0x01) == 1){
    Serial.println("change r1");
    data1["r1"] = (inputLastState >> 1) & 0x01;
  }
  else{
    //data1["r1"] = 0;
  }
  if(((pChange >> 2) & 0x01) == 1){
    Serial.println("change r2");
    data1["r2"] = (inputLastState >> 2) & 0x01;
  }
  else{
    //data1["r2"] = 0;
  }
  if(((pChange >> 3) & 0x01) == 1){
    Serial.println("change r3");
    data1["r3"] = (inputLastState >> 3) & 0x01;
  }
  else{
    //data1["r3"] = 0;
  }
  if(((pChange >> 4) & 0x01) == 1){
    Serial.println("change r4");
    data1["r4"] = (inputLastState >> 4) & 0x01;
  }
  else{
    //data1["r4"] = 0;    
  }
  if((pChange & 0x01) == 1){
    Serial.println("change r5");
    data1["r5"] = inputLastState & 0x01;
  }
  else{
    //data1["r5"] = 0;
  }
  vObj["data"] = data1;
  vObj.printTo(a);
  Serial.println(a);
  client.publish("esp/espdk001/status", a.c_str());
  delay(200);
}

int gtimeCount = 0;
void fCheckWdt(){
  gtimeCount ++;
  if (gtimeCount == timeReset){
    Serial.println("reset");
    ESP.restart();
  }
}

void setup() {
    WiFi.setAutoReconnect(true);
  // put your setup code here, to run once:
    initPort();
    ledSetup();
//    initSystem();
//    resetState();
    wifiConnect();
    //init port after bc of using Rx as pinout 
    //initPort();
    topicMacid();
    //sdtLoad();
    // server address, port and URL
    client.setServer(mqtt_server, mqtt_port); 
    client.setCallback(callback);
    reconnect();
    //setup sim
    SIM808_Setup();
    SIMData_Write(5,2);
    SIMData_Read(2,&gSdt);
    //setup input
    GPIO_Setup();// bat buoc phai co, dat trong setup
    GPIOData_Write(1,0.1); //cho Timedelay la 0.01s 
    //dem mot phut
    timer.setInterval(60000,stateSend);  
    //set server time
    setTimeServer();
  
}

void loop() {
  client.loop();
  if(wifiData_Read(1) != 0){
   if(!client.connected()){
    reconnect();
    } 
  }
  
  if(rP(RS) == 1){
    wifiReset();
  }
  checkWifi();
  ledWifi(wifiData_Read(1));
  ledServer(client.connected());
  ledSim(SIMData_Read(1));
  //check INPUT
  int temp = GPIOData_Read(2);// doc GPIO; du lieu sau khi doc GPIO tra ve kieu int gom 5 bit, bit thap nha la Source
  
  if ( (temp & 0x01) == 1){
    alarmFlag = 0;
  }
  else if ( ((temp & 0x01) == 0) && (alarmFlag == 0)){
    alarmFlag = 1;
    delay(1000);
    Serial.println(temp,BIN); 
    alarmSend();
    Serial.print("Alarm");   
    SIM800alert(gSdt,"Power off ");//Em van de ham nhu cu cho linh dong.
  }
  else{
    
  }
  //check sms success
  int  sms = SIMData_Read(5);
  if( sms != 2){
    if ( sms == 1 ){
      Serial.println("da gui");
      SIMData_Write(5,2);
    }
    else if (sms == 0){
      
    }
  }
  if ( inputLastState != temp){
    int aa = inputLastState ^ temp;
    Serial.print("change: ");
    Serial.println(aa, BIN);
    inputLastState = temp;
    stateChange(aa);
  }
  else{
    //timer.run();
  }
}

void wifiReset(){
  delay(1000);
  Serial.println("Reset wifi");
  wifiConfig();
}
void firmwareUpdate(){
//    hP(LEDSYS);
    delay(1000);
    Serial.println("update firmware"); 
  }

void topicMacid(){
   const char s[2] = ":";
   char *token;
   WiFi.macAddress().toCharArray(topic,20);
   /* lay token dau tien */
   token = strtok(topic, s);
   
   /* duyet qua cac token con lai */
   while( token != NULL ) 
   {
      gTopic = gTopic+token;    
      token = strtok(NULL, s);
   }
   Serial.print("mac: ");
   Serial.println(gTopic);
}

void reconnect() {
  // Loop until we're reconnected
  if (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("arduinoClient")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      //client.publish("outTopic","hello world"); 
      // ... and resubscribe
      client.subscribe("esp/espdk001/control");
      //lP(LED_G);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(10);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i=0;i<length;i++) {
    Serial.print((char)payload[i]);     
  }
  Serial.println();
  messParse(payload);
}

void messParse(uint8_t* json){
  JsonObject& parseO = jsonBuffer.parseObject( json );
  if (parseO.success()){
     int a = parseO["func"];
     Serial.println("msg : ");
     Serial.println(a);
     if (a == 0){
      stateSend();
     }
     if (a == 5){
      const char* b = parseO["data"];
      SIMData_Write(2,String(b));
      SIMData_Read(2,&gSdt);
     }
  }
  else{
  }    
}

//void sdtPub(){
//  String vString = "{\"id\":"+ gTopic +",\"func\":\"list\", \"data\":{\"sdt1\":\"" 
//                    + sdt1 + "\",\"sdt2\":\"" + sdt2 + "\",\"sdt3\":\"" + sdt3 + "\"}}";
//  Serial.println(vString);
//  client.publish("ESP32monitor/sdt", vString.c_str());
//}


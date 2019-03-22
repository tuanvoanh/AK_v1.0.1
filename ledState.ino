#include "ledState.h"

void ledSetup(){
  pinMode(wifiR,OUTPUT);
  pinMode(wifiB,OUTPUT);
  pinMode(simR,OUTPUT);
  pinMode(simB,OUTPUT);
  pinMode(serverL,OUTPUT);
  ledStart();
}

void ledWifi(int a){
  if (a == 0){
    digitalWrite(wifiR,0);
    digitalWrite(wifiB,0);
  }
  else if (a == 1){
    digitalWrite(wifiB,0);
    digitalWrite(wifiR,1);  
  }
  else if (a == 2){
    digitalWrite(wifiR,0);
    digitalWrite(wifiB,1);
  }
  else{
    
  }
}
void ledSim(int a){
  if (a == 0){
    digitalWrite(simR,0);
    digitalWrite(simB,0);
  }
  else if (a == 1){
    digitalWrite(simB,0);
    digitalWrite(simR,1);
  }
  else if (a == 2){
    digitalWrite(simR,0);
    digitalWrite(simB,1);
  }
  else{
    
  }
}
void ledServer(int a){
  if(a == 1){
    digitalWrite(serverL,1);
  }
  else 
    digitalWrite(serverL,0);
}

void ledConfig(){
  digitalWrite(wifiR,0);
  digitalWrite(wifiB,0);
  digitalWrite(simR,0);
  digitalWrite(simB,0);
  digitalWrite(serverL,1);
}

void ledStart(){
  digitalWrite(wifiR,1);
  digitalWrite(wifiB,1);
  digitalWrite(simR,1);
  digitalWrite(simB,1);
  digitalWrite(serverL,1);
  delay(100); 
  digitalWrite(wifiR,0);
  digitalWrite(wifiB,0);
  digitalWrite(simR,0);
  digitalWrite(simB,0);
  digitalWrite(serverL,0);
}


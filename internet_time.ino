#include "internet_time.h"

int timezone = 7;
void setTimeServer(){
  configTime(timezone * 3600, 0, "pool.ntp.org", "time.nist.gov");
  Serial.println("\nWaiting for time");
  while (!time(nullptr)) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("");
}

String dateGet(){
  time_t now = time(nullptr);
  char *token = strtok(ctime(&now), " ");
  char *token1 = strtok(NULL, " ");
  char *token2 = strtok(NULL, " ");
  char *token3 = strtok(NULL, " ");
  char *token4 = strtok(NULL, " ");
  
  String vDate = String(token) + "," + String(token1) + "-" + String(token2) + "-" + String(token4);
  return vDate;
}

String timeGet(){
  time_t now = time(nullptr);
  char *token = strtok(ctime(&now), " ");
  char *token1 = strtok(NULL, " ");
  char *token2 = strtok(NULL, " ");
  char *token3 = strtok(NULL, " ");
  char *token4 = strtok(NULL, " ");
  
  String vTime= String(token3);
  return vTime;
}



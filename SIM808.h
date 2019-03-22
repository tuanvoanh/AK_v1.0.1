//#include "SoftwareSerial.h"
#include <stdio.h>
#include <string.h>
#include "EEPROM.h"

//#define DEBUG 1
//#define Rx 16 // D0
//#define Tx 14// D1
void SIM808_Setup();
uint8_t sim_call(String *pSDT);
void SIM800alert(String pSDTSIM, String pContentSIM);
int SIMData_Write(int order, int px);
int SIMData_Read(int order);
void SIMData_Write(int order, String px);
void SIMData_Read(int order, String *pResult);

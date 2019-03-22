#include "GPIO.h"
static int Timedelay = 5; //ms

void _SerialPrint(String pstring){
  int vtemp = 1;
  if(vtemp){
    Serial.println(pstring);
  }
}

void GPIO_Setup(){
  pinMode(I1, INPUT);
  pinMode(I2, INPUT);
  pinMode(I3, INPUT);
  pinMode(I4, INPUT);
  pinMode(ISource, INPUT);
}
void GPIOData_Write(int pA, double pB){
  switch(pA){
    case 1:{
      if(pB<0) break;
      double vtemp = pB*1000;
      Timedelay = vtemp;
      break;
    }
////////////////////
    case 2:

    break;
////////////////////
    case 3:

    break;
////////////////////
    default:
    
    break;
  }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        
int GPIOData_Read(int pA){
    switch(pA){
    case 1:

    break;
////////////////////
    case 2:
    return _GPIORead();
    break;
////////////////////
    case 3:

    break;
////////////////////
    default:
    
    break;
  }
}
int _GPIORead(){
  int __I1 = digitalRead(I1);
  int __I2 = digitalRead(I2);
  int __I3 = digitalRead(I3);
  int __I4 = digitalRead(I4);
  int __IS = digitalRead(ISource);

  delay(Timedelay);
  int _I1 = digitalRead(I1);
  int _I2 = digitalRead(I2);
  int _I3 = digitalRead(I3);
  int _I4 = digitalRead(I4);
  int _IS = digitalRead(ISource);

  if(__I1 != _I1 || __I2 != _I2 || __I3 != _I3 || __I4 != _I4 || __IS != _IS){
    delay(Timedelay);
    int _I1_ = digitalRead(I1);
    int _I2_ = digitalRead(I2);
    int _I3_ = digitalRead(I3);
    int _I4_ = digitalRead(I4);
    int _IS_ = digitalRead(ISource);

    if(__I1 = _I1_) _I1 = __I1;
    else _I1 = _I1_;

    if(__I2 = _I2_) _I2 = __I2;
    else _I2 = _I2_;

    if(__I3 = _I3_) _I3 = __I3;
    else _I3 = _I3_;

    if(__I4 = _I4_) _I4 = __I4;
    else _I4 = _I4_;

    if(__IS = _IS_) _IS = __IS;
    else _IS = _IS_;
  }

  int vResult = _IS + (_I1<<1) + (_I2<<2) + (_I3<<3) + (_I4<<4);
  return vResult;
}


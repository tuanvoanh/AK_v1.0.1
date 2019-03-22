#include "SIM808.h"
#define sim808 Serial2 
#define EEPROM_SIZE 64
static int x = 2; // trang thai cua gui tin nhan, o nho so 5
String Flash_return = "1234567891";

int SIMData_Write(int order, int px){
  switch(order){
    case 1:

    break;
///
    case 2:

    break;
///
    case 3:

    break;
///
    case 4:

    break;
    
///
    case 5:
    // Chua viet khuc ghi x # 1 2 3
      x = px;
    break;
///
    default:

    break;
  }
}



// write string
void SIMData_Write(int order, String px){
  switch(order){
    case 1:

    break;
///
    case 2:
    _Flash_wirte(0,px);
    break;
///
    case 3:
    _Flash_wirte(10,px);
    break;
///
    case 4:
    _Flash_wirte(20,px);
    break;
    
///
    case 5:
    // Chua viet khuc ghi x # 1 2 3
    break;
///
    default:

    break;
  }
}


void SIMData_Read(int order, String *pResult){
   switch(order){
    case 1:
    break;
///
    case 2:
    _Flash_read(0);
    *pResult = Flash_return;
    break;
///
    case 3:
     _Flash_read(10);
    *pResult = Flash_return;
    break;
///
    case 4:
     _Flash_read(20);
    *pResult = Flash_return;
    break;
    
///
    case 5:
    break;
///
    default:

    break;
  }
}

int SIMData_Read(int order){
   switch(order){
    case 1:{
      //return _SIM808_Network();
      return _SIM_Name_Host();
    }
    break;
///
    case 2:
  
    break;
///
    case 3:

    break;
///
    case 4:

    break;
    
///
    case 5:
    // Chua viet khuc ghi x # 1 2 3
      return x;
    break;
///
    default:

    break;
  }
}

void SerialPrint(String pstring){
  int vtemp = 1;
  if(vtemp == 1){
    Serial.println(pstring);
  }
}
void SIM808_Setup(){
  simRate(9600);
  if (!EEPROM.begin(EEPROM_SIZE))
  {
    SerialPrint("failed to initialise EEPROM");
  }
  else
  SerialPrint("Init EEPROM OK");
  /*
  // TEST NETWORK
  SerialPrint("Start test network");
  int pdelete = _SIM808_Network();
  if(pdelete == 0) {
    SerialPrint("Yeu");
  }
  else if(pdelete = 1){
    SerialPrint("Trung binh");
  }
  else if(pdelete = 2){
    SerialPrint("Manh");
  }
  */
  /*
  // tes Read and write EPPROM
  String resulttemp;
  SIMData_Write(2,"0364952123");
  SIMData_Read(2,&resulttemp);
  SerialPrint(resulttemp);
  
  SIMData_Write(3,"0099887766");
  SIMData_Read(3,&resulttemp);
  SerialPrint(resulttemp);
  
  SIMData_Write(4,"0122334455");
  SIMData_Read(4,&resulttemp);
  SerialPrint(resulttemp);
  */
}

void simRate(uint32_t pBaurt)
{
  sim808.begin(pBaurt);
}

uint8_t sim_call(String *pSDT)
{
    // Test call
  at("AT",1000);
  if(sim808.available()){
    SerialPrint(sim808.readString());
  }
  at("ATD"+*pSDT+";",15000);
  at("ATH",1000);
  return 1;
}

uint8_t _sim_sendsms(String pSDT, String pSmsContent)
{
    //test sms
  at("AT",1000);
  at("AT+CMGF=1",1000);
  at("AT+CSCS=\"GSM\"",1000);
  at("AT+CMGS=\"" + pSDT+"\"",2000);
  if(sim808.available()){
    String vx = sim808.readString();
    SerialPrint("Gia tri SIM tra ve truoc khi gui tin nhan la: ");
    SerialPrint(vx);
  }
  at(pSmsContent,1000);
  sim808.write(26);     // ctlrZ
  delay(3000);
  if(sim808.available()){
    String vsimreturn = sim808.readString();
    if(_SIM_OK_Return(vsimreturn)){
      return 1;
    }
  }
  return 0;
}

void SIM800alert(String pSDTSIM, String pContentSIM)
{
    SerialPrint("start SIM800alert");
    if(_sim_sendsms(pSDTSIM,pContentSIM)){
      x = 1;
    }
    else {
      x = 0;
    }
   SerialPrint("end alert");
}

void at(String _atcm,unsigned long _dl){
  sim808.print(_atcm+"\r\n");
  delay(_dl);
}
int _SIM_OK_Return(String pstring){
  for(int i = 0; i < pstring.length() - 1; ++i){
  if(pstring[i] == 'O' && pstring[i+1] == 'K'){
    return 1;
    }
  }
  return 0;
}

int _SIM_Name_Host(){
  /*
  //_SIM808_Network();
  test2("AT+COPS?");
  // AT+CGREG?
  //AT+COPS? : Kiểm tra tên nhà mạng --> length = 40 (27 là không có nhà mạng) --> Khong có tên thì khỏi kiểm tra sóng
  //AT+CPIN? Tim SIM --> length = 31 --> Không có sim cũng return luôn (AT+CPIN? ERROR --> length = 18
  test2("AT+CPIN?");
  _SIM808_Network();
  */
  if(sim808.available()){
    String temppp = sim808.readString();
  }
   at("AT+COPS?",1000);
    if(sim808.available()){
      String psimreturn = sim808.readString();
      SerialPrint("sim return is: ");
      SerialPrint(psimreturn);
      if(psimreturn.length() == 27){
        return 0;
      }
      else{
        return 1;
      }
      //Serial.println(psimreturn.length());
    }
   else{
    SerialPrint("Error");
    return 0;
   }
   return 0;
}
void test2(String x){
  at(x,1000);
    if(sim808.available()){
      String psimreturn = sim808.readString();
      SerialPrint("sim return is: ");
      SerialPrint(psimreturn);
      Serial.println(psimreturn.length());
    }
   else{
    SerialPrint("Error");
   }
}
int _SIM808_Network(){
  String psimreturn = "";
  if(sim808.available()){
    String vdelete = sim808.readString();
  }
    at("AT+CSQ",1000);
    if(sim808.available()){
      psimreturn = sim808.readString();
      SerialPrint("sim return is: ");
      SerialPrint(psimreturn);
    }
   else{
    SerialPrint("Error");
    return 0;
   }
   if(_SIM_OK_Return(psimreturn)){
     int vsignal = _SIM_Nework_separate(psimreturn);
     if(vsignal < 10)
     return 0;
     else if(10 <= vsignal && vsignal < 20)
     return 1;
     else if(20 <= vsignal && vsignal <= 31)
     return 2;
     else return 0;
   }
   else {
    return 0;
   }
   return 0;
}

int _SIM_Nework_separate(String pstring){
  String vresult = "0000";
  int haicham = 0;
  int phay = 0;
  double vreturn = 0;
  
  for(int i = 0; i< pstring.length(); ++i){
    if(pstring[i] ==':'){
      haicham = i;
//      SerialPrint("vi tri dau hai cham la: ");
//      Serial.println(haicham);
//      SerialPrint("Co ;");
//      vresult[0] = pstring[i+2];
//      vresult[1] = pstring[i+3];
//      vresult[2] = pstring[i+4];
//      vresult[2] = pstring[i+5];
    }
    if(pstring[i] == ','){
      phay = i;
//      SerialPrint("vi tri dau phay la: ");
//      Serial.println(phay);
    }
  }
  if(phay!=0 && haicham != 0)
  for(int i = haicham + 1; i <= phay + 1; ++i){
    vresult[i - haicham -1] = pstring[i];
  }
  
  vreturn = vresult.toFloat();
  int intreturn = vreturn;
  return intreturn;
}

uint8_t _Flash_wirte(int pPosition, String pstring){ 
  
  if(pstring[0] != '0' || pstring.length()!= 10){
    return 0;
  }
  for(int i = pPosition; i<10 + pPosition ;i++){
    EEPROM.write(i, pstring[i - pPosition]);
//    SerialPrint("dang viet");
  }
  EEPROM.commit();
  return 1;
}

uint8_t _Flash_read(int pPosition){
  for(int i = pPosition; i < pPosition + 10; ++i){
//    SerialPrint("Dang doc");
    Flash_return[i - pPosition] = EEPROM.read(i);
  }
}



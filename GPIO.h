#define I1  34 // input motor1
#define I2  35 // input motor2
#define I3  32 //input motor3
#define I4  33 //input motor4
#define ISource  25 // input check alert

void GPIO_Setup();
void GPIOData_Write(int pA, double pB);
int GPIOData_Read(int pA);

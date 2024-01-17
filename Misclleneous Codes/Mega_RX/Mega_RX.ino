#include <EasyTransfer.h>
#include <PS3BT.h>
#include <usbhub.h>
#include <Sabertooth.h>
#include <SoftwareSerial.h>

//create object
EasyTransfer ET; 

struct RECEIVE_DATA_STRUCTURE{
  int enc0;
  int enc1;
  int enc2;
  int enc3;
};


SoftwareSerial SWSerial(NOT_A_PIN, 11);
Sabertooth ST1(128, SWSerial);
Sabertooth ST2(129, SWSerial);

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

USB Usb;
//USBHub Hub1(&Usb); // Some dongles have a hub inside

BTD Btd(&Usb); // You have to create the Bluetooth Dongle instance like so
/* You can create the instance of the class in two ways */
PS3BT PS3(&Btd); // This will just create the instance
//PS3BT PS3(&Btd, 0x00, 0x15, 0x83, 0x3D, 0x0A, 0x57); // This will also store the bluetooth address - this can be obtained from the dongle when running the sketch

bool printTemperature, printAngle;

long prevT= 0;
int i=0;
int posPrev[3] = {0};
float v1Filt[3]= {0};
float v1Prev[3]= {0};
float eintegral[3] = {0};
//volatile int pos_i[3] = {0};
int pos_i[3] = {0};
float error1[10]={0};
float error2[10]={0};
float error3[10]={0};
float error4[10]={0};

float kp = 3.5;
float ki = 10;
float kd = 1500;


//give a name to the group of data
RECEIVE_DATA_STRUCTURE mydata;


void setup(){
  Serial.begin(9600);
  //start the library, pass in the data details and the name of the serial port. Can be Serial, Serial1, Serial2, etc. 
  ET.begin(details(mydata), &Serial);
  
  SWSerial.begin(9600);

  ST1.setBaudRate(9600);
  ST2.setBaudRate(9600);
  SWSerial.end();


  SWSerial.begin(9600);

  // Serial.begin(115200);
  //Serial.begin(9600);
  Serial.println("Before bluetooth!!");
#if !defined(MIPSEL)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print(F("\r\nPS3 Bluetooth Library Started"));

}

void loop(){
  //check and see if a data packet has come in.
  v1Filt[0]=mydata.enc0;
  v1Filt[1]=mydata.enc1;
  v1Filt[2]=mydata.enc2;
  v1Filt[3]=mydata.enc3;
  if(ET.receiveData()){
    //this is how you access the variables. [name of the group].[variable name]
    //since we have data, we will blink it out. 
    Serial.println("Data Received");
  }
  Serial.println("In side loop");

  Usb.Task();
  
  int S1 = 0;
  int S2 = 0; 
  int S3 = 0;
  int S4 = 0;
  if (PS3.PS3Connected || PS3.PS3NavigationConnected) { 
    if (PS3.getAnalogHat(LeftHatX) > 137 || PS3.getAnalogHat(LeftHatX) < 117 || PS3.getAnalogHat(LeftHatY) > 137 || PS3.getAnalogHat(LeftHatY) < 117 || PS3.getAnalogHat(RightHatX) > 137 || PS3.getAnalogHat(RightHatX) < 117 || PS3.getAnalogHat(RightHatY) > 137 || PS3.getAnalogHat(RightHatY) < 117) {
      int x = 2*((PS3.getAnalogHat(LeftHatX)-130));
      int y = 2*(129 - (PS3.getAnalogHat(LeftHatY))); 
      if(x<-255)
      {
        x = -255;
      }
      if(x>255)
      {
        x = 255;
      }
      if(y<-255)
      {
        y = -255;
      }
      if(y>255)
      {
        y = 255;
      }
      if(x<50 and x>-50)
      {
        x = 0;
      }
      if(y<50 and y>-50)
      {
        y = 0;
      }

      int s1 = (-0.7071*x + 0.7071*y)*0.7352;
      int s2 = (-0.7071*x - 0.7071*y)*0.7352;
      int s3 = (0.7071*x - 0.7071*y)*0.7352;
      int s4 = (0.7071*x + 0.7071*y)*0.7352;    
      
      // Serial.print(F("\r\ns1: "));
      // // Serial.print(s1);
      // Serial.print(F("\ts2: "));
      // Serial.print(s2);
      // Serial.print(F("\ts3: "));
      // Serial.print(s3);
      // Serial.print(F("\ts4: "));
      // Serial.print(s4);
      // Serial.print(F("\tx: "));
      // Serial.print(x);
      // Serial.print(F("\ty: "));
      // Serial.print(y);

      S1=map(s1, -255, 255, -127, 127);
      S2=map(s2, -255, 255, -127, 127);
      S3=map(s3, -255, 255, -127, 127);
      S4=map(s4, -255, 255, -127, 127);
      
      // Serial.print(F("\r\nS1: "));
      // Serial.print(S1);
      // Serial.print(F("\r\nS2: "));
      // Serial.print(S2);
      // Serial.print(F("\r\nS3: "));
      // Serial.print(S3);
      // Serial.print(F("\r\nS4: "));
      // Serial.print(S4);

    
    }

    if(PS3.getButtonPress(CIRCLE)){
         S4 = -100;
         S3 = 100;
         S2 = -100;
         S1 = 100;
    }
      

    }
    long currT = micros();
    float deltaT = ((float) (currT-prevT))/1.0e6;
    prevT = currT;
    PID_control(S1,S2,S3,S4,deltaT);
    Serial.println("calling PID");
  }


void PID_control(int S1,int S2,int S3,int S4,float deltaT)
{ 
  //rpmcalc1(deltaT);
  float e1 = S1-v1Filt[0];
  // Serial.println();
  eintegral[0] = eintegral[0] + e1*deltaT;
  float u1 = kp*e1 + ki*eintegral[0] - kd*e1*deltaT;
  //Serial.println(u1);
  delay(1000);
  //rpmcalc2(deltaT);
  float e2 = S2-v1Filt[1];
  eintegral[1] = eintegral[1] + e2*deltaT;
  float u2 = kp*e2 + ki*eintegral[1] - kd*e2*deltaT;
  //Serial.println(u2);
  delay(1000);
  //rpmcalc3(deltaT);
  float e3 = S3-v1Filt[2];
  eintegral[2] = eintegral[2] + e3*deltaT;
  float u3 = kp*e3 + ki*eintegral[2] - kd*e3*deltaT;
  //Serial.println(u3);
  delay(1000);
  //rpmcalc4(deltaT);
  float e4 = S4-v1Filt[3];
  eintegral[3] = eintegral[3] + e4*deltaT;
  float u4 = kp*e4 + ki*eintegral[3] - kd*e4*deltaT;
  //Serial.println(u4);
  delay(1000);
  

  ST1.motor(1, S2);  
  ST1.motor(2, S3);    
  ST2.motor(1, S4); 
  ST2.motor(2, S1); 

  if(i>9)
  i=0;

  error1[i]=e1;
  error2[i]=e2;
  error3[i]=e3;
  error4[i]=e4;
  i++;
}

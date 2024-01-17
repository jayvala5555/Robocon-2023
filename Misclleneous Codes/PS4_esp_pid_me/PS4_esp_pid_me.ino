#include <PS4Controller.h>
#include <EasyTransfer.h>

#define EsptoDue Serial2

int X,Y,Z,W = 0;

EasyTransfer ED;

struct senddata{
  int16_t x;
  int16_t y;  
  int16_t w;
  int16_t z;
};

senddata psdata;

void setup() {
  Serial.begin(9600);
  EsptoDue.begin(9600,SERIAL_8N1,16,17);
  ED.begin(details(psdata),&EsptoDue);
  PS4.begin("e0:d4:e8:bd:e6:0a");
  Serial.println("Ready.");

// 4c:d5:77:df:cf:64 
}

void loop() {
  // Below has all accessible outputs from the controller
  if (PS4.isConnected()) {
    X = PS4.data.analog.stick.lx;
    Y = PS4.data.analog.stick.ly;
    W = PS4.data.analog.button.l2;
    Z = PS4.data.analog.button.r2;
    // Serial.print(X);
    // Serial.print(" ");
    // Serial.println(Y);
  }
  psdata.x=map(X,-128,128,0,255);
  psdata.y=map(Y,-128,128,0,255);
  psdata.w=W;
  psdata.z=Z;
  ED.sendData(); 
  Serial.print(psdata.x);
  Serial.print(" ");    
  Serial.print(psdata.y); 
  Serial.print(" ");    
  Serial.print(psdata.w); 
  Serial.print(" ");    
  Serial.println(psdata.z);    
  
  delay(20);
}

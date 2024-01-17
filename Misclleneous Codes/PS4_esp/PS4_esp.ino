#include <PS4Controller.h>
#include <EasyTransfer.h>

#define EsptoDue Serial2

int X,Y = 0;

EasyTransfer ED;

struct senddata{
  int16_t x;
  int16_t y;  
};

senddata psdata;

void setup() {
  Serial.begin(9600);
  EsptoDue.begin(9600,SERIAL_8N1,16,17);
  ED.begin(details(psdata),&EsptoDue);
  PS4.begin("94:e6:86:38:03:2a");
  Serial.println("Ready.");
}

void loop() {
  // Below has all accessible outputs from the controller
  if (PS4.isConnected()) {
    X = PS4.data.analog.stick.lx;
    Y = PS4.data.analog.stick.ly;
    // Serial.print(X);
    // Serial.print(" ");
    // Serial.println(Y);
  }
  psdata.x=map(X,-128,128,0,255);
  psdata.y=map(Y,-128,128,0,255);
  ED.sendData();  





































































































































































  
  Serial.print(psdata.x);
  Serial.print(" ");    
  Serial.println(psdata.y);    
  
  delay(50);
}

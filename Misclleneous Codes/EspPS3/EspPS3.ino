#include <Ps3Controller.h>
#include <EasyTransfer.h>

#define MegatoDue Serial2
//create object
EasyTransfer ET;
int X,Y,Z,W = 0;
struct SEND_DATA_STRUCTURE{
  //put your variable definitions here for the data you want to send
  //THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO
  int16_t x;
  int16_t y;
  int16_t w;
  int16_t z;
};

//give a name to the group of data
SEND_DATA_STRUCTURE data;

void setup(){
  Serial.begin(9600);
  MegatoDue.begin(9600, SERIAL_8N1, 16, 17);
  ET.begin(details(data), &MegatoDue);
  Ps3.begin("00:1a:7d:da:71:10");
  Serial.println("Ready.");
  
}

void loop(){

  if(Ps3.isConnected()){
    X= Ps3.data.analog.stick.lx;
    Y = -Ps3.data.analog.stick.ly; 
    W = Ps3.data.analog.button.triangle;
    Z = Ps3.data.analog.button.cross;  
    Serial.print(data.x);
    Serial.print(" ");    
    Serial.print(data.y);
    Serial.print(" ");    
    Serial.print(W);
    Serial.print(" ");    
    Serial.println(Z);
//    Serial.println(X);
//    Serial.println(Y);
    }
  data.x=map(X,-127,127,0,255);
  data.y=map(Y,-127,127,0,255);
  data.w=W;
  data.z=Z;    
  ET.sendData();
  delay(20);
}

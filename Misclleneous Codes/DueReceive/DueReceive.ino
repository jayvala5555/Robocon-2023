#include <EasyTransfer.h>

//create object
EasyTransfer MegatoDue; 

struct RECEIVE_DATA_STRUCTURE{
  //put your variable definitions here for the data you want to receive
  //THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO
  int16_t xHat;
  int16_t yHat;
};

#define Upperlowerserial Serial2

//give a name to the group of data
RECEIVE_DATA_STRUCTURE PS4DataMega;

void setup(){
  Serial.begin(9600);
  Upperlowerserial.begin(9600);
  //start the library, pass in the data details and the name of the serial port. Can be Serial, Serial1, Serial2, etc. 
  MegatoDue.begin(details(PS4DataMega), &Upperlowerserial);
  
  
  
}

void loop(){
  //check and see if a data packet has come in. 
  if(MegatoDue.receiveData()){
    //this is how you access the variables. [name of the group].[variable name]
    //since we have data, we will blink it out. 
    Serial.print(PS4DataMega.xHat);
    Serial.print(" ");
    Serial.println(PS4DataMega.yHat);
    }
  
  
  //you should make this delay shorter then your transmit delay or else messages could be lost
  delay(2);
}

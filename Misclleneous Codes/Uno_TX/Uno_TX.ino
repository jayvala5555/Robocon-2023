#include <EasyTransfer.h>

//create object
EasyTransfer ET; 

int posPrev[3] = {0};
float v1Filt[3]= {0};
float v1Prev[3]= {0};
int pos_i[3] = {0};

struct SEND_DATA_STRUCTURE{
  int enc0;
  int enc1;
  int enc2;
  int enc3;
};
#define ENC1A 2
#define ENC1B 3
#define ENC2A 4
#define ENC2B 5
#define ENC3A 6
#define ENC3B 7
#define ENC4A 8
#define ENC4B 9


//give a name to the group of data
SEND_DATA_STRUCTURE mydata;

void setup(){
  Serial.begin(9600);
  //start the library, pass in the data details and the name of the serial port. Can be Serial, Serial1, Serial2, etc.
  ET.begin(details(mydata), &Serial);
  randomSeed(analogRead(0));
  
  pinMode(ENC1A,INPUT);
  pinMode(ENC1B,INPUT);
  pinMode(ENC2A,INPUT);
  pinMode(ENC2B,INPUT);
  pinMode(ENC3A,INPUT);
  pinMode(ENC3B,INPUT);
  pinMode(ENC4A,INPUT);
  pinMode(ENC4B,INPUT);

  Serial.println("Before Interrupt!!");
  attachInterrupt(digitalPinToInterrupt(ENC1A),readEncoder1,RISING); 
  attachInterrupt(digitalPinToInterrupt(ENC2A),readEncoder2,RISING); 
  attachInterrupt(digitalPinToInterrupt(ENC3A),readEncoder3,RISING); 
  attachInterrupt(digitalPinToInterrupt(ENC4A),readEncoder4,RISING);
  Serial.println("After Interrupt!!");

  
}

void loop(){
  //this is how you access the variables. [name of the group].[variable name]
  //send the data
  ET.sendData();
  
}


void rpmcalc1(float deltaT)
{
  // read the position and velocity
  int pos = 0;
  noInterrupts(); // disable interrupts temporarily while reading
  pos = pos_i[0];
  interrupts(); // turn interrupts back on

  // Compute velocity with method 1
  //Serial.println(pos_i[0]);
  float velocity1 = (pos - posPrev[0])/deltaT;
  posPrev[0] = pos;
  

  // Convert count/s to RPM
  float v1 = velocity1/144.0*60.0;
  //Serial.println(v1);
  // Low-pass filter (25 Hz cutoff)
  v1Filt[0] = 0.854*v1Filt[0] + 0.0728*v1 + 0.0728*v1Prev[0];
  v1Prev[0] = v1;
  mydata.enc0 = v1Filt[0]; 
}

void rpmcalc2(float deltaT)
{
  // read the position and velocity
  int pos = 0;
  noInterrupts(); // disable interrupts temporarily while reading
  pos = pos_i[1];
  interrupts(); // turn interrupts back on

  // Compute velocity with method 1
  //Serial.println(pos_i[1]);
  float velocity1 = (pos - posPrev[1])/deltaT;
  posPrev[1] = pos;
  

  // Convert count/s to RPM
  float v1 = velocity1/144.0*60.0;
  //Serial.println(v1);
  // Low-pass filter (25 Hz cutoff)
  v1Filt[1] = 0.854*v1Filt[1] + 0.0728*v1 + 0.0728*v1Prev[1];
  v1Prev[1] = v1;
  mydata.enc1 = v1Filt[1]; 
}

void rpmcalc3(float deltaT)
{
  // read the position and velocity
  int pos = 0;
  noInterrupts(); // disable interrupts temporarily while reading
  pos = pos_i[2];
  interrupts(); // turn interrupts back on
  //Serial.println(pos_i[2]);
  // Compute velocity with method 1
  
  float velocity1 = (pos - posPrev[2])/deltaT;
  posPrev[2] = pos;
  

  // Convert count/s to RPM
  float v1 = velocity1/144.0*60.0;
  //Serial.println(v1);
  // Low-pass filter (25 Hz cutoff)
  v1Filt[2] = 0.854*v1Filt[2] + 0.0728*v1 + 0.0728*v1Prev[2];
  v1Prev[2] = v1;
  mydata.enc2 = v1Filt[2]; 
  
}

void rpmcalc4(float deltaT)
{
  // read the position and velocity
  int pos = 0;
  noInterrupts(); // disable interrupts temporarily while reading
  pos = pos_i[3];
  interrupts(); // turn interrupts back on
  //Serial.println(pos_i[3]);
  // Compute velocity with method 1
  
  float velocity1 = (pos - posPrev[3])/deltaT;
  posPrev[3] = pos;
  

  // Convert count/s to RPM
  float v1 = velocity1/144.0*60.0;
  //Serial.println(v1);
  // Low-pass filter (25 Hz cutoff)
  v1Filt[3] = 0.854*v1Filt[3] + 0.0728*v1 + 0.0728*v1Prev[3];
  v1Prev[3] = v1;
  mydata.enc3 = v1Filt[3]; 
 
}
  
void readEncoder1(){
  // Read encoder B when ENCA rises
  int b = digitalRead(ENC1B);
  int increment = 0;
  if(b>0){
    // If B is high, increment forward
    increment = 1;
  }
  else{
    // Otherwise, increment backward
    increment = -1;
  }
 pos_i[0] = pos_i[0] + increment;
}

void readEncoder2(){
  // Read encoder B when ENCA rises
  int b = digitalRead(ENC2B);
  int increment = 0;
  if(b>0){
    // If B is high, increment forward
    increment = 1;
  }
  else{
    // Otherwise, increment backward
    increment = -1;
  }
  pos_i[1] = pos_i[1] + increment;
}

void readEncoder3(){
  // Read encoder B when ENCA rises
  int b = digitalRead(ENC3B);
  int increment = 0;
  if(b>0){
    // If B is high, increment forward
    increment = 1;
  }
  else{
    // Otherwise, increment backward
    increment = -1;
  }
  pos_i[2] = pos_i[2] + increment;
}

void readEncoder4(){
  // Read encoder B when ENCA rises
  int b = digitalRead(ENC4B);
  int increment = 0;
  if(b>0){
    // If B is high, increment forward
    increment = 1;
  }
  else{
    // Otherwise, increment backward
    increment = -1;
  }
  pos_i[3] = pos_i[3] + increment;
}

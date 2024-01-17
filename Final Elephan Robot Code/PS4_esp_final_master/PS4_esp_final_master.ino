#include <PS4Controller.h>
#include <EasyTransfer.h>
#include <Wire.h>
#include <Adafruit_MCP4725.h>

#define EsptoDue Serial
//---------------
#define esptoesp Serial2  //Check carefully
//---------------

Adafruit_MCP4725 DAC;

#define DAC_RESOLUTION 4095

int X,Y,Z,W,up,down = 0;
int maxvol = 0;
EasyTransfer ET;
//-------------------
EasyTransfer ET1;
//-------------------


struct sendduedata{
  int16_t x;
  int16_t y;  
  int16_t w;
  int16_t z;
  int16_t pickingup;
  int16_t pickingdown;
};


//--------------------
struct send_upper_data {
  //put your variable definitions here for the data you want to send
  //THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO
  int16_t servoUp;
  int16_t servoDown;
  int16_t actdown;
  int16_t actup;
  int16_t fiddingmotor;
  int16_t pencilnumeticsclose;
  int16_t pencilnumeticsopen;
  int16_t throwingnumetics1;
};

sendduedata psdata;
send_upper_data psdata1;
//-------------------

void func(){

  //  big servo up
  if (PS4.Triangle()){
      psdata1.servoDown = 1;
      psdata.pickingup=1;
      // Serial.println(psdata1.servoUp);
   }else{
      psdata1.servoDown = 0;
      psdata.pickingdown=0;
   }

  //  big servo down
   if (PS4.Cross()){
      psdata1.servoUp = 1;
      psdata.pickingdown=1;
   }else{
      psdata1.servoUp = 0;
      psdata.pickingdown=0;      
   }

  //  small servo up-down
  if (PS4.Square()){
       psdata1.fiddingmotor = 1;
        delay(200);
          
  }else{
    psdata1.fiddingmotor = 0;
   }


  if (PS4.Circle()){
    psdata1.throwingnumetics1 = true; 
    delay(200);
      
  }else{
    psdata1.throwingnumetics1 = false;
   }
//  actuatorup

  if (PS4.L1()){
    psdata1.actup = 1;
  }
  else{
    psdata1.actup = 0;
  }

//  actuatordown

  if (PS4.R1()){
    psdata1.actdown = 1;
  }
  else{
    psdata1.actdown = 0;
  }
  

//pencilnumeticsopen

  if (PS4.Right()){
      psdata1.pencilnumeticsopen = 1;
      } 
  else {
      psdata1.pencilnumeticsopen = 0;
  }

  //pencilnumeticsclose

  if (PS4.Left()){
      psdata1.pencilnumeticsclose = 1;
      } 
  else {
      psdata1.pencilnumeticsclose = 0;
  }

  if (PS4.Up() >= 1){
      maxvol = maxvol + 100;
      if(maxvol>=4095){
        maxvol=4095;
      }    
      Serial.println(maxvol);
      DAC.setVoltage(maxvol,false);
      } 
  
  if (PS4.Down() >= 1){
      maxvol = maxvol - 100;
      if(maxvol<=0){
        maxvol = 0;
      }
      Serial.println(maxvol);    
      DAC.setVoltage(maxvol,false);
    } 

/*Still left to use: 

      
    if (PS4.Down()) Serial.println("Down Button");
    if (PS4.Up()) Serial.println("Up Button");
    if (PS4.Circle()) Serial.println("Circle Button");
    if (PS4.UpRight()) Serial.println("Up Right");
    if (PS4.DownRight()) Serial.println("Down Right");
    if (PS4.UpLeft()) Serial.println("Up Left");
    if (PS4.DownLeft()) Serial.println("Down Left");
    if (PS4.Share()) Serial.println("Share Button");
    if (PS4.Options()) Serial.println("Options Button");
    if (PS4.L3()) Serial.println("L3 Button");
    if (PS4.R3()) Serial.println("R3 Button");

    if (PS4.PSButton()) Serial.println("PS Button");
    if (PS4.Touchpad()) Serial.println("Touch Pad Button");
    */

}

void setup() {
  // Serial.begin(9600);
  esptoesp.begin(9600, SERIAL_8N1, 16, 17);             //For esp to esp
  EsptoDue.begin(9600, SERIAL_8N1, 3, 1);
  ET.begin(details(psdata),&EsptoDue);
  ET1.begin(details(psdata1), &esptoesp);
  PS4.begin("4c:d5:77:df:cf:64");
  DAC.begin(0x60); 
  Serial.println("Ready.");
  // delay(500);
}

void loop() {
  // Below has all accessible outputs from the controller
  if (PS4.isConnected()) {
    X = PS4.data.analog.stick.lx;
    Y = PS4.data.analog.stick.ly;
    W = PS4.data.analog.button.l2;
    Z = PS4.data.analog.button.r2;
    up = PS4.Cross();
    down = PS4.Triangle();
    func();
//     Serial.print(X);
//     Serial.print(" ");
//     Serial.println(Y);
  }
  psdata.x=map(X,-128,128,0,255);
  psdata.y=map(Y,-128,128,0,255);
  psdata.w=W;
  psdata.z=Z;
  psdata.pickingup = up;
  psdata.pickingdown = down;
  ET.sendData(); 
  ET1.sendData(); 
    // Serial.print("master data");
    // Serial.print(" ");
    //  Serial.print(psdata.x);
    //  Serial.print(" ");    
    //  Serial.print(psdata.y); 
    //  Serial.print(" ");    
    //  Serial.print(psdata.w); 
    //  Serial.print(" ");    
    //  Serial.print(psdata.z);
    //  Serial.print(" ");    
    // Serial.print(psdata1.servoUp);
    // Serial.print(" ");    
    // Serial.print(psdata1.servoDown);
    // Serial.print(" ");
    // Serial.print(psdata1.actdown);
    // Serial.print(" ");
    // Serial.print(psdata1.actup);
    // Serial.print(" ");
    // Serial.print(psdata1.fiddingmotor);
    // Serial.print(" ");
    // Serial.print(psdata1.pencilnumeticsclose);
    // Serial.print(" ");
    // Serial.print(psdata1.pencilnumeticsopen);
    // Serial.print(" ");
    // Serial.print(psdata1.throwingnumetics1);
    // Serial.println(" "); 
     
  
  delay(50);
}

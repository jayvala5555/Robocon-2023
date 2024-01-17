


#include <EasyTransfer.h>
#include <ESP32_Servo.h>

// #include <Wire.h>
// #include <Adafruit_MCP4725.h>

#define esptoesp Serial2

#define actuator_dir 5
#define actuator_pwm 4
// #define pencilneuOpen 12
// #define pencilneuClose 14
#define pencilneuOpen 22
#define pencilneuClose 23
// #define numeticks1 27
// #define numeticks2 22
// #define numeticks3 23
// #define pencilneuOpen 12
// #define pencilneuClose 14
#define numeticks1 12
#define numeticks2 14
#define numeticks3 2

const int freq = 30000;
const int resolution = 8;
int pickingDir = 19; 
int pickingPWM = 18;
const int pwmChannel = 0;



// Adafruit_MCP4725 DAC;

// #define DAC_RESOLUTION 4095

Servo myservo2;
Servo myservo3;
Servo serv;
//create object
EasyTransfer ET1;
int count, count1, count2, pencilnumeticsopen, pencilnumeticsclose, servoup, servodown, actuatorup, actuatordown, numeticsthrow1, fiddingmotor = 0;
int maxvol = 0;
struct RECEIVE_DATA_STRUCTURE {
  //put your variable definitions here for the data you want to receive
  //THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO
  int16_t servoUp;
  int16_t servoDown;
  int16_t actdown;
  int16_t actup;
  int16_t fiddingMotor;
  int16_t pencilnumeticsclose;
  int16_t pencilnumeticsopen; 
  int16_t throwingnumetics1;
};

//give a name to the group of data
RECEIVE_DATA_STRUCTURE psdata1;

void setup() {
  Serial.begin(9600);
  //start the library, pass in the data details and the name of the serial port. Can be Serial, Serial1, Serial2, etc.
  esptoesp.begin(9600, SERIAL_8N1, 16, 17);
  ET1.begin(details(psdata1), &esptoesp);
  // DAC.begin(0x60);

  ledcSetup(pwmChannel, freq, resolution);

  serv.attach(26, 500, 2500);
  myservo3.attach(25, 500, 2500);
  pinMode(actuator_dir, OUTPUT);
  pinMode(actuator_pwm, OUTPUT);
  pinMode(pencilneuOpen, OUTPUT);
  pinMode(pencilneuClose, OUTPUT);
  pinMode(numeticks2, OUTPUT);
  pinMode(numeticks3, OUTPUT);
  pinMode(numeticks1, OUTPUT);
  pinMode(pickingDir, OUTPUT);
  pinMode(pickingPWM, OUTPUT);

  ledcSetup(pwmChannel, freq, resolution);
  ledcAttachPin(pickingPWM, pwmChannel);
  Serial.println("setup ");
}

void loop() {
  //check and see if a data packet has come in.
  if (ET1.receiveData()) {
    //this is how you access the variables. [name of the group].[variable name]
    //since we have data, we will blink it out.
    // Serial.println("receive ");
    servoup = psdata1.servoUp;
    servodown = psdata1.servoDown;
    actuatorup = psdata1.actup;
    actuatordown = psdata1.actdown;
    pencilnumeticsopen = psdata1.pencilnumeticsopen;
    pencilnumeticsclose = psdata1.pencilnumeticsclose;
    numeticsthrow1 = psdata1.throwingnumetics1;
    fiddingmotor = psdata1.fiddingMotor;


    Serial.print("slave data");
    Serial.print(" ");
    Serial.print(servoup);
    Serial.print(" ");
    Serial.print(servodown);
    Serial.print(" ");
    Serial.print(actuatorup);
    Serial.print(" ");
    Serial.print(actuatordown);
    Serial.print(" ");
    Serial.print(pencilnumeticsopen);
    Serial.print(" ");
    Serial.print(pencilnumeticsclose);
    Serial.print(" ");
    Serial.print(numeticsthrow1);
    Serial.print(" ");
    Serial.println(fiddingmotor);
  }


  //Linear  Actuators
  if (actuatorup > 0 && actuatorup <= 255) {
    digitalWrite(actuator_dir, HIGH);
    digitalWrite(actuator_pwm, HIGH);
    delay(50);
    Serial.println("Up");
  } else {
    digitalWrite(actuator_dir, LOW);
    digitalWrite(actuator_pwm, LOW);
  }
  if (actuatordown > 0 && actuatordown <= 255) {
    digitalWrite(actuator_dir, LOW);
    digitalWrite(actuator_pwm, HIGH);

  } else {
    digitalWrite(actuator_dir, LOW);
    digitalWrite(actuator_pwm, LOW);
  }

  //BigServo Picking
if(servoup>0 || servodown>0){
  if (servoup > 0) {
    Serial.print("gygt11");
    // digitalWrite(pickingDir, LOW);
    // ledcWrite(pwmChannel, 255);

      digitalWrite(pickingDir, HIGH);
  // digitalWrite(motor1Pin2, LOW);
     ledcWrite(pwmChannel, 150);
  }

  if (servodown > 0) {
    Serial.print("g9ygt");
    // digitalWrite(pickingDir, HIGH);
    // ledcWrite(pwmChannel, 255);
     digitalWrite(pickingDir, LOW);
  // digitalWrite(motor1Pin2, LOW);
    ledcWrite(pwmChannel, 150);
  }
  }else{
// for(int i = 100;i>0;i--){
  ledcWrite(pwmChannel, 0);
  // i= i-4;
// }    
        
  }

  //  small servo
  if (fiddingmotor >= 1 && count2 == 0) {
    // Serial.write("xaa");
    for (int i = 0; i < 100; i=i+2) {
      // Serial.println("xaa");
      serv.write(i+2);
      myservo3.write(i);
      delay(10);
    }
    count2 = 1;

  } else if (fiddingmotor >= 1 && count2 == 1) {
    for (int i = 0; i < 100; i=i+2) {

      serv.write(102 - i);
      myservo3.write(100 - i);
      delay(10);
    }
    count2 = 0;
  }

  // if(PPRincrease>=1)
  // {
  //   maxvol = maxvol + 0.1*(4095/5);
  //   if(maxvol>=4095){
  //     maxvol = 4095;}
  //   DAC.setVoltage(maxvol,false);
  // }

  // if(PPRincrease>=1)
  // {
  //   maxvol = maxvol - 0.1*(4095/5);
  //   if(maxvol<=0){
  //     maxvol = 0;}
  //   DAC.setVoltage(maxvol,false);
  // }

  if (pencilnumeticsclose >= 1 && count1 == 0) {
    digitalWrite(pencilneuClose, HIGH);
    delay(500);
    digitalWrite(pencilneuClose, LOW);
    delay(1000);

    count1 = 1;
  }
  if (pencilnumeticsopen >= 1 && count1 == 1) {
    digitalWrite(pencilneuOpen, HIGH);
    delay(500);
    digitalWrite(pencilneuOpen, LOW);

    count1 = 0;
  }
  if (numeticsthrow1 >= 1) {
    digitalWrite(numeticks1, HIGH);
    delay(500);
    digitalWrite(numeticks1, LOW);
    delay(500);
    digitalWrite(numeticks2, HIGH);
    delay(500);
    digitalWrite(numeticks2, LOW);
    delay(500);
    digitalWrite(numeticks3, HIGH);
    delay(500);
    digitalWrite(numeticks3, LOW);
    delay(500);

  } else {
    digitalWrite(numeticks1, LOW);
    digitalWrite(numeticks2, LOW);
    digitalWrite(numeticks3, LOW);
  }



  //you should make this delay shorter then your transmit delay or else messages could be lost
  //delay(2);
}

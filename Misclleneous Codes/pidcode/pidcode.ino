#include <PS3BT.h>
#include <usbhub.h>

#include <SPI.h>
#include <Sabertooth.h>
#include <SoftwareSerial.h>
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif

SoftwareSerial SWSerial(NOT_A_PIN, 30 );
Sabertooth ST(129, SWSerial);   //1st motor driver
Sabertooth ST1(128, SWSerial); //2nd motor driver

//Declaring motor speeds for the 4 motors
int S1,S2,S3,S4;

// Motor encoder output pulses per 360 degree revolution (measured manually)
#define qsize 10
#define ENC_COUNT 324
#define ENC_IN_RIGHT_A 19 //SW 1 128 right of sabertooth
#define ENC_IN_RIGHT_B 24
#define ENC_IN_LEFT_A 18 //SW 1 128 left of sabertooth
#define ENC_IN_LEFT_B 22
#define ENC1_IN_RIGHT_A 20//SW 2 129 right sabertooth
#define ENC1_IN_RIGHT_B 26
#define ENC1_IN_LEFT_A 21//SW 2 129 left sabertooth
#define ENC1_IN_LEFT_B 28

boolean Direction_right = true;
boolean Direction_left = true;
boolean Direction_right1 = true;
boolean Direction_left1 = true;

// Keep track of the number of right wheel pulses
volatile long right_wheel_pulse_count = 0;
volatile long left_wheel_pulse_count = 0;
volatile long right1_wheel_pulse_count = 0;
volatile long left1_wheel_pulse_count = 0; 
// One-second interval for measurements
int interval = 1;
  
// Counters for milliseconds during interval
long previousMillis = 0;
long currentMillis = 0;
 
// Variable for RPM measuerment
float rpm_right = 0;
float rpm_left = 0; 
float rpm_right1 = 0;
float rpm_left1 = 0;

// Variable for angular velocity measurement
float ang_velocity_right = 0; 
float ang_velocity_right_deg = 0;
float ang_velocity_left = 0;
float ang_velocity_left_deg = 0;
float ang_velocity_right1 = 0;
float ang_velocity_right1_deg = 0;
float ang_velocity_left1 = 0;
float ang_velocity_left1_deg = 0; 
const float rpm_to_radians = 0.10471975512;
const float rad_to_deg = 57.29578;

//Values of Kp, Kd and Ki
float kp=1,kd=0,ki=0;
int i;
float error[4]={0},preverror[4]={0};
float errorFunc[4] = {0};
float prevSerror[4] = {0};
float newerror[4] = {0};
float queue1[qsize]={0,0,0,0,0,0,0,0,0,0};
float queue2[qsize]={0,0,0,0,0,0,0,0,0,0};
float queue3[qsize]={0,0,0,0,0,0,0,0,0,0};
float queue4[qsize]={0,0,0,0,0,0,0,0,0,0};
//int n;

USB Usb;
//USBHub Hub1(&Usb); // Some dongles have a hub inside
BTD Btd(&Usb); // You have to create the Bluetooth Dongle instance like so
/* You can create the instance of the class in two ways */
PS3BT PS3(&Btd); // This will just create the instance
//PS3BT PS3(&Btd, 0x00, 0x15, 0x83, 0x3D, 0x0A, 0x57); // This will also store the bluetooth address - this can be obtained from the dongle when running the sketch

bool printTemperature, printAngle;


void setup() {
  SWSerial.begin(9600);
  ST.setBaudRate(115200);
  ST1.setBaudRate(115200);  
  SWSerial.end();
  SWSerial.begin(115200);
  Serial.begin(115200); 
#if !defined(MIPSEL)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt    
  }
  
    pinMode(ENC_IN_RIGHT_A,INPUT_PULLUP);//Motor 1
    pinMode(ENC_IN_RIGHT_B,INPUT);
    attachInterrupt(digitalPinToInterrupt(ENC_IN_RIGHT_A), right_wheel_pulse, RISING);
    pinMode(ENC_IN_LEFT_A,INPUT_PULLUP);//Motor 2
    pinMode(ENC_IN_LEFT_B,INPUT);
    attachInterrupt(digitalPinToInterrupt(ENC_IN_LEFT_A), left_wheel_pulse, RISING);
    pinMode(ENC1_IN_RIGHT_A,INPUT_PULLUP);//Motor 3
    pinMode(ENC1_IN_RIGHT_B,INPUT);
    attachInterrupt(digitalPinToInterrupt(ENC1_IN_RIGHT_A), right1_wheel_pulse, RISING);
    pinMode(ENC1_IN_LEFT_A,INPUT_PULLUP);//Motor 4
    pinMode(ENC1_IN_LEFT_B,INPUT);
    attachInterrupt(digitalPinToInterrupt(ENC1_IN_LEFT_A), left1_wheel_pulse, RISING); 
}

void loop() {
  int S1 = 0;
  int S2 = 0;
  int S3 = 0;
  int S4 = 0;

  int PWM1, PWM2, PWM3, PWM4 = 0;
   if(i<qsize)
   {
   
    Usb.Task();
  if (PS3.PS3Connected || PS3.PS3NavigationConnected) {
    if (PS3.getAnalogHat(LeftHatX) > 137 || PS3.getAnalogHat(LeftHatX) < 117 || PS3.getAnalogHat(LeftHatY) > 137 || PS3.getAnalogHat(LeftHatY) < 117 || PS3.getAnalogHat(RightHatX) > 137 || PS3.getAnalogHat(RightHatX) < 117 || PS3.getAnalogHat(RightHatY) > 137 || PS3.getAnalogHat(RightHatY) < 117) {

      //Speeds in x and y Directions
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

      //Calculating the speeds of all 4 motors
      int s1 = (-0.7071*x + 0.7071*y)*0.7352; // max = 265.1285592, min = -265.1285592
      int s2 = (-0.7071*x - 0.7071*y)*0.7352;
      int s3 = (0.7071*x - 0.7071*y)*0.7352;
      int s4 = (0.7071*x + 0.7071*y)*0.7352;     

      //Mapping the Range of PWM in the Range of RPM
       S1=map(s1, -265, 265, -424, 424);
       S2=map(s2, -265, 265, -424, 424);
       S3=map(s3, -265, 265, -424, 424);
       S4=map(s4, -265, 265, -424, 424);
      
      
      // Serial.print(F("\r\nS1: "));
      // Serial.print(S1);
      // Serial.print(F("\r\nS2: "));
      // Serial.print(S2);
      // Serial.print(F("\r\nS3: "));
      // Serial.print(S3);
      // Serial.print(F("\r\nS4: "));
      // Serial.print(S4);
      
      //Assigning Motor Drivers to all the 4 Motors
      //  ST.motor(2, pid(S1));
      //  ST.motor(1, pid(S2)); 
      //  ST1.motor(2, pid(S3));
      //  ST1.motor(1, pid(S4));
      currentMillis = millis();

    if (currentMillis - previousMillis > interval) {
 
    previousMillis = currentMillis;
 
    // Calculate revolutions per minute
    rpm_right = (float)(right_wheel_pulse_count * 60 / ENC_COUNT);
    ang_velocity_right = rpm_right * rpm_to_radians;   
    ang_velocity_right_deg = ang_velocity_right * rad_to_deg;
    
    rpm_left = (float)(left_wheel_pulse_count * 60 / ENC_COUNT);
    ang_velocity_left = rpm_left * rpm_to_radians;   
    ang_velocity_left_deg = ang_velocity_left * rad_to_deg;
      
   
    rpm_right1 = (float)(right1_wheel_pulse_count * 60 / ENC_COUNT);
    ang_velocity_right1 = rpm_right1 * rpm_to_radians;   
    ang_velocity_right1_deg = ang_velocity_right1 * rad_to_deg;
 
   
    rpm_left1 = (float)(left1_wheel_pulse_count * 60 / ENC_COUNT);
    ang_velocity_left1 = rpm_left1 * rpm_to_radians;   
    ang_velocity_left1_deg = ang_velocity_left1 * rad_to_deg;
     
    // Serial.print(" Pulses: ");
    // Serial.println(left_wheel_pulse_count);
    // Serial.println(right_wheel_pulse_count);
    // Serial.println(left1_wheel_pulse_count);
    // Serial.println(right1_wheel_pulse_count);
    // Serial.println(rpm_left1);    
 
    left_wheel_pulse_count = 0;
    right_wheel_pulse_count = 0;
    left1_wheel_pulse_count = 0;
    right1_wheel_pulse_count = 0;
    //ST.motor(1,pid());
    PWM1 = PIDmotor1(rpm_right,S1);
    PWM2 = PIDmotor2(rpm_left,S2);
    PWM3 = PIDmotor3(rpm_right1,S3);
    PWM4 = PIDmotor4(rpm_left1,S4);
    
    }
        
      }
    }
  }
    if((PWM1<30 && PWM1>-30))
    {
    PWM1 = 0;
    }
    if((PWM2<30 && PWM2>-30))
    {
    PWM2 = 0;
    }
    if((PWM3<30 && PWM3>-30))
    {
    PWM3 = 0;
    }
    if((PWM4<30 && PWM4>-30))
    {
    PWM4 = 0;
    }
    

  Serial.print(S1);
  Serial.print(" ");
  Serial.print(PWM1);
  Serial.print(" ");
  Serial.print(S2);
  Serial.print(" ");
  Serial.print(PWM2);
  Serial.print(" ");
  Serial.print(S3);
  Serial.print(" ");
  Serial.print(PWM3);
  Serial.print(" ");
  Serial.print(S4);
  Serial.print(" ");
  Serial.println(PWM4);
  ST1.motor(2,PWM1);
  ST1.motor(1,PWM2);
  ST.motor(2,PWM3);
  ST.motor(1,PWM4);
  
}

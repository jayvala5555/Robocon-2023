#include <EasyTransfer.h>

//#include <Sabertooth.h>
//#include <SoftwareSerial.h>


//SoftwareSerial SWSerial(NOT_A_PIN, 30 );
//Sabertooth ST(129, SWSerial);   //1st motor driver
//Sabertooth ST1(128, SWSerial); //2nd motor driver
EasyTransfer MegatoDue;

//Declaring motor speeds for the 4 motors


// Motor encoder output pulses per 360 degree revolution (measured manually)
#define qsize 10
#define ENC_COUNT 324
#define ENCA_A 47 //SW 1 128 right of sabertooth
#define ENCA_B 51
#define ENCB_A 45 //SW 1 128 left of sabertooth
#define ENCB_B 43
#define ENCC_A 53//SW 2 129 right sabertooth
#define ENCC_B 52
#define ENCD_A 50//SW 2 129 left sabertooth
#define ENCD_B 48

#define MDA_PWM 6
#define MDA_DIR 37
#define MDB_PWM 7
#define MDB_DIR 33
#define MDC_PWM 8
#define MDC_DIR 27
#define MDD_PWM 9
#define MDD_DIR 23
 
struct RECEIVE_DATA_STRUCTURE{
  //put your variable definitions here for the data you want to receive
  //THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO
  int16_t xrec;
  int16_t yrec;
};

RECEIVE_DATA_STRUCTURE PS3data;

int S1,S2,S3,S4;
int PWM1, PWM2, PWM3, PWM4;
int xHat,yHat;
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


void setup() {
//  SWSerial.begin(9600);
//  ST.setBaudRate(115200);
//  ST1.setBaudRate(115200);  
//  SWSerial.end();
//  SWSerial.begin(115200);
  Serial.begin(115200); 
  Serial1.begin(115200);
  MegatoDue.begin(details(PS3data), &Serial1);
  
    pinMode(ENCA_A,INPUT_PULLUP);//Motor 1
    pinMode(ENCA_B,INPUT);
    attachInterrupt(digitalPinToInterrupt(ENCA_A), right_wheel_pulse, RISING);
    pinMode(ENCB_A,INPUT_PULLUP);//Motor 2
    pinMode(ENCB_B,INPUT);
    attachInterrupt(digitalPinToInterrupt(ENCB_A), left_wheel_pulse, RISING);
    pinMode(ENCC_A,INPUT_PULLUP);//Motor 3
    pinMode(ENCC_B,INPUT);
    attachInterrupt(digitalPinToInterrupt(ENCC_A), right1_wheel_pulse, RISING);
    pinMode(ENCD_A,INPUT_PULLUP);//Motor 4
    pinMode(ENCD_B,INPUT);
    attachInterrupt(digitalPinToInterrupt(ENCD_A), left1_wheel_pulse, RISING); 

    pinMode(MDA_PWM,OUTPUT);
    pinMode(MDA_DIR,OUTPUT);
    pinMode(MDB_PWM,OUTPUT);
    pinMode(MDB_DIR,OUTPUT);
    pinMode(MDC_PWM,OUTPUT);
    pinMode(MDC_DIR,OUTPUT);
    pinMode(MDD_PWM,OUTPUT);
    pinMode(MDD_DIR,OUTPUT);

    digitalWrite(MDA_DIR,LOW);
    digitalWrite(MDB_DIR,LOW);
    digitalWrite(MDC_DIR,LOW);
    digitalWrite(MDD_DIR,LOW);
    analogWrite(MDA_PWM,0);
    analogWrite(MDB_PWM,0);
    analogWrite(MDC_PWM,0);
    analogWrite(MDD_PWM,0);

    
}

void loop() {
//  int S1 = 0;
//  int S2 = 0;
//  int S3 = 0;
//  int S4 = 0;

//  int PWM1, PWM2, PWM3, PWM4 = 0;
   if(MegatoDue.receiveData())
   {
      xHat = PS3data.xrec;
      yHat = PS3data.yrec;

      Serial.print(xHat);
      Serial.print(" ");
      Serial.print(yHat);
      Serial.println(" ");
     if(i<qsize)
     {
        
        //Speeds in x and y Directions
        int x = 2*(xHat-130);
        int y = 2*(129 - yHat);
        
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
    

//  Serial.print(S1);
//  Serial.print(" ");
//  Serial.print(PWM1);
//  Serial.print(" ");
//  Serial.print(S2);
//  Serial.print(" ");
//  Serial.print(PWM2);
//  Serial.print(" ");
//  Serial.print(S3);
//  Serial.print(" ");
//  Serial.print(PWM3);
//  Serial.print(" ");
//  Serial.print(S4);
//  Serial.print(" ");
//  Serial.println(PWM4);

//  writePWM();
  
//  ST1.motor(2,PWM1);
//  ST1.motor(1,PWM2);
//  ST.motor(2,PWM3);
//  ST.motor(1,PWM4);
  delay(250);
  }
}

#include <DuePWM.h>
#include <DueTimer.h>
#include <EasyTransfer.h>

#define TimerEncoder Timer1
#define EsptoDue Serial3
#define PWM_FREQ1 3000

// MD WHEEL1
// MC WHEEL2
// MB WHEEL3
// MA WHEEL4

// Lx = 15cm
// Ly = 16.9cm

// #define MDA_PWM 6
// #define MDA_DIR 39
// #define MDB_PWM 7
// #define MDB_DIR 35
// #define MDC_PWM 8
// #define MDC_DIR 29
// #define MDD_PWM 9
// #define MDD_DIR 25

#define MDA_PWM 8
#define MDA_DIR 29
#define MDB_PWM 9
#define MDB_DIR 25
#define MDC_PWM 6
#define MDC_DIR 39
#define MDD_PWM 7
#define MDD_DIR 35

//        updown pin 

#define up_pwm 10
#define up_dir 12


#define qsize 10
#define ENC_PPR 325
// #define ENCA_A 47 //A,B pins of encoder1
// #define ENCA_B 51
// #define ENCB_A 45 //A,B pins of encoder2
// #define ENCB_B 43
// #define ENCC_A 53//A,B pins of encoder3
// #define ENCC_B 52
// #define ENCD_A 50//A,B pins of encoder4
// #define ENCD_B 48

#define ENCA_A 53 //A,B pins of encoder1
#define ENCA_B 52
#define ENCB_A 50 //A,B pins of encoder2
#define ENCB_B 48
#define ENCC_A 47//A,B pins of encoder3
#define ENCC_B 51
#define ENCD_A 45//A,B pins of encoder4
#define ENCD_B 43

#define gearratio 0.04
#define maxPWM 200
#define maxMotRPM 476
#define pi 3.141592653589
#define DegreeToRadian(x) x*0.0174532  
#define RadianToDegree(x) x*57.295779
#define RadiusOmniDrive 37.5  //centimetre
#define RadiusOmniWheel 7.5 //centimetre
#define VelocityToRPM(x) x*60/(2*pi*RadiusOmniWheel) //vel in cm/s
#define EncTime 0.1

// Keep track of the number of right wheel pulses
volatile long long int  wheel1_pulse_count = 0;
volatile long long int  wheel2_pulse_count = 0;
volatile long long int  wheel3_pulse_count = 0;
volatile long long int  wheel4_pulse_count = 0; 


int enc_rpm_wheel1,enc_rpm_wheel2,enc_rpm_wheel3,enc_rpm_wheel4 = 0;
volatile long long int enc_wheel1_pulse_prev_count, enc_wheel2_pulse_prev_count, enc_wheel3_pulse_prev_count, enc_wheel4_pulse_prev_count = 0;
// One-mili second interval for measurements
// float EncTime *  = 0.1;
  
// Counters for milliseconds during interval
// long previousMillis = 0;
// long currentMillis = 0;
 
// Variable for RPM measuerment
int rpm_req_wheel1,rpm_req_wheel2,rpm_req_wheel3,rpm_req_wheel4 = 0;

int rpm_prev_req_wheel1,rpm_prev_req_wheel2,rpm_prev_req_wheel3,rpm_prev_req_wheel4 = 0;

// Variable for angular velocity measurement
//float ang_velocity_wheel1 = 0; 
//float ang_velocity_wheel1_deg = 0.10471975512*ang_velocity_wheel1;
//float ang_velocity_wheel2 = 0; 
//float ang_velocity_wheel2_deg = 0.10471975512*ang_velocity_wheel2;
//float ang_velocity_wheel3 = 0; 
//float ang_velocity_wheel3_deg = 0.10471975512*ang_velocity_wheel3;
//float ang_velocity_wheel4 = 0; 
//float ang_velocity_wheel4_deg = 0.10471975512*ang_velocity_wheel4;
//const float rpm_to_radians = 0.10471975512;
//const float rad_to_deg = 57.29578;

//Values of Kp, Kd and Ki
// float kp=1.4,kd=0.1,ki=0.001;
// float kp=1.15,kd=0.075,ki=0.001,k=1;
float kp=0.95,kd=0.075,ki=0.011,k=1;
int cntr[4] = {0,0,0,0};
float error[4]={0,0,0,0};
float error_sum[4] = {0,0,0,0};
float preverror[4]={0,0,0,0};
float errorFunc[4] = {0,0,0,0};
float derivativeerror[4] = {0,0,0,0};
float output[4] = {0,0,0,0};
float queue1[qsize]={0,0,0,0,0,0,0,0,0,0};
float queue2[qsize]={0,0,0,0,0,0,0,0,0,0};
float queue3[qsize]={0,0,0,0,0,0,0,0,0,0};
float queue4[qsize]={0,0,0,0,0,0,0,0,0,0};

 
EasyTransfer ED;

DuePWM pwm;

struct receivedata{
  //put your variable definitions here for the data you want to receive
  //THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO
  int16_t x;
  int16_t y;
  int16_t w;
  int16_t z;
  int16_t pickingup;
  int16_t pickingdown;
};

receivedata psdata;

int S1,S2,S3,S4;
//int PWM1, PWM2, PWM3, PWM4;
unsigned int PWM1, PWM2, PWM3, PWM4 = 0;
unsigned int pwm1, pwm2, pwm3, pwm4 = 0;
int s1,s2,s3,s4 = 0;
int xHat,yHat,x,y,w,z,up,down = 0;

//ccc                                                                                  
void setup() {
  Serial.begin(9600); 
  EsptoDue.begin(9600, SERIAL_8N1);
  ED.begin(details(psdata), &EsptoDue);
  pwm.setFreq1(PWM_FREQ1);
  
  pinMode(MDA_PWM,OUTPUT);
  pinMode(MDA_DIR,OUTPUT);
  pinMode(MDB_PWM,OUTPUT);
  pinMode(MDB_DIR,OUTPUT);
  pinMode(MDC_PWM,OUTPUT);
  pinMode(MDC_DIR,OUTPUT);
  pinMode(MDD_PWM,OUTPUT);
  pinMode(MDD_DIR,OUTPUT);
  pinMode(up_pwm,OUTPUT);
  pinMode(up_dir,OUTPUT);  

  digitalWrite(MDA_DIR,LOW);
  digitalWrite(MDB_DIR,LOW);
  digitalWrite(MDC_DIR,LOW);
  digitalWrite(MDD_DIR,LOW);

  pwm.pinFreq1(MDA_PWM);
  pwm.pinFreq1(MDB_PWM);
  pwm.pinFreq1(MDC_PWM);
  pwm.pinFreq1(MDD_PWM);
  pwm.pinFreq1(up_pwm);
  // pwm.pinDuty(MDA_PWM,0);
  // pwm.pinDuty(MDB_PWM,0);
  // pwm.pinDuty(MDC_PWM,0);
  // pwm.pinDuty(MDD_PWM,0);

  pinMode(ENCA_A,INPUT_PULLUP);//Motor A
  pinMode(ENCA_B,INPUT);
  attachInterrupt(digitalPinToInterrupt(ENCA_A), wheel1_pulse_count_fun, RISING);
  pinMode(ENCB_A,INPUT_PULLUP);//Motor B
  pinMode(ENCB_B,INPUT);
  attachInterrupt(digitalPinToInterrupt(ENCB_A), wheel2_pulse_count_fun, RISING);
  pinMode(ENCC_A,INPUT_PULLUP);//Motor C
  pinMode(ENCC_B,INPUT);
  attachInterrupt(digitalPinToInterrupt(ENCC_A), wheel3_pulse_count_fun, RISING);
  pinMode(ENCD_A,INPUT_PULLUP);//Motor D
  pinMode(ENCD_B,INPUT);
  attachInterrupt(digitalPinToInterrupt(ENCD_A), wheel4_pulse_count_fun, RISING); 

  TimerEncoder.attachInterrupt(TimerHandler);
  TimerEncoder.start(1000000 * EncTime);
    
}

void loop() {
 
      getUpperData();
      // Serial.print(PWM1);
      // // Serial.print(" ");
      // // Serial.print(PWM1);
      // Serial.print(" ");
      // Serial.print(PWM2);
      // // Serial.print(" ");
      // // Serial.print(PWM2);
      // Serial.print(" ");
      // Serial.print(PWM3);
      // // Serial.print(" ");
      // // Serial.print(PWM3);
      // Serial.print(" ");
      // Serial.println(PWM4);
      // // Serial.print(" ");
      // // Serial.println(PWM4);
      // //writePWM();

      // Serial.print(enc_rpm_wheel1);
      // Serial.print(" ");
      // Serial.print(enc_rpm_wheel2);
      // Serial.print(" ");
      // Serial.print(enc_rpm_wheel3);
      // Serial.print(" ");
      // Serial.print(enc_rpm_wheel4);

      delay(2);
  
}

void TimerHandler()
{
    enc_rpm_wheel1 = ((wheel1_pulse_count-enc_wheel1_pulse_prev_count) * 60) / (EncTime * ENC_PPR);  
    enc_rpm_wheel2 = ((wheel2_pulse_count-enc_wheel2_pulse_prev_count) * 60) / (EncTime * ENC_PPR);
    enc_rpm_wheel3 = ((wheel3_pulse_count-enc_wheel3_pulse_prev_count) * 60) / (EncTime * ENC_PPR);
    enc_rpm_wheel4 = ((wheel4_pulse_count-enc_wheel4_pulse_prev_count) * 60) / (EncTime * ENC_PPR);

    // Serial.print(enc_rpm_wheel1);
    // Serial.print(" ");
    // Serial.print(enc_rpm_wheel2);
    // Serial.print(" ");
    // Serial.print(enc_rpm_wheel3);
    // Serial.print(" ");
    // Serial.println(enc_rpm_wheel4);
        
    enc_wheel1_pulse_prev_count = wheel1_pulse_count;
    enc_wheel2_pulse_prev_count = wheel2_pulse_count;
    enc_wheel3_pulse_prev_count = wheel3_pulse_count;
    enc_wheel4_pulse_prev_count = wheel4_pulse_count;

    PWM1 = PIDmotor1();
    PWM2 = PIDmotor2();
    PWM3 = PIDmotor3();
    PWM4 = PIDmotor4();

    // rpm_prev_req_wheel1 = rpm_req_wheel1;
    // rpm_prev_req_wheel2 = rpm_req_wheel2;
    // rpm_prev_req_wheel3 = rpm_req_wheel3;
    // rpm_prev_req_wheel4 = rpm_req_wheel4;

    writePWM();
    
  }

    // for calculating maxMotRPM
    // digitalWrite(MDA_DIR,HIGH);    
    // digitalWrite(MDB_DIR,HIGH);
    // digitalWrite(MDC_DIR,HIGH);
    // digitalWrite(MDD_DIR,HIGH);
    
    // pwm.pinDuty(MDA_PWM,255);
    // pwm.pinDuty(MDB_PWM,255);
    // pwm.pinDuty(MDC_PWM,255);
    // pwm.pinDuty(MDD_PWM,255);  
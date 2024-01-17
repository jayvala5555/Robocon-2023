#include <DuePWM.h>
#include <EasyTransfer.h>

#define N 4
#define MegatoDue Serial1
#define PWM_FREQ1 5000

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

 
EasyTransfer ET;

DuePWM pwm;

struct RECEIVE_DATA_STRUCTURE{
  //put your variable definitions here for the data you want to receive
  //THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO
  int16_t x;
  int16_t y;
};

RECEIVE_DATA_STRUCTURE data;

int S1,S2,S3,S4;
//int PWM1, PWM2, PWM3, PWM4;
unsigned int PWM1, PWM2, PWM3, PWM4 = 0;
int s1,s2,s3,s4 = 0;
int xHat,yHat,x,y = 0;

class Motor
{
  public:
    int dirpin;
    int pwmpin;

    void initMotor()
    {
      pinMode(dirpin,OUTPUT);
      pinMode(pwmpin,OUTPUT);
      digitalWrite(dirpin,LOW);
    }
};

Motor motor1 = {6,39};
Motor motor2 = {7,35};
Motor motor3 = {8,29};
Motor motor4 = {9,25};

Motor *pMotor[N] = {&motor1,&motor2,&motor3,&motor4};


void setup() {
  Serial.begin(9600); 
  MegatoDue.begin(9600);
  ET.begin(details(data), &MegatoDue);
  pwm.setFreq1(PWM_FREQ1);
  
  for(int i=0;i<N;++i)
    pMotor[i]->initMotor();
    
  // pinMode(MDA_PWM,OUTPUT);
  // pinMode(MDA_DIR,OUTPUT);
  // pinMode(MDB_PWM,OUTPUT);
  // pinMode(MDB_DIR,OUTPUT);
  // pinMode(MDC_PWM,OUTPUT);
  // pinMode(MDC_DIR,OUTPUT);
  // pinMode(MDD_PWM,OUTPUT);
  // pinMode(MDD_DIR,OUTPUT);

  // digitalWrite(MDA_DIR,LOW);
  // digitalWrite(MDB_DIR,LOW);
  // digitalWrite(MDC_DIR,LOW);
  // digitalWrite(MDD_DIR,LOW);

  for(int i=0;i<N;++i)
    pwm.pinFreq1(pMotor[i]->pwmpin);
  
  // pwm.pinFreq1(MDA_PWM);
  // pwm.pinFreq1(MDB_PWM);
  // pwm.pinFreq1(MDC_PWM);
  // pwm.pinFreq1(MDD_PWM);
  for(int i=0;i<N;++i)
    pwm.pinDuty(pMotor[i]->pwmpin,0);
  // pwm.pinDuty(MDA_PWM,0);
  // pwm.pinDuty(MDB_PWM,0);
  // pwm.pinDuty(MDC_PWM,0);
  // pwm.pinDuty(MDD_PWM,0);
    
}

void loop() {

      
      ET.receiveData();
      
      xHat = data.x;
      yHat = data.y;
      //Speeds in x and y Directions
      invkinematics();

      Serial.print(s1);
      // Serial.print(" ");
      // Serial.print(PWM1);
      Serial.print(" ");
      Serial.print(s2);
      // Serial.print(" ");
      // Serial.print(PWM2);
      Serial.print(" ");
      Serial.print(s3);
      // Serial.print(" ");
      // Serial.print(PWM3);
      Serial.print(" ");
      Serial.println(s4);
      // Serial.print(" ");
      // Serial.println(PWM4);
      writePWM();
      delay(2);
  
}

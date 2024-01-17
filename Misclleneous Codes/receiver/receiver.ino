#include <Sabertooth.h>
#include <SoftwareSerial.h>

struct RECEIVE_DATA_STRUCTURE {
  //put your variable definitions here for the data you want to receive
  //THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO
  int16_t x;
  int16_t y;
};

//give a name to the group of data
RECEIVE_DATA_STRUCTURE data;

//define slave i2c address
#define I2C_SLAVE_ADDRESS 9

SoftwareSerial SWSerial(NOT_A_PIN, 30);
Sabertooth ST(128, SWSerial);
Sabertooth ST1(129, SWSerial);


//Declaring motor speeds for the 4 motors
int S1, S2, S3, S4;
int x,y;
int s1,s2,s3,s4;
void setup() {
  ST.motor(1, 0);
  delay(2000);

  Serial.begin(9600);
  Serial1.begin(9600);  // Initialize serial communication
  Serial1.setTimeout(10);
  SWSerial.begin(9600);
  ST.setBaudRate(9600);
  ST1.setBaudRate(9600);
  SWSerial.end();
  SWSerial.begin(9600);
}

void loop() {

  S1 = 0;
  S2 = 0;
  S3 = 0;
  S4 = 0;

  if (Serial1.available() >= sizeof(RECEIVE_DATA_STRUCTURE)) {
    // Check if a full PS3Data struct has been received
    //RECEIVE_DATA_STRUCTURE data; // Create a PS3Data struct to hold the received data
    Serial1.readBytes((uint8_t*)&data, sizeof(data));
    // Serial.println(data.x);
    // Serial.print("y");
    // Serial.println(data.y);
  }

  if (data.x > 10 || data.x < -10 || data.y > 10 || data.y < -10 || data.x > 10 || data.x < -10 || data.y > 10 || data.y < -10) {
    //Speeds in x and y Directions
    // int x = 2*((PS3.getAnalogHat(LeftHatX)-130));
    // int y = 2*(129 - (PS3.getAnalogHat(LeftHatY)));
    x = data.x;
    y = data.y;
  // Serial.println(x);
  // Serial.print(" ");
  // Serial.println(y);
  // Serial.print(" ");
    

    if (x < -127) {
      x = -127;
    }
    if (x > 127) {
      x = 127;
    }
    if (y < -127) {
      y = -127;
    }
    if (y > 127) {
      y = 127;
    }
    if (x < 20 and x > -20) {
      x = 0;
    }
    if (y < 20 and y > -20) {
      y = 0;
    }
    // Serial.print("x");
    // Serial.println(data.x);
    // Serial.print("y");
    // Serial.println(data.y);
    //Calculating the speeds of all 4 motors
    s1 = 2 * (y - x);
    s2 = 2 * (x + y);
    s3 = 2 * (x + y);
    s4 = 2 * (y - x);

    S1 = map(s1, -255, 255, -127, 127);
    S2 = map(s2, -255, 255, -127, 127);
    S3 = map(s3, -255, 255, -127, 127);
    S4 = map(s4, -255, 255, -127, 127);


    //Assigning Motor Drivers to all the 4 Motors

  } else {
    S1 = 0;
    S2 = 0;
    S3 = 0;
    S4 = 0;
  }
  ST.motor(2, S3);
  ST.motor(1, S1);
  ST1.motor(2, S4);
  ST1.motor(1, S2);
  Serial.print(S1);
  Serial.print(" ");
  Serial.print(S2);
  Serial.print(" ");
  Serial.print(S3);
  Serial.print(" ");
  Serial.print(S4);
  Serial.println(" ");

  delay(60);
}

#include <Ps3Controller.h>
#include <ESP32Servo.h>
//create object
// EasyTransferI2C ET;



Servo myservo_yaw_feeding;
Servo myservo1_yaw_feeding;
Servo myservo_feeding;
Servo myservo1_feeding;                              // RABBIT FINAL ESP32
Servo myservo;
Servo myservo1;
int up = 0;
int down = 0;

#define actuator_dir 5
#define actuator_pwm 22
#define numeticks 4
#define numeticks1 2
#define numeticks2 21


struct SEND_DATA_STRUCTURE {

  int16_t x;
  int16_t y;
};


SEND_DATA_STRUCTURE data;

#define I2C_SLAVE_ADDRESS 9

void setup() {
  Serial.begin(9600);

  Serial2.begin(9600, SERIAL_8N1, 16, 17);
  Ps3.begin("00:1a:7d:da:71:10");
  Serial.println("Ready.");
  pinMode(actuator_dir, OUTPUT);
  pinMode(actuator_pwm, OUTPUT);
  pinMode(numeticks, OUTPUT);
  pinMode(numeticks1, OUTPUT);
  myservo.attach(19, 500, 2500);
  myservo1.attach(18, 500, 2500);
  pinMode(numeticks2, OUTPUT);
}

void loop() {

  if (Ps3.isConnected()) {

    if (abs(Ps3.event.analog_changed.stick.lx) + abs(Ps3.event.analog_changed.stick.ly) > 2) {

      data.x = Ps3.data.analog.stick.lx;
      data.y = -Ps3.data.analog.stick.ly;
      Serial.println(data.x);
      Serial.println(data.y);

      //send the data
      Serial2.write((uint8_t*)&data, sizeof(data));  // Send the PS3Data struct as a byte array
    }
    if (abs(Ps3.event.analog_changed.button.down))  //linear actuatpr going down
    {
      Serial.print("Pressing the down button: ");
      Serial.println(Ps3.data.analog.button.down, DEC);
      down = Ps3.data.analog.button.down;
      if (down > 0 && down <= 255) {
        digitalWrite(actuator_dir, LOW);
        digitalWrite(actuator_pwm, HIGH);
      } else {
        digitalWrite(actuator_dir, LOW);
        digitalWrite(actuator_pwm, LOW);
      }
    }
    if (abs(Ps3.event.analog_changed.button.up))  // linear acutaor going up
    {
      Serial.print("Pressing the up button: ");
      Serial.println(Ps3.data.analog.button.up, DEC);
      up = Ps3.data.analog.button.up;
      Serial.print(up);
      if (up > 0 && up <= 255) {
        digitalWrite(actuator_dir, HIGH);
        digitalWrite(actuator_pwm, HIGH);
      } else {
        digitalWrite(actuator_dir, LOW);
        digitalWrite(actuator_pwm, LOW);
      }
    }
    if (Ps3.event.button_down.cross) {
      Serial.println("the cross button");

      for (int pos = 0; pos <= 173; pos++)  // go up
      {
        myservo1.write(pos);
        myservo.write(173 - pos);
        delay(20);
      }
    }
    if (Ps3.event.button_down.circle)  // go down
    {
      for (int pos = 173; pos >= 0; pos--) {
        myservo1.write(pos);
        myservo.write(173 - pos);
        delay(20);
      }
      if (Ps3.event.button_down.l2)  //Close the grip{

        Serial.println("Started pressing the triangle button");
      digitalWrite(numeticks, HIGH);
      delay(500);
      digitalWrite(numeticks, LOW);
    }
    if (Ps3.event.button_down.r2)  // open grip
    {
      digitalWrite(numeticks1, HIGH);
      delay(500);
      digitalWrite(numeticks1, LOW);
    }
    if (Ps3.event.button_down.r1)  // throw
    {
      digitalWrite(numeticks2, HIGH);
      delay(500);
      digitalWrite(numeticks2, LOW);
    }
  }
  delay(120);
}

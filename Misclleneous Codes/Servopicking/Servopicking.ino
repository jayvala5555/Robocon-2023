/*
 Controlling a servo position using a potentiometer (variable resistor)
 by Michal Rinott <http://people.interaction-ivrea.it/m.rinott>

 modified on 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Knob
*/

#include <Servo.h>

Servo myservo;  // create servo object to control a servo
Servo myservo2;

void setup() {
  myservo.attach(9);
  myservo2.attach(10);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  myservo.write(0);
  myservo2.write(0);                  // sets the servo position according to the scaled value
  delay(3000);
  myservo.write(41);
  myservo2.write(175);                  // sets the servo position according to the scaled value
  delay(3000);                          // waits for the servo to get there
}

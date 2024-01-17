#include <Wire.h>

void setup() {
  Wire.begin(8); // set the slave address of the Due to 8
  Wire.onReceive(receiveData); // set the receive function for the Wire library
  Wire.onRequest(requestData); // set the request function for the Wire library
  Serial.begin(9600); // initialize the USB serial port
}

void loop() {
  // do nothing
}

void receiveData(int byteCount) {
  if (byteCount == 2 * sizeof(int)) { // check if the correct number of bytes has been received
    int data1;
    int data2;
    Wire.readBytes((uint8_t*)&data1, sizeof(int)); // read the first integer
    Wire.readBytes((uint8_t*)&data2, sizeof(int)); // read the second integer
    Serial.print("Received: ");
    Serial.print(data1);
    Serial.print(", ");
    Serial.println(data2);
  }
}

void requestData() {
  // do nothing
}

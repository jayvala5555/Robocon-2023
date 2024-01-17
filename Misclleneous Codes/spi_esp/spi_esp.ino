#include <SPI.h>

const int slaveSelectPin = 15;
SPISettings spiSettings(8000000, MSBFIRST, SPI_MODE0); // SPI speed is 21 MHz

void setup() {
  pinMode(slaveSelectPin, OUTPUT);
  SPI.begin();
}

void loop() {
  // send a byte to the Arduino Due over SPI
  digitalWrite(slaveSelectPin, LOW);
  SPI.beginTransaction(spiSettings);
  SPI.transfer(0x55);
  SPI.endTransaction();
  digitalWrite(slaveSelectPin, HIGH);
  delay(10);
}


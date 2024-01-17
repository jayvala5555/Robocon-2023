#include <SPI.h>
byte data;
const int slaveSelectPin = 10;
SPISettings spiSettings(8000000, MSBFIRST, SPI_MODE0); // SPI speed is 21 MHz

void setup() {
  pinMode(slaveSelectPin, INPUT_PULLUP);
  SPI.begin();
  Serial.begin(9600);
  SPI.setClockDivider(SPI_CLOCK_DIV2); // set SPI clock to 42 MHz
}

void loop() {
  // receive a byte from the ESP32 over SPI
  if (digitalRead(slaveSelectPin) == LOW) {
    SPI.beginTransaction(spiSettings);
    data = SPI.transfer(0x00);
    Serial.println(data);
    SPI.endTransaction();
    // do something with the received data
  }
  
  delay(10);
}
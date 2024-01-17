#include <Wire.h>
#include <Adafruit_MCP4725.h>

Adafruit_MCP4725 DAC;

#define DAC_RESOLUTION 4095

void setup() {
  Serial.begin(9600);
  Serial.println("Test");

  DAC.begin(0x60);
  delay(2000);
}

void loop() {
  
   for(int i=0;i<=4095;i=i+409)
   {
    DAC.setVoltage(i,false);   
    delay(2000);   
   }

    


}

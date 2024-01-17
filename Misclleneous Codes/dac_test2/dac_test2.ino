#include <Wire.h>             //wire library
#include <Adafruit_MCP4725.h> // MCP4725 library from adafruit
#define analogVin A0          // Analog voltage input to A0

Adafruit_MCP4725 MCP4725; 

void setup(void) {
  Serial.begin(9600);
  MCP4725.begin(0x60); // Default I2C Address of MCP4725 breakout board (sparkfun)   If not try 0x61 or 0x62
  
}

void loop(void) {
  
    uint32_t MCP4725_value;
    int adcValueRead = 0;
    float voltageRead = 0;
    
    float MCP4725_expected_output;
    
   
    for (MCP4725_value = 0; MCP4725_value < 4096; MCP4725_value++)
    {
      MCP4725_expected_output = (5.0/4096.0) * MCP4725_value;
      MCP4725.setVoltage(MCP4725_value, false);
      delay(250);
      adcValueRead = analogRead(analogVin);
      voltageRead = (adcValueRead * 5.0 )/ 1024.0;
      
      Serial.print("MCP4725 Value: ");
      Serial.print(MCP4725_value);
      
      Serial.print("\tExpected Voltage: ");
      Serial.print(MCP4725_expected_output,3);
      
      Serial.print("\tArduino ADC Value: ");
      Serial.print(adcValueRead);
      
      Serial.print("\tArduino Voltage: ");      
      Serial.println(voltageRead,3);      
    }    
}
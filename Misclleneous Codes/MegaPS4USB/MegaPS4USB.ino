//#include <EasyTransfer.h>
#include <PS4USB.h>
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

USB Usb;
PS4USB PS4(&Usb);

//EasyTransfer MegatoDue;

//struct SEND_DATA_STRUCTURE{
//  //put your variable definitions here for the data you want to send
//  //THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO
//  int16_t xrec;
//  int16_t yrec;
//};
//
//SEND_DATA_STRUCTURE PSdata;

bool printTemperature, printAngle;



void setup() {
  Serial.begin(9600);
  //Serial1.begin(9600);
//  MegatoDue.begin(details(PSdata), &Serial1);
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print(F("\r\nPS3 Bluetooth Library Started"));
}
void loop() {
  Usb.Task();
  int xrec,yrec;
  if (PS4.connected()) {
    //if (PS4.getAnalogHat(LeftHatX) > 137 || PS4.getAnalogHat(LeftHatX) < 117 || PS4.getAnalogHat(LeftHatY) > 137 || PS4.getAnalogHat(LeftHatY) < 117 || PS4.getAnalogHat(RightHatX) > 137 || PS4.getAnalogHat(RightHatX) < 117 || PS4.getAnalogHat(RightHatY) > 137 || PS4.getAnalogHat(RightHatY) < 117) {
      Serial.print(F("\r\nLeftHatX: "));
      Serial.print(PS4.getAnalogHat(LeftHatX));
      Serial.print(F("\tLeftHatY: "));
      Serial.print(PS4.getAnalogHat(LeftHatY));
   
      xrec = PS4.getAnalogHat(LeftHatX);
      yrec = PS4.getAnalogHat(LeftHatY);
    //}
    //MegatoDue.sendData();
    
    

    
    }
    Serial.write((byte*)&xrec, sizeof(xrec));
    Serial.write((byte*)&yrec, sizeof(yrec));
    delay(1000);

}

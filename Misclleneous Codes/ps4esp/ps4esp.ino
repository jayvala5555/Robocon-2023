#include <PS4Controller.h>
 
void setup()
{
  Serial.begin(115200);
 
  PS4.begin("48:18:8D:72:68:BA");
  Serial.println("Initialization ready!");
}
 
void loop()
{
  if(PS4.isConnected()) {
    Serial.println("Controller connected");
  }
 
  delay(1000);
}

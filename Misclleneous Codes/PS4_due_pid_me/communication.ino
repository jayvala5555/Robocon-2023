void getUpperData()
{
  
  ED.receiveData();
  xHat = psdata.x;
  yHat = psdata.y;
  w = psdata.w;
  z = psdata.z;
  

  // Serial.print(xHat);
  // Serial.print(" ");
  // Serial.print(yHat);
  // Serial.print(" ");
  // Serial.print(w);
  // Serial.print(" ");
  // Serial.print(z);
  // Serial.println(" ");
  

  invkinematics();
  
  }

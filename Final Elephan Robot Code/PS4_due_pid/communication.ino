void getUpperData()
{
  
  ED.receiveData();
  xHat = psdata.x;
  yHat = psdata.y;
  w = psdata.w;
  z = psdata.z;
  up = psdata.pickingup;
  down = psdata.pickingdown;
  updown();

  // Serial.print(xHat);
  // Serial.print(" ");
  // Serial.print(yHat);
  // Serial.print(" ");
  Serial.print(up);
  Serial.print(" ");
  Serial.print(down);
  Serial.println(" ");
  

  invkinematics();
  
  }

void invkinematics()
{
      x = 2*(xHat - 128);
      y = 2*(yHat - 128);

      if(x<-255)
      {
        x = -255;
      }
      if(x>255)
      {
        x = 255;
      }
      if(y<-255)
      {
        y = -255;
      }
      if(y>255)
      {
        y = 255;
      }
      if(x<10 and x>-10)
      {
        x = 0;
      }
      if(y<10 and y>-10)
      {
        y = 0;
      }

      //Calculating the speeds of all 4 motors
      s1 = (-0.7071*x + 0.7071*y)*0.7352; // max = 265.1285592, min = -265.1285592
      s2 = (-0.7071*x - 0.7071*y)*0.7352;
      s3 = (0.7071*x - 0.7071*y)*0.7352;
      s4 = (0.7071*x + 0.7071*y)*0.7352;
      
      // s1 = x+y;
      // s2 = x-y;
      // s3 = x+y;
      // s4 = x-y;
      // s1 = map(s1,-510,510,-255,255);
      // s2 = map(s2,-510,510,-255,255);
      // s3 = map(s3,-510,510,-255,255);
      // s4 = map(s4,-510,510,-255,255);
      
      s1 = map(s1,-265,265,-255,255);
      s2 = map(s2,-265,265,-255,255);
      s3 = map(s3,-265,265,-255,255);
      s4 = map(s4,-265,265,-255,255);

      PWM1 = abs(s1);
      PWM2 = abs(s2);
      PWM3 = abs(s3);
      PWM4 = abs(s4);      
      // Serial.print(F("\r\nS1: "));
      // Serial.print(S1);
      // Serial.print(F("\r\nS2: "));
      // Serial.print(S2);
      // Serial.print(F("\r\nS3: "));
      // Serial.print(S3);
      // Serial.print(F("\r\nS4: "));
      // Serial.print(S4);

}

void writePWM()
{
      if(s1>0)
      {
        digitalWrite(MDA_DIR,HIGH);
        }
      if(s1<0)
      {
        digitalWrite(MDA_DIR,LOW);
        }
      if(s2>0)
      {
        digitalWrite(MDB_DIR,HIGH);
        }
      if(s2<0)
      {
        digitalWrite(MDB_DIR,LOW);
        }
      if(s3>0)
      {
        digitalWrite(MDC_DIR,HIGH);
        }
      if(s3<0)
      {
        digitalWrite(MDC_DIR,LOW);
        }
      if(s4>0)
      {
        digitalWrite(MDD_DIR,HIGH);
        }
      if(s4<0)
      {
        digitalWrite(MDD_DIR,LOW);
        }

      if(PWM1<0)
        PWM1 = 0;
      if(PWM1>255)
        PWM1 = 255;
      if(PWM2<0)
        PWM2 = 0;
      if(PWM2>255)
        PWM2 = 255;
      if(PWM3<0)
        PWM3 = 0;
      if(PWM3>255)
        PWM3 = 255;
      if(PWM4<0)
        PWM4 = 0;
      if(PWM4>255)
        PWM4 = 255;
      
      pwm.pinDuty(MDA_PWM,PWM1);
      pwm.pinDuty(MDB_PWM,PWM2);
      pwm.pinDuty(MDC_PWM,PWM3);
      pwm.pinDuty(MDD_PWM,PWM4);


}
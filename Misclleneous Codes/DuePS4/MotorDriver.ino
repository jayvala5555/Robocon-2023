void writePWM()
{
  if(PWM1>0)
  {
    digitalWrite(MDA_DIR,HIGH);
    }
  if(PWM1<0)
  {
    digitalWrite(MDA_DIR,LOW);
    }
  if(PWM2>0)
  {
    digitalWrite(MDB_DIR,HIGH);
    }
  if(PWM2<0)
  {
    digitalWrite(MDB_DIR,LOW);
    }
  if(PWM3>0)
  {
    digitalWrite(MDC_DIR,HIGH);
    }
  if(PWM3<0)
  {
    digitalWrite(MDC_DIR,LOW);
    }
  if(PWM4>0)
  {
    digitalWrite(MDD_DIR,HIGH);
    }
  if(PWM4<0)
  {
    digitalWrite(MDD_DIR,LOW);
    }

  analogWrite(MDA_PWM,PWM1);
  analogWrite(MDB_PWM,PWM2);
  analogWrite(MDC_PWM,PWM3);
  analogWrite(MDD_PWM,PWM4);
  }

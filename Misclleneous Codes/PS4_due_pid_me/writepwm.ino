void writePWM()
{
      if(rpm_req_wheel1>0)
      {
        digitalWrite(MDA_DIR,HIGH);
        }
      if(rpm_req_wheel1<0)
      {
        digitalWrite(MDA_DIR,LOW);
        }
      if(rpm_req_wheel2>0)
      {
        digitalWrite(MDB_DIR,HIGH);
        }
      if(rpm_req_wheel2<0)
      {
        digitalWrite(MDB_DIR,LOW);
        }
      if(rpm_req_wheel3>0)
      {
        digitalWrite(MDC_DIR,HIGH);
        }
      if(rpm_req_wheel3<0)
      {
        digitalWrite(MDC_DIR,LOW);
        }
      if(rpm_req_wheel4>0)
      {
        digitalWrite(MDD_DIR,HIGH);
        }
      if(rpm_req_wheel4<0)
      {
        digitalWrite(MDD_DIR,LOW);
        }

//      if(PWM1<0)
//        PWM1 = 0;
      if(PWM1>maxMotRPM){
        PWM1 = maxMotRPM;}
//      if(PWM2<0)
//        PWM2 = 0;
      if(PWM2>maxMotRPM){
        PWM2 = maxMotRPM;}
//      if(PWM3<0)
//        PWM3 = 0;
      if(PWM3>maxMotRPM){
        PWM3 = maxMotRPM;}
//      if(PWM4<0)
//        PWM4 = 0;
      if(PWM4>maxMotRPM){
        PWM4 = maxMotRPM;}

      pwm1 = (PWM1*maxPWM)/maxMotRPM;
      pwm2 = (PWM2*maxPWM)/maxMotRPM;
      pwm3 = (PWM3*maxPWM)/maxMotRPM;
      pwm4 = (PWM4*maxPWM)/maxMotRPM;
      
      // Serial.print(rpm_req_wheel1);      
      // Serial.print(" ");
      // Serial.print(enc_rpm_wheel1);      
      // Serial.print(" ");
      // Serial.println(PWM1);      
      // Serial.print(" ");
      // Serial.println(pwm1);

      // Serial.print(pwm1);      
      // Serial.print(" ");
      // Serial.print(pwm2);      
      // Serial.print(" ");
      // Serial.print(pwm3);      
      // Serial.print(" ");
      // Serial.println(pwm4);     
      
      pwm.pinDuty(MDA_PWM,(int)pwm1);//(((rpm_req_wheel1)*maxPWM)/maxMotRPM));
      pwm.pinDuty(MDB_PWM,(int)pwm2);
      pwm.pinDuty(MDC_PWM,(int)pwm3);
      pwm.pinDuty(MDD_PWM,(int)pwm4);


}

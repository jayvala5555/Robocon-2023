void invkinematics()
{
      x = 2*(xHat - 127);
      y = 2*(127 - yHat);

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
      if(x<20 and x>-20)
      {
        x = 0;
      }
      if(y<20 and y>-20)
      {
        y = 0;
      }


      w = map(w,0,255,0,100);
      z = map(z,0,255,0,100);      
      
      //Calculating the speeds of all 4 motors
      s1 = ((-0.7071*x + 0.7071*y)*0.7352) + w - z; // max = 265.1285592, min = -265.1285592
      s2 = ((-0.7071*x - 0.7071*y)*0.7352) + w - z;
      s3 = ((0.7071*x - 0.7071*y)*0.7352) + w - z;
      s4 = ((0.7071*x + 0.7071*y)*0.7352) + w - z;
      
      // Serial.print(s1);
      // Serial.print(" ");
      // Serial.print(s2);
      // Serial.print(" ");
      // Serial.print(s3);
      // Serial.print(" ");
      // Serial.println(s4);
      
      S1=map(s1, -265, 265, -maxMotRPM, maxMotRPM);
      S2=map(s2, -265, 265, -maxMotRPM, maxMotRPM);
      S3=map(s3, -265, 265, -maxMotRPM, maxMotRPM);
      S4=map(s4, -265, 265, -maxMotRPM, maxMotRPM);

      rpm_prev_req_wheel1 = rpm_req_wheel1;
      rpm_prev_req_wheel2 = rpm_req_wheel2;
      rpm_prev_req_wheel3 = rpm_req_wheel3;
      rpm_prev_req_wheel4 = rpm_req_wheel4;
      
      rpm_req_wheel1 = S1;
      rpm_req_wheel2 = S2;
      rpm_req_wheel3 = S3;
      rpm_req_wheel4 = S4;      

      // Serial.print(rpm_req_wheel1);
      // Serial.print(" ");
      // Serial.print(rpm_req_wheel2);
      // Serial.print(" ");
      // Serial.print(rpm_req_wheel3);
      // Serial.print(" ");
      // Serial.println(rpm_req_wheel4);    

}

//      currentMillis = millis();

//    if (currentMillis - previousMillis > interval) {
// 
//    previousMillis = currentMillis;
 
    // Calculate revolutions per minute
//    rpm_wheel1 = (float)(wheel1_pulse_count * 60 / gearratio * ENC_PPR);
//    ang_velocity_wheel1 = rpm_wheel1 * rpm_to_radians;   
//    ang_velocity_wheel1_deg = ang_velocity_wheel1 * rad_to_deg;
    
//    rpm_wheel2 = (float)(wheel2_pulse_count * 60 / gearratio * ENC_PPR);
//    ang_velocity_wheel2 = rpm_wheel2 * rpm_to_radians;   
//    ang_velocity_wheel2_deg = ang_velocity_wheel2 * rad_to_deg;
      
   
//    rpm_wheel3 = (float)(wheel3_pulse_count * 60 / gearratio * ENC_PPR);
//    ang_velocity_wheel3 = rpm_wheel3 * rpm_to_radians;   
//    ang_velocity_wheel3_deg = ang_velocity_wheel3 * rad_to_deg;
 
   
//    rpm_wheel4 = (float)(wheel4_pulse_count * 60 / gearratio * ENC_PPR);
//    ang_velocity_wheel4 = rpm_wheel4 * rpm_to_radians;   
//    ang_velocity_wheel4_deg = ang_velocity_wheel4 * rad_to_deg;
     
  
//    wheel1_pulse_count = 0;
//    wheel2_pulse_count = 0;
//    wheel3_pulse_count = 0;
//    wheel4_pulse_count = 0;


//    PWM1 = PIDmotor1(rpm_wheel1,rpm_req_wheel1);
//    PWM2 = PIDmotor2(rpm_wheel2,rpm_req_wheel2);
//    PWM3 = PIDmotor3(rpm_wheel3,rpm_req_wheel3);
//    PWM4 = PIDmotor4(rpm_wheel4,rpm_req_wheel4);
   

//  }

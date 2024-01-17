float PIDmotor1(){
  error[0] = fabs(rpm_req_wheel1) - fabs(enc_rpm_wheel1);
  derivativeerror[0] = error[0] - preverror[0];
  preverror[0] = error[0];
  queue1[cntr[0]]=error[0]; 
  cntr[0]++;
  if (cntr[0]>=10){
        cntr[0]=0;    
  } 
  int error_sum=0;    
  for(int n=0;n<qsize;n++)
  {
    error_sum = error_sum + queue1[n];     
  } 
   
  errorFunc[0] = kp*error[0] + kd*(derivativeerror[0]) + ki*error_sum;     //PID
  float output = k*errorFunc[0] + fabs(rpm_req_wheel1)*1.01;
  
  if(output > maxMotRPM)
  {
    output = maxMotRPM;
    }
    
  if(output < 0)
  {
    output = 0;
    } 
  
  return output;

}

float PIDmotor2(){
  error[1] = fabs(rpm_req_wheel2) - fabs(enc_rpm_wheel2);
  derivativeerror[1] = error[1] - preverror[1];
  preverror[1] = error[1];
  queue1[cntr[1]]=error[1]; 
  cntr[1]++;
  if (cntr[1]>=10){
        cntr[1]=0;    
  } 
  int error_sum=0;    
  for(int n=0;n<qsize;n++)
  {
    error_sum = error_sum + queue1[n];     
  } 
   
  errorFunc[1] = kp*error[1] + kd*(derivativeerror[1]) + ki*error_sum;     //PID
  float output = k*errorFunc[1] + fabs(rpm_req_wheel2)*1.01;
  
  if(output > maxMotRPM)
  {
    output = maxMotRPM;
    }
    
  if(output < 0)
  {
    output = 0;
    }
  
  return output;

}

float PIDmotor3(){
  error[2] = fabs(rpm_req_wheel3) - fabs(enc_rpm_wheel3);
  derivativeerror[2] = error[2] - preverror[2];
  preverror[2] = error[2];
  queue1[cntr[2]]=error[2]; 
  cntr[2]++;
  if (cntr[2]>=10){
        cntr[2]=0;    
  } 
  int error_sum=0;    
  for(int n=0;n<qsize;n++)
  {
    error_sum = error_sum + queue1[n];     
  } 
   
  errorFunc[2] = kp*error[2] + kd*(derivativeerror[2]) + ki*error_sum;     //PID
  float output = k*errorFunc[2] + fabs(rpm_req_wheel3)*1.01;

  if(output > maxMotRPM)
  {
    output = maxMotRPM;
    }
    
  if(output < 0)
  {
    output = 0;
    }
  
  return output;

}



float PIDmotor4(){
  error[3] = fabs(rpm_req_wheel4) - fabs(enc_rpm_wheel4);
  derivativeerror[3] = error[3] - preverror[3];
  preverror[3] = error[3];
  queue1[cntr[3]]=error[3]; 
  cntr[3]++;
  if (cntr[3]>=10){
        cntr[3]=0;    
  } 
  int error_sum=0;    
  for(int n=0;n<qsize;n++)
  {
    error_sum = error_sum + queue1[n];     
  } 
   
  errorFunc[3] = kp*error[3] + kd*(derivativeerror[3]) + ki*error_sum;     //PID
  float output = k*errorFunc[3] + fabs(rpm_req_wheel4)*1.01;

  if(output > maxMotRPM)
  {
    output = maxMotRPM;
    }
    
  if(output < 0)
  {
    output = 0;
    }
  
  return output;

}
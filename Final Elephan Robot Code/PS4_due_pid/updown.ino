void updown(){
  if(up>=1){
    digitalWrite(up_dir,HIGH);

    pwm.pinDuty(up_pwm,100);
    Serial.println("inup");
  }
  // else{
  //    digitalWrite(up_dir,LOW);

  //   pwm.pinDuty(up_pwm,0);
  // }
  if(down>=1){
  digitalWrite(up_dir,LOW);

    pwm.pinDuty(up_pwm,100);
    Serial.println("indown");
  }
  // else{
  //      digitalWrite(up_dir,LOW);

  //   pwm.pinDuty(up_pwm,0);
  // }
}
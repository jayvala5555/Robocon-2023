void wheel1_pulse_count_fun() {
  
  if (digitalRead(ENC_IN_wheel1_B)) {
    wheel1_pulse_count++;
  }
  else {
    wheel1_pulse_count--;
  }
}


void wheel2_pulse_count_fun() {
  
  if (digitalRead(ENC_IN_wheel2_B)) {
    wheel2_pulse_count++;
  }
  else {
    wheel2_pulse_count--;
  }
}


void wheel3_pulse_count_fun() {
   
  if (digitalRead(ENC_IN_wheel3_B)) {
    wheel3_pulse_count++;
  }
  else {
    wheel3_pulse_count--;
  }
}

void wheel4_pulse_count_fun() {
  
  if (digitalRead(ENC_IN_wheel4_B)) {
    wheel4_pulse_count++;
  }
  else {
    wheel4_pulse_count--;
  }
}

//440
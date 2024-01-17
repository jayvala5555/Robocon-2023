void wheel1_pulse_count_fun() {
  
  if (digitalRead(ENCA_B)) {
    wheel1_pulse_count++;
  }
  else {
    wheel1_pulse_count--;
  }
}


void wheel2_pulse_count_fun() {
  
  if (digitalRead(ENCB_B)) {
    wheel2_pulse_count++;
  }
  else {
    wheel2_pulse_count--;
  }
}


void wheel3_pulse_count_fun() {
   
  if (digitalRead(ENCC_B)) {
    wheel3_pulse_count++;
  }
  else {
    wheel3_pulse_count--;
  }
}

void wheel4_pulse_count_fun() {
  
  if (digitalRead(ENCD_B)) {
    wheel4_pulse_count++;
  }
  else {
    wheel4_pulse_count--;
  }
}

//440
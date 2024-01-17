void setup() {
  pinMode(DAC0, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
    for(int i=0;i<=1024;i++)
    {
        analogWrite(DAC0, i);
        delay(50);
    }

}

word PWMPin = 3;

void setup() {
  pinMode(PWMPin, OUTPUT);
  
  //Change the below 25kHz freqency if it is not in the acceptable range for your fan
  pwm25kHzBegin();
  
}

void loop() {
  pwmDuty(65); // Change PWM to desired value here (For ML350e Gen8 fans, higher PWM = slower fan)
               // 79/79 = slowest, 1/79 = fastest. 65/79, for example, is approx. 18% fan speed
}

void pwm25kHzBegin() {
  TCCR2A = 0;                               // TC2 Control Register A
  TCCR2B = 0;                               // TC2 Control Register B
  TIMSK2 = 0;                               // TC2 Interrupt Mask Register
  TIFR2 = 0;                                // TC2 Interrupt Flag Register
  TCCR2A |= (1 << COM2B1) | (1 << WGM21) | (1 << WGM20);  // OC2B cleared/set on match when up/down counting, fast PWM
  TCCR2B |= (1 << WGM22) | (1 << CS21);     // prescaler 8
  OCR2A = 79;                               // TOP overflow value (Hz)
  OCR2B = 0;
}

void pwmDuty(byte ocrb) {
  OCR2B = ocrb;                             // PWM Width (duty)
}

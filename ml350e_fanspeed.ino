//Tested on Arduino Nano. Ensure the PWMPin you select is appropriate for your Arduino model.

word PWMPin = 3;

void setup() {
  pinMode(PWMPin, OUTPUT);
  
  pwm25kHzBegin();
  
}

void loop() {
  pwmDuty(65); // Change PWM duty cycle to desired value here (For ML350e Gen8 fans, higher PWM = slower fan)
               // 79/79 = slowest, 1/79 = fastest. 65/79, for example, is approx. 18% fan speed
               // The ceiling value (default 79) can be changed with OCR2A below

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

void setup(){
	noInterrupts();
	// pinMode(3, OUTPUT);
	pinMode(11, OUTPUT);
	TCCR2A = (
			2 << 6 // set ocr0a to non inverting mode
			| 2 << 4 // set ocr0b to non inverting mode
			| 3 << 0 // set waveform generation mode to fast pwm
			);
	TCCR2B = (
			0 << 3 // set waveform generation mode to fast pwm
			| 5 << 0 // set prescaler to 1024
			);
	// OCR0A = 23; // 90 degrees
	interrupts();
}

void loop(){
	OCR2B = 64;
  // 0.007812
	delay(1000);
	// OCR2B = 254;
	OCR2B = 80;
	delay(1000);
	// OCR2B = 39;
	delay(1000);
	// digitalWrite(6, HIGH);
	// delayMicroseconds(1500);
	// digitalWrite(6, LOW);
	// delay(8);
}

#include "servo_func.h"

// 90 Degrees
float servo_on_time = 1.5; // pwn on pulse for 1.5 ms out of 10 ms (100 hz)
int on_ticks = 23;
int off_ticks = 133;

// 0 Degrees
// float servo_on_time = 0.5; // pwn on pulse for 0.5 ms out of 10 ms (100 hz)
// int on_ticks = 8;
// int off_ticks = 148;

// 270 Degrees
// float servo_on_time = 2.5; // pwn on pulse for 2.5 ms out of 10 ms (100 hz)
// int on_ticks = 39;
// int off_ticks = 117;

static bool current_on = true;
ISR(TIMER0_COMPA_vect){//timer0 interrupt 100 Hz for servo pwm
	if(current_on){
		TCNT0 = off_ticks; // will run for on_ticks # of ticks before reacing ocr0a
		// servo on
	} else{
		TCNT0 = on_ticks;
		// servo off
	}
	current_on = !current_on;
}

void servoIntSetup(){
	// // Use Timer 0 to setup servo interrupt at 100Hz
	//
	// TCCR0A = 0;// set entire TCCR0A register to 0
	// TCCR0B = 0;// same for TCCR0B
	// TCNT0  = 0;//initialize counter value to 0
	// 		   // set compare match register for 2khz increments
	// OCR0A = 156;// = (16*10^6) / (100*1024) - 1 (must be <256)
	// 			// turn on CTC mode
	// TCCR0A |= (1 << WGM01);
	// // Set CS02 and CS00 bits for 1024 prescaler
	// TCCR0B |= (1 << CS02) | (1 << CS00);
	// // enable timer compare interrupt
	// TIMSK0 |= (1 << OCIE0A);
	// Servo PWM config
	TCCR0A = (
			2 << 6 // set ocr0a to non inverting mode
			| 2 << 4 // set ocr0b to non inverting mode
			| 3 << 0 // set waveform generation mode to fast pwm
			);
	TCCR0B = (
			0 << 3 // set waveform generation mode to fast pwm
			| 5 << 0 // set prescaler to 1024
			);
	OCR0A = 23; // 90 degrees
}

#include "led_flash.h"

extern int BlueLED;
extern bool is_moving;
void ledFlash(){
	// Faux interrupt function that gets called repeatedly and toggles the LED at approximately 2 Hz only when the robot is moving
	// else just turning the LED off
	static uint32_t previous_toggle_time = 0;
	static bool previous_led_state = 0;
	if(is_moving) {
		if(millis() - previous_toggle_time >= 250){
			digitalWrite(BlueLED,!previous_led_state);
			previous_led_state = !previous_led_state;
			previous_toggle_time = millis();
		}
	}
	else {
		digitalWrite(BlueLED, 0);
		previous_led_state = 0;
	}
}

void delayWithFlash(uint32_t time_ms){
	// Delay function that repeatedly flashes the LED as a replacement for delay(ms);
	uint32_t curtime = millis();
	while(millis() - curtime < time_ms)
		ledFlash();
}

#include "led_flash.h"

extern int BlueLED;
extern bool is_moving;
void ledFlash(){
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
	uint32_t curtime = millis();
	while(millis() - curtime < time_ms)
		ledFlash();
}

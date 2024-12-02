#ifndef LED_FLASH_H
#define LED_FLASH_H

#define FREQ 2
#define PULSE_TIME (1000 / (FREQ * 2))
void ledFlash();
void delayWithFlash(uint32_t time_ms);

#endif


#include "led.h"

#include "hal.h"
#include "hal_pal.h"

void led_write(int num, int state) {
  switch (num) {
  case LED_RED:
    palWritePad(GPIOC, 10, state);
    break;

  case LED_GREEN:
    palWritePad(GPIOC, 11, state);
    break;

  default:
    break;
  }
}

void led_init(void) {
  palSetPadMode(GPIOC, 10,
		PAL_MODE_OUTPUT_PUSHPULL |
		PAL_STM32_OSPEED_HIGHEST);
  palSetPadMode(GPIOC, 11,
		PAL_MODE_OUTPUT_PUSHPULL |
		PAL_STM32_OSPEED_HIGHEST);

  led_write(LED_RED, 0);
  led_write(LED_GREEN, 1);
}

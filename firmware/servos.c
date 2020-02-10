/*
    Copyright 2020 Joel Svensson	svenssonjoel@yahoo.se

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdint.h>
#include "servos.h"

#include "hal.h"
#include "hal_pwm.h"
#include "hal_pal.h"

/* 
   Alternate function mappings for 
   PA0 - PA3 to use tim 5 
   PB0 - PB1 to use tim 3
   PB3       to use tim 2
    ---- PB4       to use tim 3 --- should not have used this!
*/ 
#define GPIO_AF_TIM5   ((uint8_t)0x02)
#define GPIO_AF_TIM3   ((uint8_t)0x02)  
#define GPIO_AF_TIM2   ((uint8_t)0x01)

/* pwmconfig to use for TIM5.
   Here all channels are used. 
*/ 
static PWMConfig pwmcfg_tim5 = {
  1000000,
  20000,
  NULL,
  {
    {PWM_OUTPUT_ACTIVE_HIGH, NULL},
    {PWM_OUTPUT_ACTIVE_HIGH, NULL},
    {PWM_OUTPUT_ACTIVE_HIGH, NULL},
    {PWM_OUTPUT_ACTIVE_HIGH, NULL}
  },
  0,
  0
};

static PWMConfig pwmcfg_tim3 = {
  1000000,
  20000,
  NULL,
  {
    {PWM_OUTPUT_ACTIVE_HIGH, NULL},
    {PWM_OUTPUT_DISABLED,    NULL},
    {PWM_OUTPUT_ACTIVE_HIGH, NULL},
    {PWM_OUTPUT_ACTIVE_HIGH, NULL}
  },
  0,
  0,
};

/*
static PWMConfig pwmcfg_tim2 = {
  1000000,
  20000,
  NULL,
  {
    {PWM_OUTPUT_DISABLED,    NULL},
    {PWM_OUTPUT_ACTIVE_HIGH, NULL},
    {PWM_OUTPUT_DISABLED,    NULL},
    {PWM_OUTPUT_DISABLED,    NULL},
  },
  0,
  0,
};
*/

void servos_init(void) {

  palSetPadMode(GPIOA, 0,
		PAL_MODE_ALTERNATE(GPIO_AF_TIM5) |
		PAL_STM32_OSPEED_HIGHEST |
		PAL_STM32_PUPDR_FLOATING);
  palSetPadMode(GPIOA, 1,
		PAL_MODE_ALTERNATE(GPIO_AF_TIM5) |
		PAL_STM32_OSPEED_HIGHEST |
		PAL_STM32_PUPDR_FLOATING);
  palSetPadMode(GPIOA, 2,
		PAL_MODE_ALTERNATE(GPIO_AF_TIM5) |
		PAL_STM32_OSPEED_HIGHEST |
		PAL_STM32_PUPDR_FLOATING);
  palSetPadMode(GPIOA, 3,
		PAL_MODE_ALTERNATE(GPIO_AF_TIM5) |
		PAL_STM32_OSPEED_HIGHEST |
		PAL_STM32_PUPDR_FLOATING);

  palSetPadMode(GPIOB, 0,
		PAL_MODE_ALTERNATE(GPIO_AF_TIM3) |
	        PAL_STM32_OSPEED_HIGHEST |
		PAL_STM32_PUPDR_FLOATING);
  palSetPadMode(GPIOB, 1,
		PAL_MODE_ALTERNATE(GPIO_AF_TIM3) |
		PAL_STM32_OSPEED_HIGHEST |
		PAL_STM32_PUPDR_FLOATING);
  palSetPadMode(GPIOB, 4,
		PAL_MODE_ALTERNATE(GPIO_AF_TIM3) |
		PAL_STM32_OSPEED_HIGHEST |
		PAL_STM32_PUPDR_FLOATING);

  //palSetPadMode(GPIOB, 3,
  //		PAL_MODE_ALTERNATE(GPIO_AF_TIM2) |
  //		PAL_STM32_OSPEED_HIGHEST |
  //		PAL_STM32_PUPDR_FLOATING);

  
  //pwmStart(&PWMD2, &pwmcfg_tim2);
  pwmStart(&PWMD3, &pwmcfg_tim3);
  pwmStart(&PWMD5, &pwmcfg_tim5);

  //pwmEnableChannel(&PWMD2, 1, 0); /* Second channel of tim 2 */

  pwmEnableChannel(&PWMD5, 0, 0);
  pwmEnableChannel(&PWMD5, 1, 0);
  pwmEnableChannel(&PWMD5, 2, 0);
  pwmEnableChannel(&PWMD5, 3, 0);
  
  pwmEnableChannel(&PWMD3, 0, 0);
  pwmEnableChannel(&PWMD3, 2, 0);
  pwmEnableChannel(&PWMD3, 3, 0);
}
  

extern void servos_set_duty(uint8_t servos, unsigned int duty) {

  if (servos & SERVO1) {
    pwmEnableChannel(&PWMD5, 0, PWM_PERCENTAGE_TO_WIDTH(&PWMD5, duty));
  }

  if (servos & SERVO2) {
    pwmEnableChannel(&PWMD5, 1, PWM_PERCENTAGE_TO_WIDTH(&PWMD5, duty));
  }

  if (servos & SERVO3) {
    pwmEnableChannel(&PWMD5, 2, PWM_PERCENTAGE_TO_WIDTH(&PWMD5, duty));
  }

  if (servos & SERVO4) {
    pwmEnableChannel(&PWMD5, 3, PWM_PERCENTAGE_TO_WIDTH(&PWMD5, duty));
  }

  if (servos & SERVO5) { 
    pwmEnableChannel(&PWMD3, 0, PWM_PERCENTAGE_TO_WIDTH(&PWMD3, duty));
  }

  if (servos & SERVO6) {
    pwmEnableChannel(&PWMD3, 2, PWM_PERCENTAGE_TO_WIDTH(&PWMD3, duty));
  }

  if (servos & SERVO7) {
    //pwmEnableChannel(&PWMD2, 1, PWM_PERCENTAGE_TO_WIDTH(&PWMD2, duty)); 
  }

  if (servos & SERVO8) {
    pwmEnableChannel(&PWMD3, 3, PWM_PERCENTAGE_TO_WIDTH(&PWMD3, duty));
  }

}

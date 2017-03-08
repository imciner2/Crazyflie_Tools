/*
 * interuptHandlers.h
 *
 *  Created on: Feb 8, 2017
 *      Author: imcinerney
 */

#ifndef INTERRUPTHANDLERS_H__
#define INTERRUPTHANDLERS_H_

#include <stdint.h>

// The averaged motor speeds
extern volatile uint32_t averageValues[4];

extern volatile uint32_t motor1_cnt;
extern volatile uint32_t motor2_cnt;
extern volatile uint32_t motor3_cnt;
extern volatile uint32_t motor4_cnt;

// Callback for the GPIO interrupts
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_pin);

// Callback for the timer period
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);


#endif /*INTERRUPTHANDLERS_H_ */

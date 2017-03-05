/*
 * interuptHandlers.h
 *
 *  Created on: Feb 8, 2017
 *      Author: imcinerney
 */

#ifndef INTERRUPTHANDLERS_H__
#define INTERRUPTHANDLERS_H_

#include <stdint.h>

#define LENGTH_ROTOR_TIMES 1024
#define TRIGGER 50000

// The averaged motor speeds
extern volatile uint32_t rotorTimes[LENGTH_ROTOR_TIMES];

extern volatile uint8_t copied;
extern volatile uint8_t copying;
extern volatile uint8_t cycled_once;
extern volatile uint16_t currentIndex;


// Callback for the GPIO interrupts
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_pin);

// Callback for the timer period
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);


#endif /*INTERRUPTHANDLERS_H_ */

/*
 * interruptHandlers.c
 *
 *  Created on: Feb 8, 2017
 *      Author: imcinerney
 */

#include "main.h"
#include "gpio.h"
#include "tim.h"
#include "interruptHandlers.h"

#include <stdint.h>

volatile uint32_t rotorTimes[LENGTH_ROTOR_TIMES];

volatile uint8_t copied;
volatile uint8_t copying;

volatile uint8_t cycled_once;

// The current location in the circular buffer to place the next measurements
volatile uint16_t currentIndex = 0;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_pin) {
	// Depending upon which pin triggered, increment the count
	if ( !copying && (GPIO_pin == Motor_1_Pin) ) {
		// Save the count and then reset it
		rotorTimes[currentIndex] = htim2.Instance->CNT;
		htim2.Instance->CNT = 0;
		currentIndex++;
		if (currentIndex == LENGTH_ROTOR_TIMES) {
			currentIndex = 0;
			cycled_once = 1;
		}

	}
}

/**
 * This is a callback for when the timer period elapses
 *
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	if (htim->Instance == TIM2) {
		// Toggle the LED and another pin just to make sure
		HAL_GPIO_TogglePin(Timer_Indicator_GPIO_Port, Timer_Indicator_Pin);
	}
}

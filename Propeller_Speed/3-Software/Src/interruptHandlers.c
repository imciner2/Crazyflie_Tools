/*
 * interruptHandlers.c
 *
 *  Created on: Feb 8, 2017
 *      Author: imcinerney
 */

#include "main.h"
#include "gpio.h"
#include "tim.h"

#include <stdint.h>

#define NUM_AVERAGE 4

// Array to hold the circular buffer of speed values
volatile uint32_t shadowValues[NUM_AVERAGE][4];

// The 4-second average of the speed values
volatile uint32_t averageValues[4];

// The current location in the circular buffer to place the next measurements
volatile uint8_t currentIndex = 0;

// Counters for the motor speeds
volatile uint32_t motor1_cnt = 0;
volatile uint32_t motor2_cnt = 0;
volatile uint32_t motor3_cnt = 0;
volatile uint32_t motor4_cnt = 0;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_pin) {
	// Depending upon which pin triggered, increment the count
	if (GPIO_pin == Motor_1_Pin) {
		motor1_cnt++;
	} else if (GPIO_pin == Motor_2_Pin) {
		motor2_cnt++;
	} else if (GPIO_pin == Motor_3_Pin) {
		motor3_cnt++;
	} else if (GPIO_pin == Motor_4_Pin) {
		motor4_cnt++;
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
		HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);

		// Copy the motor counts and make them propeller turns
		shadowValues[currentIndex][0] = (motor1_cnt >> 1);
		shadowValues[currentIndex][1] = (motor2_cnt >> 1);
		shadowValues[currentIndex][2] = (motor3_cnt >> 1);
		shadowValues[currentIndex][3] = (motor4_cnt >> 1);

		// Zero out the counter
		motor1_cnt = 0;
		motor2_cnt = 0;
		motor3_cnt = 0;
		motor4_cnt = 0;

		// Increment the current index and keep it between 0 and NUM_AVERAGE
		currentIndex++;
		currentIndex = currentIndex % NUM_AVERAGE;

		// Average the current measurements in the circular buffer
		averageValues[0] = 0;
		averageValues[1] = 0;
		averageValues[2] = 0;
		averageValues[3] = 0;

		for (uint8_t i = 0; i < NUM_AVERAGE; i++) {
			averageValues[0] += shadowValues[i][0];
			averageValues[1] += shadowValues[i][1];
			averageValues[2] += shadowValues[i][2];
			averageValues[3] += shadowValues[i][3];
		}

		averageValues[0] = averageValues[0]/NUM_AVERAGE;
		averageValues[1] = averageValues[1]/NUM_AVERAGE;
		averageValues[2] = averageValues[2]/NUM_AVERAGE;
		averageValues[3] = averageValues[3]/NUM_AVERAGE;
	}
}

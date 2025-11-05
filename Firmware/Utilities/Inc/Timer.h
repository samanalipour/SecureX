/*
 * Timer.h
 *
 *  Created on: Oct 26, 2024
 *      Author: saman
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_

#include "main.h"
extern bool DeviceState;
extern uint32_t Timer;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

#endif /* INC_TIMER_H_ */

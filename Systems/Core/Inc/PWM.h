
#ifndef _HAL_PWM_H_
#define _HAL_PWM_H_

#include "stm32f1xx_hal.h"

void PWM_vidInit(TIM_HandleTypeDef *TIM, uint8_t TIM_Channel);

void PWM_vidStart(uint8_t Duty_cycle);

#endif

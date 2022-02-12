

#ifndef _HAL_ULTRASONIC_H_
#define _HAL_ULTRASONIC_H_

#include "stm32f1xx_hal.h"

void US_vidInit(TIM_HandleTypeDef *TIM);

uint8_t US_u8CalculateDistance(void);

#endif

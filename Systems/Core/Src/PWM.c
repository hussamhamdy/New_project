
#include "PWM.h"


TIM_HandleTypeDef *LOC_TIM;
uint8_t Timer_u8Channel;
void PWM_vidInit(TIM_HandleTypeDef *TIM, uint8_t TIM_Channel)
{
	LOC_TIM = TIM;
	Timer_u8Channel =TIM_Channel;
	if(Timer_u8Channel == TIM_CHANNEL_1 ||Timer_u8Channel == TIM_CHANNEL_2 ||Timer_u8Channel == TIM_CHANNEL_3 ||Timer_u8Channel == TIM_CHANNEL_4  )
	{
		HAL_TIM_PWM_Start(LOC_TIM, Timer_u8Channel);
	}

}

void PWM_vidStart(uint8_t Duty_cycle)
{
	uint8_t dutyCycle;
	dutyCycle = (255 * Duty_cycle)/100;
	__HAL_TIM_SET_COMPARE(LOC_TIM, Timer_u8Channel, dutyCycle);

}

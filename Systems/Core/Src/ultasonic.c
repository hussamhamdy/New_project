#include "ultrasonic.h"


#define TRIG_PIN GPIO_PIN_3
#define TRIG_PORT	GPIOA
#define ECHO_PIN GPIO_PIN_4
#define ECHO_PORT	GPIOA


uint32_t pMillis;
uint32_t Value1 = 0;
uint32_t Value2 = 0;
uint8_t Distance  = 0;


TIM_HandleTypeDef *LOC_TIM;


void US_vidInit(TIM_HandleTypeDef *TIM)
{
	LOC_TIM = TIM;
	HAL_TIM_Base_Start(LOC_TIM);
	HAL_GPIO_WritePin(TRIG_PORT, TRIG_PIN, GPIO_PIN_RESET);

}

uint8_t US_u8CalculateDistance(void)
{
	HAL_GPIO_WritePin(TRIG_PORT, TRIG_PIN, GPIO_PIN_SET);  // pull the TRIG pin HIGH
	__HAL_TIM_SET_COUNTER(LOC_TIM, 0);
	while (__HAL_TIM_GET_COUNTER (LOC_TIM) < 10);  // wait for 10 us
	HAL_GPIO_WritePin(TRIG_PORT, TRIG_PIN, GPIO_PIN_RESET);  // pull the TRIG pin low
	pMillis = HAL_GetTick(); // used this to avoid infinite while loop  (for timeout)
	// wait for the echo pin to go high
	while (!(HAL_GPIO_ReadPin (ECHO_PORT, ECHO_PIN)) && pMillis + 10 >  HAL_GetTick());
	Value1 = __HAL_TIM_GET_COUNTER (LOC_TIM);
	pMillis = HAL_GetTick(); // used this to avoid infinite while loop (for timeout)
	// wait for the echo pin to go low
	while ((HAL_GPIO_ReadPin (ECHO_PORT, ECHO_PIN)) && pMillis + 50 > HAL_GetTick());
	Value2 = __HAL_TIM_GET_COUNTER (LOC_TIM);
	Distance = (Value2-Value1)* 0.034/2;
	return Distance;
}

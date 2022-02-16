/*
 * SchM.c
 *
 *  Created on: Feb 13, 2022
 *      Author: Mahmoud Ayman
 */

#include "stm32f1xx_hal.h"
#include "SchM.h"

typedef void (*tpfvidTaskEntry)(void);

typedef struct _strTaskEntry
{
	u8 u8Periodicity;
	tpfvidTaskEntry pfvidTaskEntry;
} strTaskEntry;

#define u8NUMBER_OF_TASKS 6


static strTaskEntry astrTaskList[u8NUMBER_OF_TASKS] =
	{
		{1, },
		{1, },
		{1, }

	};


u16 LOC_u16FreeRunningCounter;

void vidUpdateTick(void);
BOOL bIsReadyToExecute(u8 u8TaskPeriodicty);

void SchM_vidInit(void)
{
	 MX_TIM4_Init();
}

void SchM_vidScheduler(void)
{
	
	/*start of Super Loop*/
	Timer_bSetTimer(TIMER_OS_TICK_TIMER, SCHM_SYSTEM_TICK);
	Timer_bStartTimer(TIMER_OS_TICK_TIMER);
	while (1)
	{
		if (TRUE == Timer_bIsTimerExpired(TIMER_OS_TICK_TIMER))
		{
			u8 u8Counter;
			vidUpdateTick();

			/*Start cyclic tasks */

			for (u8Counter = 0; (u8Counter < (u8)u8NUMBER_OF_TASKS); (u8Counter++))
			{
				if (TRUE == bIsReadyToExecute(astrTaskList[u8Counter].u8Periodicity))
				{
					astrTaskList[u8Counter].pfvidTaskEntry();
				}
			}
		}
	}
}

void vidUpdateTick(void)
{
	/*TBD: check if we need to handle overflow*/
	LOC_u16FreeRunningCounter++;
}

BOOL bIsReadyToExecute(u8 u8TaskPeriodicty)
{
	/*TBD: check logic*/
	BOOL bDecision = FALSE;

	if ((LOC_u16FreeRunningCounter % u8TaskPeriodicty) == 0.0)
	{
		bDecision = TRUE;
	}
	else
	{
		bDecision = FALSE;
	}
	return bDecision;
}
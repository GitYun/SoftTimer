// Copyright (c) 2019 Yoki
// Licensed under the MIT License

/**
  *******************************************************************************
  * @file	     softTimer.c
  * @author    Yoki
  * @version   V1.0.0
  * @date      2017-4-21
  * @brief     Software timer.
  ********************************************************************************
  */

#ifndef USE_SOFTTIMER
#define USE_SOFTTIMER 0
#endif

#if defined(USE_SOFTTIMER) && (USE_SOFTTIMER == 1)

#include "softTimer.h"

#define SOFT_TIMER_COUNT	(4)

SoftTimer_s g_SoftTimer[SOFT_TIMER_COUNT];

/**
 * \brief 	Timer counter decrement
 * \param 	softTmr pointer to SoftTiemr object
 *
 * \note	Call the function in the hardware timer interrupt ISR
 */
void softTimerDec(SoftTimer_s * softTmr)
{
	if (softTmr->expiredFlag == 0)
	{
		if (softTmr->counter > 0)
		{
			softTmr->counter--;
			if (softTmr->counter == 0)	softTmr->expiredFlag = 1;
		}
	}
}

void softTimerInit(void)
{
	uint8_t i = 0;
	for (i = 0; i < SOFT_TIMER_COUNT; i++)
	{
		g_SoftTimer[i].counter = 0;
		g_SoftTimer[i].expiredFlag = 0;
	}
}

void softTimerCreat(uint8_t timerId, uint32_t timerPeriod)
{
	if (timerId >= SOFT_TIMER_COUNT)
		return;

	__set_PRIMASK(1);	// disable all interrupts, excepet NMI
	g_SoftTimer[timerId].counter = timerPeriod;
	g_SoftTimer[timerId].expiredFlag = 0;
	__set_PRIMASK(0);	// enable all interrupts
}

uint8_t softtimerIsExpired(uint8_t timerId)
{
	if (timerId >= SOFT_TIMER_COUNT)
		return 0;
	if (g_SoftTimer[timerId].expiredFlag == 1)
	{
		g_SoftTimer[timerId].expiredFlag = 0;
		return 1;
	}

	return 0;
}

void SoftTiemrDelayMs(uint32_t ms)
{
	if (ms <= 1) ms = 2;

	__set_PRIMASK(1);
	g_SoftTimer[0].counter = ms;
	__set_PRIMASK(0);

	do {
		__nop();
	} while(g_SoftTimer[0].expiredFlag != 1);
}

#endif // defined

/**************************************** Copyright (C) 2019 **************************************/

// Copyright (c) 2019 Yoki
// Licensed under the MIT License

/**
  *******************************************************************************
  * @file	softTimer.h
  * @author	Yoki
  * @version	V1.0.0
  * @date	2017-4-21
  * @brief	Software timer
  ********************************************************************************
  */

#ifndef SOFTTIMER_H
#define SOFTTIMER_H

#ifdef __cplusplus
extern "C"	{
#endif

#include <stdint.h>

typedef struct {
	volatile uint32_t counter;
	volatile uint32_t expiredFlag;
} SoftTimer_s;

extern SoftTimer_s g_SoftTimer[];

void softTimerInit(void);
void softTimerCreat(uint8_t timerID, uint32_t timerPeriod);
void softTimerDec(SoftTimer_s * softTmr);
uint8_t softTimerIsExpired(uint8_t timerID);
void softTimerDelayMs(uint32_t ms);


#ifdef __cplusplus
}
#endif

#endif

/**************************************** Copyright (C) 2019 **************************************/

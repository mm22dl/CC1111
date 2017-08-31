#ifndef _TIMER_H_
#define _TIMER_H_

#include "cc1111.h"
#include "lib.h"
#include "led.h"

void timer_init(void);
void timer_start(void);
void timer_isr(void);

#endif
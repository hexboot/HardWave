
#ifndef __PWM_H
#define __PWM_H

#include "stm8s.h"










void PWM_Config(void);	//Init the Duoji & door
void DjRun(u8 i);		//0 put out  1 get it
void TestDj(void);		//
void Doorcolock(u8 i);	// 0 off 1 on
void PWMDelay(u8 i);

#endif
#ifndef __MOTOR3D_H
#define __MOTOR3D_H

#include "stm8s.h"

//-3D MOTOR FOR X Y Z--------------------
#define X3D_PORT	GPIOF
#define	XPWM	GPIO_PIN_7
#define XDIR	GPIO_PIN_6
#define XEN		GPIO_PIN_5

#define Y3D_PORT	GPIOF
#define YPWM	GPIO_PIN_4
#define YDIR	GPIO_PIN_3
#define YEN		GPIO_PIN_0

#define Z3D_PORT	GPIOG
#define ZPWM	GPIO_PIN_7
#define ZDIR	GPIO_PIN_6
#define ZEN		GPIO_PIN_5
//-----XXXXXXXX
#define X3DPWM(a)	if (a)	\
					GPIO_WriteHigh(X3D_PORT,XPWM);\
					else		\
					GPIO_WriteLow(X3D_PORT,XPWM)

#define X3DDIR(a)	if (a)	\
					GPIO_WriteHigh(X3D_PORT,XDIR);\
					else		\
					GPIO_WriteLow(X3D_PORT,XDIR)

#define X3DEN(a)	if (a)	\
					GPIO_WriteHigh(X3D_PORT,XEN);\
					else		\
					GPIO_WriteLow(X3D_PORT,XEN)
//---YYYYYYY
#define Y3DPWM(a)	if (a)	\
					GPIO_WriteHigh(Y3D_PORT,YPWM);\
					else		\
					GPIO_WriteLow(Y3D_PORT,YPWM)

#define Y3DDIR(a)	if (a)	\
					GPIO_WriteHigh(Y3D_PORT,YDIR);\
					else		\
					GPIO_WriteLow(Y3D_PORT,YDIR)

#define Y3DEN(a)	if (a)	\
					GPIO_WriteHigh(Y3D_PORT,YEN);\
					else		\
					GPIO_WriteLow(Y3D_PORT,YEN)
//-----ZZZZZZZZ
#define Z3DPWM(a)	if (a)	\
					GPIO_WriteHigh(Z3D_PORT,ZPWM);\
					else		\
					GPIO_WriteLow(Z3D_PORT,ZPWM)

#define Z3DDIR(a)	if (a)	\
					GPIO_WriteHigh(Z3D_PORT,ZDIR);\
					else		\
					GPIO_WriteLow(Z3D_PORT,ZDIR)

#define Z3DEN(a)	if (a)	\
					GPIO_WriteHigh(Z3D_PORT,ZEN);\
					else		\
					GPIO_WriteLow(Z3D_PORT,ZEN)

//-ZG MOTOR & DUO JI----------------------

#define ZG_PORT GPIOG
#define ZGPWM	GPIO_PIN_4
#define ZGDIR	GPIO_PIN_3
#define ZGEN	GPIO_PIN_2

// ZG DUOJI-->TIM2_CH1

//----ZG MOTOR
#define ZGPPWM(a)	if (a)	\
					GPIO_WriteHigh(ZG_PORT,ZGPWM);\
					else		\
					GPIO_WriteLow(ZG_PORT,ZGPWM)

#define ZGPDIR(a)	if (a)	\
					GPIO_WriteHigh(ZG_PORT,ZGDIR);\
					else		\
					GPIO_WriteLow(ZG_PORT,ZGDIR)

#define ZGPEN(a)	if (a)	\
					GPIO_WriteHigh(ZG_PORT,ZGEN);\
					else		\
					GPIO_WriteLow(ZG_PORT,ZGEN)


#define LowSteps 50
#define HighSteps 50
#define UP		1
#define DOWN	0
#define IN 		1
#define OUT		0
#define LEFT	1
#define RIGHT	0












void Motor_Config(void);
void Motor3DRun(u8 i,u32 num);
void MotorZgRun(uint8_t dr ,uint32_t num);
void DelayMot(u8 i);
void MotDelay(u32 i);
void MotJiasu(uint8_t dr,uint32_t temp);
void MotCri(uint8_t dr,uint32_t temp);

#endif

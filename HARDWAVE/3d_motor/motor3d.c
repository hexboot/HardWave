#include "motor3d.h"
/*
#define ZG_PORT1 GPIOB
#define ZGPWM	GPIO_PIN_0

#define ZG_PORT2	GPIOE
#define ZGDIR	GPIO_PIN_7
#define ZGEN	GPIO_PIN_6

//-ZG MOTOR & DUO JI----------------------
*/
// xsbuff ,ysbuff,zsbuff,zgsbuff means the status for the senors of guides
// xsteps,ysteps,zsteps.etc means steps for motors to run
uint32_t xsteps=0;
uint8_t xsbuff=0;
uint32_t ysteps=0;
uint8_t ysbuff=0;
uint32_t zsteps=0;
uint8_t zsbuff=0;
uint32_t zgsteps=0;
uint8_t zgsbuff=0;

uint32_t cristeps=0;
uint8_t crisbuff=0;

void Motor_Config(void)
{
	//X
	GPIO_Init(X3D_PORT, XPWM, GPIO_MODE_OUT_PP_HIGH_FAST);
	GPIO_Init(X3D_PORT, XDIR, GPIO_MODE_OUT_PP_HIGH_FAST);
	GPIO_Init(X3D_PORT, XEN, GPIO_MODE_OUT_PP_HIGH_FAST);
	//Y
	GPIO_Init(Y3D_PORT, YPWM, GPIO_MODE_OUT_PP_HIGH_FAST);
	GPIO_Init(Y3D_PORT, YDIR, GPIO_MODE_OUT_PP_HIGH_FAST);
	GPIO_Init(Y3D_PORT, YEN, GPIO_MODE_OUT_PP_HIGH_FAST);
	//Z
	GPIO_Init(Z3D_PORT, ZPWM, GPIO_MODE_OUT_PP_HIGH_FAST);
	GPIO_Init(Z3D_PORT, ZDIR, GPIO_MODE_OUT_PP_HIGH_FAST);
	GPIO_Init(Z3D_PORT, ZEN, GPIO_MODE_OUT_PP_HIGH_FAST);
	//ZG
	GPIO_Init(ZG_PORT, ZGPWM, GPIO_MODE_OUT_PP_HIGH_FAST);
	GPIO_Init(ZG_PORT, ZGDIR, GPIO_MODE_OUT_PP_HIGH_FAST);
	GPIO_Init(ZG_PORT, ZGEN, GPIO_MODE_OUT_PP_HIGH_FAST);
}

void Motor3DRun(uint8_t i,uint32_t num)
{
	switch(i)
	{
		case 1:
		X3DDIR(0);
		X3DEN(0);
		break;
		case 2:
		X3DDIR(1);
		X3DEN(0);
		break;
		default:
		break;
	}
	while(num)
	{
		X3DPWM(1);
		DelayMot(2);
		X3DPWM(0);
		DelayMot(2);
		num--;
	}
	X3DEN(1);
}



void MotorZgRun(uint8_t dr ,uint32_t num)
{
	uint32_t temp=0;
	zgsteps = num;
	if(zgsteps>55){
		temp=zgsteps-50;
	}
	switch(dr)
	{
		case 0:
		ZGPDIR(0);
		ZGPEN(0);
		break;
		case 1:
		ZGPDIR(1);
		ZGPEN(0);
		break;
		default:
		break;
	}
	while(zgsteps)
	{
		ZGPPWM(1);
		DelayMot(1);
		ZGPPWM(0);
		DelayMot(1);
		zgsteps--;
		// if(zgsteps<=temp) break;
	}
	while(zgsteps)
	{
		ZGPPWM(1);
		if(zgsteps <= LowSteps){
		  DelayMot(1);
		}
		else{
		  DelayMot(2);
		}
		ZGPPWM(0);
		if(zgsteps <= LowSteps){
		  DelayMot(1);
		}
		else{
		  DelayMot(2);
		}
		zgsteps--;
	}
}



void DelayMot(u8 i)
{
	if(i==1)
		MotDelay(400);
	if(i==2)
		MotDelay(200);
}

void MotDelay(u32 i)
{
	while(i)
	{
		i--;
	}
}


void MotJiasu(uint8_t dr,uint32_t temp)
{

	uint32_t tim=300;
	zgsteps=temp;
	switch(dr)
	{
		case 0:
		ZGPDIR(0);
		ZGPEN(0);
		break;
		case 1:
		ZGPDIR(1);
		ZGPEN(0);
		break;
		default:
		break;
	}
	while(zgsteps > 50)
	{
		ZGPPWM(1);
		MotDelay(tim);
		ZGPPWM(0);
		MotDelay(tim);
		zgsteps--;
		if(tim > 50) tim--;
		// if(zgsteps<=temp) break;
	}

	while(zgsteps <=50)
	{
		ZGPPWM(1);
		MotDelay(tim);
		ZGPPWM(0);
		MotDelay(tim);
		zgsteps--;
		if(tim<400) tim++;
	}
	ZGPEN(1);
}



void MotCri(uint8_t dr,uint32_t temp)
{

	uint32_t tim=600;
	cristeps=temp;
	switch(dr)
	{
		case 0:
		Z3DDIR(0);
		Z3DEN(0);
		break;
		case 1:
		Z3DDIR(1);
		Z3DEN(0);
		break;
		default:
		break;
	}
	while(cristeps > 100)
	{
		Z3DPWM(1);
		MotDelay(tim);
		Z3DPWM(0);
		MotDelay(tim);
		cristeps--;
		if(tim > 300) tim--;
		// if(cristeps<=temp) break;
	}

	while(cristeps <=100)
	{
		Z3DPWM(1);
		MotDelay(tim);
		Z3DPWM(0);
		MotDelay(tim);
		cristeps--;
		if(tim<600) tim=tim+20;
	}
	Z3DEN(0);
}
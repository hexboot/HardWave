
#include "pwm.h"



u8 djbuff=1000;

u8 topbuff=2400;
u8 botbuff=1000;

void PWM_Config(void)
{
    TIM2_TimeBaseInit(TIM2_PRESCALER_16, 19999);
    TIM2_OC1Init(TIM2_OCMODE_PWM1, TIM2_OUTPUTSTATE_ENABLE,1000, TIM2_OCPOLARITY_HIGH);
    TIM2_OC1PreloadConfig(ENABLE);
    /*
    TIM2_OC2Init(TIM2_OCMODE_PWM1, TIM2_OUTPUTSTATE_ENABLE,1000, TIM2_OCPOLARITY_HIGH);
    TIM2_OC2PreloadConfig(ENABLE);
    */
    TIM2_Cmd(ENABLE);
}

void DjRun(u8 i)
{
	if(i==0)
	{
		while(djbuff<= topbuff && djbuff >= botbuff)
		{
			TIM2_SetCompare1(djbuff++);
			PWMDelay(2000);
		}
	}
	if(i==1)
	{
		while(djbuff <= topbuff && djbuff >= botbuff)
		{
			TIM2_SetCompare1(djbuff--);
			PWMDelay(2000);

		}
	}
	if(djbuff <= botbuff)
		djbuff = botbuff;
	if(djbuff >= topbuff)
		djbuff = topbuff;

}

void TestDj(void)
{
	DjRun(0);
	DjRun(1);
}



void Doorcolock(u8 i)
{
	if(i==0)
		TIM2_SetCompare2(0);
	else
		TIM2_SetCompare2(19999);
}





void PWMDelay(u8 i)
{
	while(i)
	{
		i--;
	}
}
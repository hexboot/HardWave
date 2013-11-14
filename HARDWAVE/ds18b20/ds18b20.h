#ifndef __DS18B20_H
#define __DS18B20_H

#include "main.h"

#define DS18B20_PORT	GPIOG
#define DS18B20_DO		GPIO_PIN_0

#define DS18B20_INPUT	GPIO_Init(DS18B20_PORT,DS18B20_DO,GPIO_MODE_IN_PU_NO_IT);
#define DS18B20_OUTPUT	GPIO_Init(DS18B20_PORT,DS18B20_DO,GPIO_MODE_OUT_PP_HIGH_FAST);

#define DS18B20_READ	GPIO_ReadInputPin(DS18B20_PORT,DS18B20_DO)

#define DS18B20_HIGH	GPIO_WriteHigh(DS18B20_PORT,DS18B20_DO);
#define DS18B20_LOW		GPIO_WriteLow(DS18B20_PORT,DS18B20_DO);




void DS18B20_Init(void);

void DS18B20_rst(void);

u8 DS18B20_readbyte(void);
void DS18B20_writebyte(u8 dat);
short DS18B20_get_temp(void);

void dsdelay(u32 i);

#endif
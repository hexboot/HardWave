#ifndef __FM24C256_H
#define __FM24C256_H

#include "main.h"

#define FM24C256_PORT	GPIOE
#define FM24C256_WP		GPIO_PIN_0
#define FM24C256_SCL 	GPIO_PIN_1
#define FM24C256_SDA 	GPIO_PIN_2


#define FM24CX_W		0
#define FM24CX_R 		1

#define FM24CX_read 	0xA1		//1010 000 (r/w)
#define	FM24CX_write	0xA0


//-----FM24C256....SDA=PE2....SCL=PE1...WP=PE0

#define FM24C256_SCL_HIGH	GPIO_WriteHigh(FM24C256_PORT,FM24C256_SCL);
#define FM24C256_SCL_LOW	GPIO_WriteLow(FM24C256_PORT,FM24C256_SCL);
#define FM24C256_SCL_INPUT	GPIO_Init(FM24C256_PORT,FM24C256_SCL,GPIO_MODE_IN_FL_NO_IT);
#define FM24C256_SCL_OUTPUT	GPIO_Init(FM24C256_PORT,FM24C256_SCL,GPIO_MODE_OUT_PP_HIGH_FAST);

#define FM24C256_SDA_HIGH 	GPIO_WriteHigh(FM24C256_PORT,FM24C256_SDA);
#define FM24C256_SDA_LOW 	GPIO_WriteLow(FM24C256_PORT,FM24C256_SDA);
#define FM24C256_SDA_INPUT 	GPIO_Init(FM24C256_PORT,FM24C256_SDA,GPIO_MODE_IN_FL_NO_IT);
#define FM24C256_SDA_OUTPUT GPIO_Init(FM24C256_PORT,FM24C256_SDA,GPIO_MODE_OUT_PP_HIGH_FAST);
#define FM24C256_SDA_STATUS (GPIO_ReadInputPin(FM24C256_PORT,FM24C256_SDA)==1)

#define FM24C256_WP_HIGH	GPIO_WriteHigh(FM24C256_PORT,FM24C256_WP);
#define FM24C256_WP_LOW		GPIO_WriteLow(FM24C256_PORT,FM24C256_WP);
#define FM24C256_WP_INPUT	GPIO_Init(FM24C256_PORT,FM24C256_WP,GPIO_MODE_IN_FL_NO_IT);
#define FM24C256_WP_OUTPUT	GPIO_Init(FM24C256_PORT,FM24C256_WP,GPIO_MODE_OUT_PP_HIGH_FAST);


#define FRAM_READ 0xA1
#define FRAM_WRITE 0xA0

//----items for byte

/*
void FM24CX_Init(void);
void FM24CX_ByteWrite(u16 WriteAddr,u8 pbuff);
u8 FM24CX_ByteRead(u16 WriteAddr);
*/

void Some_NOP(u32 i);

void FRAM_Init(void);
void FRAM_Start(void);
void FRAM_Stop(void);
void FRAM_Ack(void);
void FRAM_No_Ack(void);
u8 Wait_FRAM_Ack(void);
void IN_Byte(u8 ch);
u8 OUT_Byte(void);
void  FRAM_Single_Data_Write(u16 addr,u8 ch);
void  FRAM_Multi_Data_Write(u16 addr,u8 length,u8 *ptr);
u8 FRAM_Single_Data_Read(u16 addr);
void FRAM_Sequ_Data_Read(u16 addr,u8 length,u8 *ptr);





#endif
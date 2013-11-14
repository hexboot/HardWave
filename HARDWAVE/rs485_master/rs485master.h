

#ifndef __RS485MASTER_H
#define __RS485MASTER_H

#include "stm8s.h"

/*
Revbuff[]
0x0A 		head
0x0D
0x01		id of Abox
0x01	 	0x02=>order Abox	0x03->read data from Abox
{
===order Abox===
0x01		0x00 open the door 0x01=>motor stop 0x02=>RESET THE ABOX
===read Abox===(ABOX MUST DELAY AWHILE AND THEN SEND DATA Delayms(20))
0x01~0xFF	0x01=>ask Abox status(wait/run)		0x02=>ask the senors's status	0x03=>.....
}
0x0D	end buff for receive orders
0x0A


Sendbuff[]
0x0A  		head
0x0D
0x00		id of master
0x00		0x01=>no work 0x02=>running
0x00		(0x00~0xFF)  numbers of boards
0x0D		end buff for receive orders
0x0A

*/

#define RS485_PORT	GPIOD
#define RS485_PORT	GPIOD
#define RS485EN		GPIO_PIN_7

#define	ReSize 		32
#define CommandSize	8
#define HEAD1		0xAA
#define HEAD2		0xBB

#define END1		0xCC
#define END2		0xDD

#define MASTER_ADD	0x00
#define	ID_ADD		0x01

#define RxBufferSize 64

void BusRecvData(void);
void CheckCommand(void);
void ClearReData(void);
void Uart1_Init(void);
void Uart3_Init(void);
void Bus_Config(void);
void BusSendData(uint8_t i);
void UART1_SendByte(uint8_t data);
void UART1_SendString(uint8_t* Data,uint16_t len);
uint8_t UART1_ReceiveByte(void);
void UART3_SendByte(uint8_t data);
void UART3_SendString(uint8_t* Data,uint16_t len);
uint8_t UART3_ReceiveByte(void);
void PGdot(uint8_t nu);



#endif

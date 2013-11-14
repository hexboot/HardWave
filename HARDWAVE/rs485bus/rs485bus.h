/**************************************************************************
function: for rs485bus.c
writer:hexboot
date:2013/11/14
**************************************************************************/

#ifndef __RS485BUS_H
#define __RS485BUS_H

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
0x0D		s
0x00		id of master
0x01		0x01=>no work 0x02=>running
0x01		(0x00~0xFF)  numbers of boards
0x0D		end buff for receive orders
0x0A		

*/


#define	Rebuff 128

#define HEAD1	0x0A
#define HEAD2	0x0D

#define ADDRS	0x01

#define END1	0x0D
#define END2	0x0A

void Rs485bus_Config(void);
void BusRecvData(void);
void BusSendData(void);
void ClearRecvData(void);
uint8_t JudgeCommand(uint8_t *data);

uint8_t BusRecvByte(void);
void BusSendByte(uint8_t data);

void Uart1_Init(void);
void Uart3_Init(void);
void UART1_SendByte(uint8_t data);
void UART1_SendString(uint8_t* Data,uint16_t len);
uint8_t UART1_ReceiveByte(void);
void UART3_SendByte(uint8_t data);
void UART3_SendString(uint8_t* Data,uint16_t len);
uint8_t UART3_ReceiveByte(void);



#endif
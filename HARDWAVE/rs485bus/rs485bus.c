/**********************************************************
Function: drive for RS485 bus
Writer: hexboot
Date:	2013/11/14
*********************************************************/

#include "rs485bus.h"

//-----------------Abox dirver

// extern for main
uint8_t len=30;
uint8_t ibuff=0;
uint8_t RecvData[Rebuff];
uint8_t RecvCommand[len];
//-----
uint8_t SendData[];



// Configuration for Rs485----------------------------------------------------------------------------------

void Rs485bus_Config(void)
{
	Uart1_Init();		// TO PC
	Uart3_Init();		// TO RS485

}


//Receive Data (working in interrupt)------------

void BusRecvData(void)
{
	RecvData[ibuff]=BusRecvByte();
	ibuff++;
	if(ibuff==(Rebuff-1)){
		ibuff=0;
	}
}


void BusSendData(uint8_t i)
{
	BusSendByte(0x0A);
	BusSendByte(0x0D);
	BusSendByte(SendData[0]);		//ID for send
	// .....send data
	BusSendByte(SendData[1]);
	BusSendByte(SendData[2]);
	BusSendByte(SendData[3]);
	BusSendByte(0x0D);
	BusSendByte(0x0A);
}

void ClearRecvData(void)
{
	for(uint8_t i = 0; i<=Rebuff;i++)
	{
		RecvData[i]=0;
	}
}


//----Judge data in RecData[]------------------------------------------
uint8_t JudgeCommand(uint8_t *data)	//if Judge return true ,means RecvCommand[] can be used
{
	for(uint8_t i=0;i<(Rebuff-len);i++){
		if((data[i]==0x0A)&&(data[i+1]==0x0D)){
			if(data[i+2]==ADDRS){
				if(data[i+len-2]==0x0D){
					if(data[i+len-1]==0x0A){
						for(uint8_t j=0;j<len;j++){
							RecvCommand[j]=data[i];
							j++;
							i++;
						}
						return true;
					}
				}
			}
		}
		if(i>=(Rebuff-len)){
			return false;
		}
	}
	ClearRecvData();	//Clear RecvData[]
}

//====================== CENTER FUNCTION =================================
//--------Recevie & Send
uint8_t BusRecvByte(void)
{
	uint8_t Recv;
	Recv=UART1_ReceiveByte();
	//Recv=UART3_ReceiveByte();
	return Recv;
}

void BusSendByte(uint8_t data)
{
	UART1_SendByte(data);
	//UART3_SendByte(data);
}


//========================================================================
//----------------------HARDWAVE FOR MCU----------------------------------

void Uart1_Init(void)
{
    UART1_DeInit();
    UART1_Init((u32)9600, UART1_WORDLENGTH_8D, UART1_STOPBITS_1, \
    UART1_PARITY_NO , UART1_SYNCMODE_CLOCK_DISABLE , UART1_MODE_TXRX_ENABLE);
    UART1_ITConfig(UART1_IT_RXNE_OR,ENABLE  );
    UART1_Cmd(ENABLE );
}

void Uart3_Init(void)
{
    UART3_DeInit();
    UART3_Init((u32)9600, UART3_WORDLENGTH_8D, UART3_STOPBITS_1, \
    UART3_PARITY_NO , UART3_MODE_TXRX_ENABLE);
    UART3_ITConfig(UART3_IT_RXNE_OR,ENABLE  );
    UART3_Cmd(ENABLE );
    GPIO_Init(RS485_PORT, RS485EN, GPIO_MODE_OUT_PP_HIGH_FAST);
    GPIO_WriteHigh(RS485_PORT,RS485EN);
}

//----------------------hardwave for BusDrive
void UART1_SendByte(uint8_t data)
{
    UART1_SendData8((uint8_t)data);
  /* Loop until the end of transmission */
  while (UART1_GetFlagStatus(UART1_FLAG_TXE) == RESET);
}

void UART1_SendString(uint8_t* Data,uint16_t len)
{
  uint16_t i=0;
  for(;i<len;i++)
    UART1_SendByte(Data[i]);
}

uint8_t UART1_ReceiveByte(void)
{
     uint8_t USART1_RX_BUF;
     while (UART1_GetFlagStatus(UART1_FLAG_RXNE) == RESET);
     USART1_RX_BUF=UART1_ReceiveData8();
     return  USART1_RX_BUF;
}


void UART3_SendByte(uint8_t data)
{
    UART3_SendData8((unsigned char)data);
  /* Loop until the end of transmission */
  while (UART3_GetFlagStatus(UART3_FLAG_TXE) == RESET);
}

void UART3_SendString(uint8_t* Data,uint16_t len)
{
  uint16_t i=0;
  for(;i<len;i++)
    UART3_SendByte(Data[i]);
}

uint8_t UART3_ReceiveByte(void)
{
     uint8_t USART3_RX_BUF;
     while (UART3_GetFlagStatus(UART3_FLAG_RXNE) == RESET);
     USART3_RX_BUF=UART3_ReceiveData8();
     return  USART3_RX_BUF;
}

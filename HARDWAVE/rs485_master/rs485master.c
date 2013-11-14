
#include "rs485master.h"

// ----------------Slavers dirver




#define countof(a)   (sizeof(a) / sizeof(*(a)))


extern uint8_t RxBuffer[];
extern uint16_t UART_RX_NUM;
extern uint8_t Rxflag;



void BusRecvData(void)				//receive data from slavers
{

}

void CheckCommand(void)
{


}



void ClearReData(void)
{

}


void Uart1_Init(void)
{
    UART1_DeInit();
    UART1_Init((u32)9600, UART1_WORDLENGTH_8D, UART1_STOPBITS_1, \
    UART1_PARITY_NO , UART1_SYNCMODE_CLOCK_DISABLE , UART1_MODE_TXRX_ENABLE);
    UART1_ITConfig(UART1_IT_RXNE_OR,ENABLE);
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
    GPIO_WriteLow(RS485_PORT,RS485EN);
}

void Bus_Config(void)
{
	Uart1_Init();		// TO PC
	Uart3_Init();		// TO RS485
}


void BusSendData(uint8_t i)
{

}

//------------------come from fengci

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


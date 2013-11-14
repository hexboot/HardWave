
//---A0 ,A1,A2 >>>GND
//1bits address for the pic


#include "fm24c256.h"



/*******************************FM24C256***************************************/
/********FOR STM8S********SDA--->PC6,SCL--->PC5**********************************/
void FRAM_Init(void)
{
	FM24C256_SCL_OUTPUT;
	FM24C256_SDA_OUTPUT;
	FM24C256_WP_OUTPUT;

	FM24C256_SCL_LOW;
	FM24C256_SDA_LOW;
	FM24C256_WP_LOW;

}



/*************************铁电启动，SCL=PC5，SDA=PC6***************************/   
void FRAM_Start(void)
{
	FM24C256_WP_LOW;
	FM24C256_SCL_LOW;//SCL=0
	Some_NOP(2);
	FM24C256_SDA_HIGH;//SDA=1
	Some_NOP(2);
	FM24C256_SCL_HIGH;//SCL=1
	Some_NOP(4);
	FM24C256_SDA_LOW;//SDA=0
	Some_NOP(2);
	FM24C256_SCL_LOW;//SCL=0
}

/*******************************铁电停止***************************************/
void FRAM_Stop(void)
   {
           FM24C256_SCL_LOW;//SCL=0
           Some_NOP(2);
           FM24C256_SDA_LOW;//SDA=0
           Some_NOP(4);
           FM24C256_SCL_HIGH;//SCL=1
           Some_NOP(2);
           FM24C256_SDA_HIGH;//SDA=1
           Some_NOP(2);
           FM24C256_SCL_LOW;//SCL=0
   }

/********************************铁电响应**************************************/        
void FRAM_Ack(void)
   {
           FM24C256_SCL_LOW;//SCL=0
           Some_NOP(2);
           FM24C256_SDA_LOW;//SDA=0
           Some_NOP(2);
           FM24C256_SCL_HIGH;//SCL=1
           Some_NOP(4);
           FM24C256_SCL_LOW;//SCL=0
   }

/********************************铁电无应�?***********************************/
void FRAM_No_Ack(void)
   {
            FM24C256_SCL_LOW;//SCL=0
           Some_NOP(2);
            FM24C256_SDA_HIGH;//SDA=1
           Some_NOP(2);
           FM24C256_SCL_HIGH;//SCL=1
           Some_NOP(4);
           FM24C256_SCL_LOW;//SCL=0
   } 

/*******************************铁电等待应答***********************************/   
u8 Wait_FRAM_Ack(void)
   {
           u8 errtime=255;
           FM24C256_SCL_LOW;//SCL=0
           Some_NOP(2);
           FM24C256_SDA_HIGH;//SDA=1,PC6
           nop();
           FM24C256_SDA_INPUT;//Set SDA InputDirection
           Some_NOP(4);
           FM24C256_SCL_HIGH;//SCL=1,PC5
           Some_NOP(2);
           while(FM24C256_SDA_STATUS)
           {
              errtime--;
                  if(!errtime)
                   {
                       FM24C256_SDA_OUTPUT;//Set SDA OutputDirection
                           FRAM_Stop();
                           return FALSE;
                   }
           }
           FM24C256_SCL_LOW;//SCL=0
           FM24C256_SDA_OUTPUT;
           FM24C256_SDA_HIGH;//SDA=1
           Some_NOP(2);
           return TRUE; 
   }

/*******************************字节写入***************************************/          
void IN_Byte(u8 ch)
   {
       u8 i=8;
       while(i--)
            {
               FM24C256_SCL_LOW;//SCL=0
               if(ch&0x80)
                    {
                            FM24C256_SDA_HIGH;//SDA=1
                    }
                   else
                    {
                           FM24C256_SDA_LOW;//SDA=0
                    }        
                   ch<<=1;//铁电数据传输先传输高�?                   Some_NOP(3);
                   FM24C256_SCL_HIGH;//SCL=1
                   Some_NOP(3);
               }
           Some_NOP(4);
           FM24C256_SCL_LOW;//SCL=0
   }
         
/********************************字节读出**************************************/           
u8 OUT_Byte(void)
   {
       u8 i=8;
       u8 ddata=0;
       FM24C256_SDA_HIGH;//SDA=1
       nop();
       FM24C256_SDA_INPUT;//SDA InputDirection                      
            
       Some_NOP(3);
       while(i--)
        {
          ddata <<= 1;
         if(FM24C256_SDA_STATUS)  //if SDA=1
          {
                ddata |= 0x01; 
          }
                   
          FM24C256_SCL_HIGH;//SCL=1
         Some_NOP(3);                   
         FM24C256_SCL_LOW;//SCL=0
         Some_NOP(3);
        }
                
           FM24C256_SDA_OUTPUT;     //SDA 输出
           Some_NOP(4);
           FM24C256_SDA_HIGH;//SDA=1
           Some_NOP(2);
           FM24C256_SCL_LOW;//SCL=0
           return ddata;        
   }

/*******************************铁电单个数据的写�?****************************/        
/****************************地址�?x0000-0x1fff*******************************/   
void  FRAM_Single_Data_Write(u16 addr,u8 ch)
   {
           u8 addr_MSB;
           u8 addr_LSB;
           sim();
           addr_MSB=(addr>>8)& 0x007F;
           addr_LSB=addr & 0x00ff;
           FRAM_Start();
           IN_Byte(FRAM_WRITE);
           Wait_FRAM_Ack();
           IN_Byte(addr_MSB);
           Wait_FRAM_Ack();
           IN_Byte(addr_LSB);
           Wait_FRAM_Ack();
           IN_Byte(ch);
           Wait_FRAM_Ack();
           FRAM_Stop();
           rim();
   }
   
/*******************************铁电多字节数据的写入***************************/
/****************************地址�?x0000-0x1fff*******************************/
/**************************地址，长�?<255)，写入数据内�?*********************/        
void  FRAM_Multi_Data_Write(u16 addr,u8 length,u8 *ptr)
   {
           u8 addr_MSB;
           u8 addr_LSB;
           u8 i;
           sim();
           length=length-1;
           addr_MSB=(addr>>8)& 0x007F;;
           addr_LSB=addr & 0x00ff;
           FRAM_Start();
           IN_Byte(FRAM_WRITE);
           Wait_FRAM_Ack();
           IN_Byte(addr_MSB);
           Wait_FRAM_Ack();
           IN_Byte(addr_LSB);
           Wait_FRAM_Ack();
           for(i=0;i<length;i++) //出错就是在这里，最后一个数据要单独�?           
           {
                      IN_Byte(*ptr);
                   Wait_FRAM_Ack();
                   ptr++;
           }
           IN_Byte(*ptr);
           Wait_FRAM_Ack();
           FRAM_Stop();
           rim();
   }    
        
/****************************铁电单个字节数据的读�?***************************/
u8 FRAM_Single_Data_Read(u16 addr)
   {
        u8 addr_MSB;
        u8 addr_LSB;
        u8 ch;
        sim();
        addr_MSB=(addr>>8)&0x007F;
        addr_LSB=addr&0x00ff;
        FRAM_Start();
        IN_Byte(FRAM_WRITE);
        Wait_FRAM_Ack();
        IN_Byte(addr_MSB);
        Wait_FRAM_Ack();
        IN_Byte(addr_LSB);
        Wait_FRAM_Ack();
        FRAM_Start();
        IN_Byte(FRAM_READ);
        Wait_FRAM_Ack();
        ch=OUT_Byte();
        FRAM_No_Ack();
        FRAM_Stop();
        rim();
        return ch;
   }             

/****************************铁电连续数据的读�?*******************************/
/******************如果读取一个，length就为1***********************************/
/***********************地址，读取字节数(<255)，读取的内容*********************/
void FRAM_Sequ_Data_Read(u16 addr,u8 length,u8 *ptr)
   {
        u8 addr_MSB;
        u8 addr_LSB;
        u8 i;
        sim();
        length=length-1;//�?
        addr_MSB = (addr>>8) & 0x007f;
        addr_LSB = addr & 0x00ff;
        FRAM_Start();
        IN_Byte(FRAM_WRITE);
        Wait_FRAM_Ack();
        IN_Byte(addr_MSB);
        Wait_FRAM_Ack();
        IN_Byte(addr_LSB);
        Wait_FRAM_Ack();
        FRAM_Start();
        IN_Byte(FRAM_READ);
        Wait_FRAM_Ack();
        for(i=0;i<length;i++)
        {
            *ptr=OUT_Byte();
            FRAM_Ack();
            ptr++;
        }
        *ptr=OUT_Byte(); 
        FRAM_No_Ack();
        FRAM_Stop();
        rim();
   }



//-------------------


void Some_NOP(u32 i)
{
	Delay(i);
}
































/*
void FM24CX_Init(void)
{
   u8 Input_Clock = 0x0;

  Input_Clock = CLK_GetClockFreq()/1000000;	

  I2C_Cmd(ENABLE);

  I2C_Init(100000, 1300, I2C_DUTYCYCLE_2,\
            I2C_ACK_CURR, I2C_ADDMODE_7BIT, Input_Clock);
  GPIO_Init(FM24CX_PORT,FM24CX_WP,GPIO_MODE_OUT_PP_HIGH_FAST);
}

void FM24CX_RW(u8 rw)
{
	if(rw==FM24CX_W) GPIO_WriteLow(FM24CX_PORT ,FM24CX_WP);
	else
		GPIO_WriteHigh(FM24CX_PORT,FM24CX_WP);
}


void FM24CX_ByteWrite(u16 WriteAddr,u8 pbuff)
{
	FM24CX_RW(FM24CX_W);

	I2C_GenerateSTART(ENABLE);
	while(!I2C_CheckEvent(I2C_EVENT_MASTER_START_SENT));
	I2C_SendData(FM24CX_write);				//write mode
	while(!I2C_CheckEvent(I2C_EVENT_MASTER_ADDRESS_ACKED));

	I2C_SendData((u8)(WriteAddr >> 8)); // MSB 
	while (!I2C_CheckEvent(I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	I2C_SendData((u8)(WriteAddr)); // LSB 
	while (!I2C_CheckEvent(I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	I2C_SendData(pbuff);

	while(!I2C_CheckEvent(I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	I2C_GenerateSTOP(ENABLE);

}

u8 FM24CX_ByteRead(u16 WriteAddr)
{
	u8 rdata;
	FM24CX_RW(FM24CX_R);
	I2C_GenerateSTART(ENABLE);
	while(!I2C_CheckEvent(I2C_EVENT_MASTER_START_SENT));
	I2C_SendData(FM24CX_read);				//write mode
	while(!I2C_CheckEvent(I2C_EVENT_MASTER_ADDRESS_ACKED));

	I2C_SendData((u8)(WriteAddr >> 8)); // MSB 
	while (!I2C_CheckEvent(I2C_EVENT_MASTER_BYTE_TRANSMITTING));
	I2C_SendData((u8)(WriteAddr)); // LSB 
	while (!I2C_CheckEvent(I2C_EVENT_MASTER_BYTE_TRANSMITTING));

	rdata=I2C_ReceiveData();

	I2C_GenerateSTOP(ENABLE);

	return rdata;


}

*/
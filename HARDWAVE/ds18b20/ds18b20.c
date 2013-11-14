#include "ds18b20.h"


//start
void DS18B20_Init(void)
{
	DS18B20_OUTPUT
	DS18B20_HIGH
}

//rst
void DS18B20_rst(void)
{
	DS18B20_OUTPUT
	DS18B20_LOW
	dsdelay(330);
	DS18B20_HIGH
	//dsdelay(10);	//at least 480us
	//dsdelay(1);
	DS18B20_INPUT
	dsdelay(2);
	while(!DS18B20_READ);
	DS18B20_OUTPUT
	DS18B20_HIGH
	dsdelay(100);

}

//write a byte to ds18b20
void DS18B20_writebyte(uint8_t dat)
{
	uint8_t j;
	//DS18B20_HIGH
	for(j=1;j<=8;j++)
	{
		
		DS18B20_LOW
		dsdelay(2);
		if(dat&0x01)
		{
			DS18B20_HIGH	//write 1
		}
		else
		{
			DS18B20_LOW
		}
		dsdelay(15);
		
		DS18B20_HIGH
		dat=dat>>1;

	}
}

//read a byte from ds18b20
uint8_t DS18B20_readbyte(void)
{
	uint8_t dat=0,i=0;
	for(i=0;i<8;i++)
	{
		dat=dat>>1;
		DS18B20_OUTPUT
		DS18B20_LOW
		dsdelay(2);
		DS18B20_INPUT
		//dsdelay(5);
		if(DS18B20_READ) dat|=0x80;
		else while(!DS18B20_READ);
		dsdelay(30);
	}
	return dat;
}
//get temperation
short DS18B20_get_temp(void)
{
  uint8_t temp;
  uint8_t TL,TH;
  float ts;
  short tem;
  DS18B20_rst();
  DS18B20_writebyte(0xCC);
  DS18B20_writebyte(0x44);
  dsdelay(555);
  DS18B20_rst();
  DS18B20_writebyte(0xCC);
  DS18B20_writebyte(0xBE);
  TL=DS18B20_readbyte();
  TH=DS18B20_readbyte();
  if(TH>7)
  {
    TH=~TH;
    TL=~TL; 
    temp=0;
  }
  else temp=1;	  	  
  tem=TH;
  tem<<=8;
  tem+=TL;
  tem=(float)tem*0.625;
  if(temp)return tem;
  else return -tem;

}









void dsdelay(uint32_t i)
{
  while(i--);
  nop();

}
#include "LPC11xx.h"
#include "uart.h"
#include "delay.h"
#include "ADC.h"
#include "temp.h"
#include "stdio.h"
#define UART_BPS  9600

char  GcRcvBuf[20];
uint32_t temp(void)
{
  uint32_t t,k;
	uint32_t ulADCData;
	uint32_t i;
	uint32_t ulADCBuf;
	uint32_t res_value;
	UART_Init ();
	ADC_Init ();


	
    ulADCData=0;
    for(i=0;i<10;i++)
     {
			 LPC_ADC->CR |=(1<<24);
			 while((LPC_ADC ->DR[7]&0x80000000)==0);
			 LPC_ADC->CR |=(1<<24);
			 while((LPC_ADC ->DR[7]&0x80000000)==0);
			 ulADCBuf =LPC_ADC->DR[7];
			 ulADCBuf =(ulADCBuf >>6)&0x3ff;
			 ulADCData+=ulADCBuf ;
		 }	
    ulADCData=ulADCData/10;
		 

    ulADCData=(ulADCData*3300)/1024;
		res_value = ((ulADCData*10000)/(3300-ulADCData));
		 
		 
//	if((res_value<33970)&&(res_value>20310))  //0-10
//	{
//			k = 1366;
//		  t = (33970-res_value)/k;
//	}		
//	else if ((res_value<20310)&&(res_value>12570)) //10-20
//	{
//			k = 774;
//		  t = (20310-res_value)/k+10;
//	}
//	else if ((res_value<12570)&&(res_value>8034)) //20-30
//	{
//			k = 453.7;
//		  t = ((12570-res_value)/k)+20;
//	}
//	else if ((res_value<8034)&&(res_value>5298))  //30-40
//	{
//			k = 273.7;
//		  t = ((8034-res_value)/k)+30;
//	}
//	else if ((res_value<5298)&&(res_value>3586))  //40-50
//	{
//			k = 171.7;
//		  t = ((5298-res_value)/k)+40;
//	}
//	else if ((res_value<3586)&&(res_value>2484))  //50-60
//	{   k = 110.2;
//		  t = ((3586-res_value)/k)+50;
//	}
if((res_value < 33970)&&(res_value > 20310))//0~10
	{
		k=136600;
		t=(33970-res_value )*1000/k;
	}
	else if((res_value < 20311)&&(res_value > 12570))//10~20
	{
		k=77400;
		t=((20310-res_value)*1000/k)+100;
	}
	else if((res_value<12571)&&(res_value>8034))//20~30
	{
		k=45370;
		t=((12570-res_value)*1000/k)+200;
	}
	else if((res_value<8035)&&(res_value>5298))//30~40
	{
		k=27370;
		t=((8034-res_value)*1000/k)+300;
	}
	else if((res_value<5299)&&(res_value>3586))//40~50
	{
		k=17130;
		t=((5295-res_value)*1000/k)+400;
	}
	else if((res_value<3587)&&(res_value>2484))//50~60
	{
		k=11030;
		t=((3586-res_value)*1000/k)+500;
	}
	else if((res_value<2485)&&(res_value>1756))//60~70
	{
		k=7280;
		t=((2484-res_value)*1000/k)+600;
	}
	
   	sprintf (GcRcvBuf,"temp=%fC    ", (float)t/10);
      UART_SendStr(GcRcvBuf);
	  
      return 0 ;
}
	

#include "LPC11xx.h"
#include "uart.h"
#include "delay.h"
#include "display.h"
#include "ADC.h"
#include "KEY.h"
#include "temp.h"
#include <stdio.h>
#include <string.h>
//char  GcRcvBuf[20];
int main()
{  
	key_init();
	UART_Init ();
	ADC_Init ();
	InitLCD();

	while(1)
	{ temp();   
	 	LCD_DisplayStr(0,0,GcRcvBuf);	
	}

	}

#ifndef __LED_H
#define __LED_H	 
#include "stm32f10x.h"

void LED_Init(void);//≥ı ºªØ
void LEDPWM(void);
void LEDPWM_Init(void);
void LED_RGB(int a,int b,int c);
		 				    
#endif

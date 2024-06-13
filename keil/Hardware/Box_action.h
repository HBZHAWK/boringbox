#include "stm32f10x.h"                  // Device header
#include "delay.h"
#include "Key.H"
#include "stdlib.h"
#include "PWM.h"
#ifndef	 __BOX_ACTION_H
#define  __BOX_ACTION_H

void open(void);
void push(void);

void open_push(void);
void action(int con);
void waite(int con);

void boring_init(void);



#endif

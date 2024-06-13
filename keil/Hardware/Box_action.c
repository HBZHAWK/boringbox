#include <stdio.h>
#include <stdlib.h>
#include "stm32f10x.h"                
#include "Box_action.h"
#include "led.h"
#include "Delay.h"
//通道1推杆 通道2推盖

void lid(int a,int b,int c,int d)//c1为开
{
	if(c==1)
	{
		for(int i=a;i>b;i-=2)
		{
			TIM_SetCompare2(TIM4, i);
			Delay_us(d);
		}
	}
	else
	{
			for(int i=a;i<b;i+=2)
		{
			TIM_SetCompare2(TIM4, i);
			Delay_us(d);
		}
	}
}


void key1(int a,int b,int c,int d)//c1为推
{
	if(c==1)
	{
		for(int i=a;i<b;i+=5)
		{
			TIM_SetCompare1(TIM4, i);
			Delay_us(d);
		}
	}
	else
	{
			for(int i=a;i>b;i-=5)
		{
			TIM_SetCompare1(TIM4, i);
			Delay_us(d);
		}
	}
}


void boring_init()
{
	TIM_SetCompare1(TIM4, 1500);
	Delay_ms(500);
	TIM_SetCompare2(TIM4, 1348);
	Delay_ms(500);
}

void open()
{
	lid(1348,800,1,800);
	
}

void close()
{
	lid(800,1348,0,800);
}

void push()
{
	key1(1500,2500,1,1500);
}
void pull()
{
	key1(2400,1500,0,1500);
}

void pull_close()
{
	pull();
	close();
}

void open_push()
{
	open();
	push();
}
void lala()
{
	open_push();
	pull_close();
}
void heihei()
{
	open();
	key1(1500,2000,1,2000);
	key1(2000,1700,0,2000);
	key1(1700,2000,1,2000);
	key1(2000,1500,0,2000);
	close();
}


void trytry()
{
	lid(1340,1000,1,800);
	lid(1000,1340,0,800);
	lid(1340,1000,1,800);
	lid(1000,1400,0,800);
}

void weiwei()
{
	lid(1348,1100,1,600);
	lid(1200,1348,0,600);
	lid(1348,1100,1,600);
	lid(1200,1348,0,600);
	lid(1348,1100,1,600);
	lid(1200,1348,0,600);
	lid(1348,1100,1,600);
	lid(1200,1348,0,600);
	lid(1348,1100,1,600);
	lid(1200,1348,0,600);
	close();
}

void tuitui()
{
	open();
	Delay_ms(600);
	close();
}


void wuwu()
{
	setLEDStartColor(255,0,0);
	Delay_ms(500);
	setLEDStartColor(0,255,0);
	Delay_ms(500);
	setLEDStartColor(0,0,255);
	Delay_ms(500);
	
}


void haha()
{
	open();
	key1(1500,2100,1,1000);
	key1(2100,1400,0,1000);
	key1(1400,2400,1,1000);
	pull_close();
	
}

void wawa()
{
	lid(1348,1100,1,800);
	key1(1500,2400,1,800);
	key1(2400,1500,0,800);
	lid(1100,1348,0,800);
}
void dodo()
{
	open();
	key1(1500,2100,1,4000);
	key1(2100,2400,1,800);	
	pull();
	close();
}


void blala()
{
	open();
	key1(1500,2100,1,4000);
	lid(800,1180,0,1000);
	lid(1180,800,1,500);
	push();
	pull();
	close();
}


void gaga()
{
	lid(1348,1060,1,5000);
	key1(1500,1550,1,4000);
	key1(1550,1500,0,600);
	push();
	pull();
	close();
}

void xiuxiu()
{
	open();
	key1(1500,2000,1,1500);
	pull();
	close();
	open();
	push();
	pull();
	close();
}

void ouou()
{
	
	lid(1348,1100,1,600);
	lid(1200,1348,0,600);
	lid(1348,1100,1,600);
	lid(1200,1348,0,600);
	lid(1348,1100,1,600);
	lid(1200,1348,0,600);
	lid(1348,1100,1,600);
	lid(1200,1348,0,600);
	lid(1348,1100,1,600);
	lid(1200,1348,0,600);
	open_push();
	pull_close();
}

void aaaa()
{
	open();
	key1(1500,1800,1,1000);
	key1(1800,1500,0,1000);
	key1(1500,1800,1,1000);
	key1(1800,1500,0,1000);
	push();
	pull_close();
}


void wowo()
{
	open();
	key1(1500,1800,1,900);
	lid(800,1100,0,900);
	key1(1800,1500,0,900);
	lid(1100,800,1,900);
	key1(1500,1800,1,900);
	lid(800,1100,0,900);
	key1(1800,1500,0,900);
	lid(1100,800,1,900);
	push();
	pull_close();
}


void lanlan()
{
	

	open();
	Delay_ms(1000);
	push();
	pull_close();
}


void action(int con)
	{
		TIM_Cmd(TIM4, ENABLE);
		switch(con)
		{
			case 0:{lala();setLEDStartColor(225,0,0);break;}
			case 1:{haha();setLEDStartColor(0,225,0);break;}
			case 2:{wawa();setLEDStartColor(225,225,0);break;}
			case 3:{dodo();setLEDStartColor(0,225,225);break;}
			case 4:{blala();setLEDStartColor(255,182,193);break;}
			case 5:{gaga();setLEDStartColor(230,190,255);break;}
			case 6:{ouou();setLEDStartColor(135,206,250);break;}
			case 7:{aaaa();setLEDStartColor(189,252,201);break;}
			case 8:{wowo();setLEDStartColor(128,128,128);break;}
			case 9:{lanlan();setLEDStartColor(255,165,0);break;}
		}
		Delay_ms(20);
		TIM_Cmd(TIM4, DISABLE);
}
void waite(int con)
{
		TIM_Cmd(TIM4, ENABLE);
		switch(con)
		{
			case 0:{trytry();setLEDStartColor(127,0,225);break;}
			case 1:{heihei();setLEDStartColor(53,165,127);break;}
			case 2:{weiwei();setLEDStartColor(235,0,225);break;}
			case 3:{tuitui();setLEDStartColor(43,78,127);break;}
			case 4:{wuwu();break;}

		}
		Delay_ms(20);
		TIM_Cmd(TIM4, DISABLE);
}




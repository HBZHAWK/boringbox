#include "stm32f10x.h"                  // Device header
#include "Box_action.h"

#define STEP 1
#define MAX_COLOR_VALUE 255
#define UPDATE_INTERVAL 20 // 每50次中断更新一次LED状态

// LED状态结构体
typedef struct {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    int step;
    int phase;
    int counter;
} LEDState;

LEDState ledState = {0, 0, 0, STEP, 0, 0};

extern int Key_KeyNumber;
extern int randcount;
extern int hellocount;
extern int helloen;
uint8_t scan_time = 0;



void setLEDStartColor(uint8_t red, uint8_t green, uint8_t blue) {
    ledState.red = red;
    ledState.green = green;
    ledState.blue = blue;
    ledState.phase = 0; // 重置相位
    LED_RGB(ledState.red, ledState.green, ledState.blue); // 更新LED颜色
}

						
void GPIO_KeyInit(void)	//初始化GPIO								
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
}

void Timer_Init(void)//初始化定时器
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	TIM_InternalClockConfig(TIM2);
	
	TIM_TimeBaseInitTypeDef TimeBaseInitStructure;
	TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TimeBaseInitStructure.TIM_Period=10-1;
	TimeBaseInitStructure.TIM_Prescaler=7200-1;
	TimeBaseInitStructure.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM2,&TimeBaseInitStructure);
	
	TIM_ClearFlag(TIM2,TIM_FLAG_Update);
	
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=2;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM2,ENABLE);
}

void key_init()
{
	GPIO_KeyInit();
	Timer_Init();
}


void TIM2_IRQHandler(void)//定时器扫描（1ms）
{
//	static uint8_t scan_time = 0;
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==1)
	{
		
        ledState.counter++;
        if (ledState.counter >= UPDATE_INTERVAL) {
            ledState.counter = 0;

            // 更新LED状态
            switch (ledState.phase) {
                case 0: // 红 -> 黄
                    if (ledState.green < MAX_COLOR_VALUE) {
                        ledState.green += STEP;
                    } else {
                        ledState.phase++;
                    }
                    break;
                case 1: // 黄 -> 绿
                    if (ledState.red > 0) {
                        ledState.red -= STEP;
                    } else {
                        ledState.phase++;
                    }
                    break;
                case 2: // 绿 -> 青
                    if (ledState.blue < MAX_COLOR_VALUE) {
                        ledState.blue += STEP;
                    } else {
                        ledState.phase++;
                    }
                    break;
                case 3: // 青 -> 蓝
                    if (ledState.green > 0) {
                        ledState.green -= STEP;
                    } else {
                        ledState.phase++;
                    }
                    break;
                case 4: // 蓝 -> 紫
                    if (ledState.red < MAX_COLOR_VALUE) {
                        ledState.red += STEP;
                    } else {
                        ledState.phase++;
                    }
                    break;
                case 5: // 紫 -> 红
                    if (ledState.blue > 0) {
                        ledState.blue -= STEP;
                    } else {
                        ledState.phase++;
                    }
                    break;
                case 6: // 红 -> 白
                    if (ledState.green < MAX_COLOR_VALUE) {
                        ledState.green += STEP;
                    } else if (ledState.blue < MAX_COLOR_VALUE) {
                        ledState.blue += STEP;
                    } else {
                        ledState.phase++;
                    }
                    break;
                case 7: // 白 -> 绿
                    if (ledState.red > 0) {
                        ledState.red -= STEP;
                    } else if (ledState.blue > 0) {
                        ledState.blue -= STEP;
                    } else {
                        ledState.phase++;
                    }
                    break;
                case 8: // 绿 -> 蓝
                    if (ledState.red < MAX_COLOR_VALUE) {
                        ledState.red += STEP;
                    } else if (ledState.blue > 0) {
                        ledState.blue -= STEP;
                    } else {
                        ledState.phase++;
                    }
                    break;
                case 9: // 蓝 -> 青
                    if (ledState.green < MAX_COLOR_VALUE) {
                        ledState.green += STEP;
                    } else {
                        ledState.phase++;
                    }
                    break;
                case 10: // 青 -> 紫
                    if (ledState.red < MAX_COLOR_VALUE) {
                        ledState.red += STEP;
                    } else if (ledState.green > 0) {
                        ledState.green -= STEP;
                    } else {
                        ledState.phase++;
                    }
                    break;
                case 11: // 紫 -> 黄
                    if (ledState.green < MAX_COLOR_VALUE) {
                        ledState.green += STEP;
                    } else if (ledState.blue > 0) {
                        ledState.blue -= STEP;
                    } else {
                        ledState.phase++;
                    }
                    break;
                case 12: // 黄 -> 绿
                    if (ledState.red > 0) {
                        ledState.red -= STEP;
                    } else {
                        ledState.phase++;
                    }
                    break;
                case 13: // 绿 -> 青
                    if (ledState.blue < MAX_COLOR_VALUE) {
                        ledState.blue += STEP;
                    } else {
                        ledState.phase++;
                    }
                    break;
                case 14: // 青 -> 红
                    if (ledState.green > 0) {
                        ledState.green -= STEP;
                    } else if (ledState.red < MAX_COLOR_VALUE) {
                        ledState.red += STEP;
                    } else {
                        ledState.phase++;
                    }
                    break;
                case 15: // 红 -> 黑
                    if (ledState.red > 0) {
                        ledState.red -= STEP;
                    } else {
                        ledState.phase++;
                    }
                    break;
                case 16: // 黑 -> 绿
                    if (ledState.green < MAX_COLOR_VALUE) {
                        ledState.green += STEP;
                    } else {
                        ledState.phase++;
                    }
                    break;
                case 17: // 绿 -> 青
                    if (ledState.blue < MAX_COLOR_VALUE) {
                        ledState.blue += STEP;
                    } else {
                        ledState.phase++;
                    }
                    break;
                case 18: // 青 -> 蓝
                    if (ledState.green > 0) {
                        ledState.green -= STEP;
                    } else {
                        ledState.phase++;
                    }
                    break;
                case 19: // 蓝 -> 白
                    if (ledState.red < MAX_COLOR_VALUE) {
                        ledState.red += STEP;
                    } else if (ledState.green < MAX_COLOR_VALUE) {
                        ledState.green += STEP;
                    } else if (ledState.blue < MAX_COLOR_VALUE) {
                        ledState.blue += STEP;
                    } else {
                        ledState.phase = 0; // 重置为初始相位
                    }
                    break;
								case 20: // 白 -> 紫
                    if (ledState.red > 0) {
                        ledState.red -= STEP;
                    } else if (ledState.blue < MAX_COLOR_VALUE) {
                        ledState.blue += STEP;
                    } else {
                        ledState.phase++;
                    }
                    break;
                case 21: // 紫 -> 黑
                    if (ledState.blue > 0) {
                        ledState.blue -= STEP;
                    } else {
                        ledState.phase++;
                    }
                    break;
                case 22: // 黑 -> 青
                    if (ledState.blue < MAX_COLOR_VALUE) {
                        ledState.blue += STEP;
                    } else {
                        ledState.phase++;
                    }
                    break;
                case 23: // 青 -> 白
                    if (ledState.red < MAX_COLOR_VALUE) {
                        ledState.red += STEP;
                    } else if (ledState.green < MAX_COLOR_VALUE) {
                        ledState.green += STEP;
                    } else if (ledState.blue < MAX_COLOR_VALUE) {
                        ledState.blue += STEP;
                    } else {
                        ledState.phase++;
                    }
                    break;
                case 24: // 白 -> 红
                    if (ledState.green > 0) {
                        ledState.green -= STEP;
                    } else if (ledState.red < MAX_COLOR_VALUE) {
                        ledState.red += STEP;
                    } else {
                        ledState.phase++;
                    }
                    break;
                case 25: // 红 -> 黄
                    if (ledState.red > 0) {
                        ledState.red -= STEP;
                    } else if (ledState.green < MAX_COLOR_VALUE) {
                        ledState.green += STEP;
                    } else {
                        ledState.phase++;
                    }
                    break;
                case 26: // 黄 -> 蓝
                    if (ledState.green > 0) {
                        ledState.green -= STEP;
                    } else if (ledState.blue < MAX_COLOR_VALUE) {
                        ledState.blue += STEP;
                    } else {
                        ledState.phase++;
                    }
                    break;
                case 27: // 蓝 -> 绿
                    if (ledState.blue > 0) {
                        ledState.blue -= STEP;
                    } else if (ledState.red < MAX_COLOR_VALUE) {
                        ledState.red += STEP;
                    } else {
                        ledState.phase++;
                    }
                    break;
                case 28: // 绿 -> 红
                    if (ledState.blue > 0) {
                        ledState.blue -= STEP;
                    } else if (ledState.red < MAX_COLOR_VALUE) {
                        ledState.red += STEP;
                    } else {
                        ledState.phase++;
                    }
                    break;
                case 29: // 红 -> 黑
                    if (ledState.red > 0) {
                        ledState.red -= STEP;
                    } else {
                        ledState.phase = 0; // 重置为初始相位
                    }
                    break;
            }

            // 更新LED颜色
            LED_RGB(ledState.red, ledState.green, ledState.blue);
        }
		

				
		if(helloen==1)
		{
			hellocount++;	
			if(hellocount>30033)
			{
			hellocount=0;
			}
		}else{
			hellocount=0;
		}		
	
		
		
		randcount++;				
		if(randcount==100){
		randcount=0;	
		}
			if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2)==0)
			{
				scan_time ++;
			}
			else
			{
				scan_time=0;
				Key_KeyNumber=0;
			}
			if(scan_time>30)
			{ 
				scan_time=0;
				Key_KeyNumber=1;
			}
			TIM_ClearITPendingBit(TIM2, TIM_IT_Update); // 清除定时器中断标志位
	}
	
	
	
}

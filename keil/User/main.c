#include "led.h"
#include "key.h"
#include "Box_action.h"
int Key_KeyNumber=0;
int randcount=0;
int hellocount=0;
int helloen=0;
int judge=0;

const int colors[7][3] = {
    {255, 0, 0},    // 红
    {255, 165, 0},  // 橙
    {255, 255, 0},  // 黄
    {0, 255, 0},    // 绿
    {0, 255, 255},  // 青
    {0, 0, 255},    // 蓝
    {128, 0, 128}   // 紫
};

// 摩尔斯电码表
const char *morse_code[] = {
    ".-",    // A
    "-...",  // B
    "-.-.",  // C
    "-..",   // D
    ".",     // E
    "..-.",  // F
    "--.",   // G
    "....",  // H
    "..",    // I
    ".---",  // J
    "-.-",   // K
    ".-..",  // L
    "--",    // M
    "-.",    // N
    "---",   // O
    ".--.",  // P
    "--.-",  // Q
    ".-.",   // R
    "...",   // S
    "-",     // T
    "..-",   // U
    "...-",  // V
    ".--",   // W
    "-..-",  // X
    "-.--",  // Y
    "--.."   // Z
};


void setColor(int r, int g, int b) {
	LED_RGB(r,g,b);
}




void display_morse_code(const char *message) {
    int color_index = 0;

    for (int i = 0; message[i] != '\0'; i++) {
        char c = message[i];
        const char *code;

        if (c >= 'A' && c <= 'Z') {
            code = morse_code[c - 'A'];
        } else {
            continue;  // 忽略非字母字符
        }

        for (int j = 0; code[j] != '\0'; j++) {
            int r = colors[color_index % 7][0];
            int g = colors[color_index % 7][1];
            int b = colors[color_index % 7][2];
            setColor(r, g, b);

            if (code[j] == '.') {
                Delay_ms(20);  // 点的持续时间为200ms
            } else if (code[j] == '-') {
                Delay_ms(40);  // 划的持续时间为400ms
            }

            setColor(0, 0, 0);  // 点和划之间的间隔用灯灭表示
            Delay_ms(20);  // 点和划之间的间隔时间为200ms
            color_index++;
        }

        setColor(0, 0, 0);  // 字母间间隔用灯灭表示
        Delay_ms(60);  // 字母间间隔时间为600ms
    }

    setColor(0, 0, 0);  // 结束后灯灭
}

int main()
{
	
	

	int count=0;
	LEDPWM_Init();
  const char *message = "HELLOWORLD";
  display_morse_code(message);

	key_init();
	PWM_Init();
	boring_init();
//	trytry();
	TIM_Cmd(TIM4, DISABLE);
//	LED_RGB(225,225,225);
	

	while(1)
	{	
//		LED_RGB(255,0,0);
//		Delay_s(1);
//		LED_RGB(0,255,0);
//		Delay_s(1);
//		LED_RGB(0,0,255);
//		Delay_s(1);
			
//		Delay_s(1);
//		LED_RGB(225,225,255);
//		Delay_s(1);
//		action(1);




//			TIM_SetCompare1(TIM4, 500);
//			TIM_SetCompare2(TIM4, 500);
//			Delay_ms(1500);
//			TIM_SetCompare1(TIM4, 1500);
//			TIM_SetCompare2(TIM4, 1500);
//			Delay_ms(1500);
//			TIM_SetCompare1(TIM4, 2500);
//			TIM_SetCompare2(TIM4, 2500);
//			Delay_ms(1500);




			if(Key_KeyNumber==1) 
				{
					helloen=0;
					count=randcount;
					action(count%10);

				}else
				{
					helloen=1;
					judge=((count%5)*1000)+1000;
				}
							
				if(hellocount==judge)
				{
						waite(count%5);
						count=randcount;
				}

					
				
//				if(Key_KeyNumber==1) {
//				
//				LED_RGB(225,225,255);
//				
//				}else{
//				LED_RGB(0,0,0);
//				
//				}
					

	}

}


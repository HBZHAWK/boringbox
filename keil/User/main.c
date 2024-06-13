#include "led.h"
#include "key.h"
#include "Box_action.h"
int Key_KeyNumber=0;
int randcount=0;
int hellocount=0;
int helloen=0;
int judge=0;

const int colors[7][3] = {
    {255, 0, 0},    // ��
    {255, 165, 0},  // ��
    {255, 255, 0},  // ��
    {0, 255, 0},    // ��
    {0, 255, 255},  // ��
    {0, 0, 255},    // ��
    {128, 0, 128}   // ��
};

// Ħ��˹�����
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
            continue;  // ���Է���ĸ�ַ�
        }

        for (int j = 0; code[j] != '\0'; j++) {
            int r = colors[color_index % 7][0];
            int g = colors[color_index % 7][1];
            int b = colors[color_index % 7][2];
            setColor(r, g, b);

            if (code[j] == '.') {
                Delay_ms(20);  // ��ĳ���ʱ��Ϊ200ms
            } else if (code[j] == '-') {
                Delay_ms(40);  // ���ĳ���ʱ��Ϊ400ms
            }

            setColor(0, 0, 0);  // ��ͻ�֮��ļ���õ����ʾ
            Delay_ms(20);  // ��ͻ�֮��ļ��ʱ��Ϊ200ms
            color_index++;
        }

        setColor(0, 0, 0);  // ��ĸ�����õ����ʾ
        Delay_ms(60);  // ��ĸ����ʱ��Ϊ600ms
    }

    setColor(0, 0, 0);  // ���������
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


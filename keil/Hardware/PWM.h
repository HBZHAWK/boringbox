#include "stdint.h"
#ifndef __PWM_H
#define __PWM_H
 
void PWM_Init(void);
void PWM_SetCompare1(uint16_t Compare);
void PWM_SetCompare2(uint16_t Compare);
void Servo_SetAngle2(float Angle2);
void Servo_SetAngle1(float Angle1);

#endif

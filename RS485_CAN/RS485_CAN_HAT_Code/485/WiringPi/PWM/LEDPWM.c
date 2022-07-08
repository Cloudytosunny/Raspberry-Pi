#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>
// 定义控制LED灯的GPIO引脚，使用GPIO0
#define PWM_PIN     0
int main(void)
{
    int bright ;
    printf("wiringPi-C Software PWM test program\n") ;
    // 初始化
    wiringPiSetup();
    pinMode(PWM_PIN, OUTPUT);
    softPwmCreate(PWM_PIN, 0, 100);
    while(1) {
        for(bright = 0; bright < 100; bright++) {
            softPwmWrite(PWM_PIN, bright);
            delay(10);
        }
        for(bright = 100; bright >= 0; bright--) {
            softPwmWrite(PWM_PIN, bright);
            delay(10);
        }
    }
    return 0 ;
}

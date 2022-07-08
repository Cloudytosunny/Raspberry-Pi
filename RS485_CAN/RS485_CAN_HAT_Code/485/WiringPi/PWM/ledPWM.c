#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>
// 设置GPIO1为LED灯的控制引脚
#define PWM_PIN    23
int main(void)
{
    int bright ;
    printf("wiringPi-C PWM test program\n") ;
    // 配置gpio
    wiringPiSetup();
    // 配置GPIO1为PWM模式
    pinMode(PWM_PIN, PWM_OUTPUT);
    while(1) {
        for(bright = 0 ; bright < 1000; bright++) {
            // bright为 0 ~ 1000，最大是1023
            pwmWrite(PWM_PIN, bright);
            delay(1) ;
        }
        for(bright = 1000; bright >= 0; bright--) {
            pwmWrite(PWM_PIN, bright);
            delay(1) ;
        }
    }
    return 0 ;
}

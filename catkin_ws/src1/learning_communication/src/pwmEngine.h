#include <softPwm.h>
#include <wiringPi.h>
#include <stdio.h>




#define pwmpin 0

#define mode PWM_MODE_MS


class PWMEngine
{
private:
        int fd;
 
public:



void InitPWM(void)
{
    wiringPiSetup();
    pinMode(pwmpin, OUTPUT);
    softPwmCreate(pwmpin, 0, 300);
    printf("PWM is OPEN");

}


void SetPWM(int con)
        {
            softPwmWrite(pwmpin, con);
            printf("PWM is OPEN %d" , con);
        }

};

#include <wiringSerial.h>
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>     //exit()
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <sys/time.h>

// if use half-auto, EN_485 = LOW is Receiver, EN_485 = HIGH is Send
#define MODE 0 //mode = 0 is full-guto, mode = 1 is half-auto
#define EN_485 4
#define UART_DEV "/dev/ttyAMA0"
char leftstop[] = {0x3E, 0x80, 0x01, 0x00, 0xBF};
char rightstop[] = {0x3E, 0x80, 0x02, 0x00, 0xC0};

char left0[] = {0x3E, 0xA2, 0x01, 0x04, 0xE5, 0x00, 0x00, 0x00, 0x00, 0x00};
char left100[] = {0x3E, 0xA2, 0x01, 0x04, 0xE5, 0x10, 0x27, 0x00, 0x00, 0x37};
char left500[] = {0x3E, 0xA2, 0x01, 0x04, 0xE5, 0x50, 0xC3, 0x00, 0x00, 0x13};
char left1000[] = {0x3E, 0xA2, 0x01, 0x04, 0xE5, 0xA0, 0x86, 0x01, 0x00, 0x27};
char left2000[] = {0x3E, 0xA2, 0x01, 0x04, 0xE5, 0x40, 0x0D, 0x03, 0x00, 0x50};
char left3000[] = {0x3E, 0xA2, 0x01, 0x04, 0xE5, 0xE0, 0x93, 0x04, 0x00, 0x77};
char left_100[] = {0x3E, 0xA2, 0x01, 0x04, 0xE5, 0xF0, 0xD8, 0xFF, 0xFF, 0xC6};
char left_500[] = {0x3E, 0xA2, 0x01, 0x04, 0xE5, 0xB0, 0x3C, 0xFF, 0xFF, 0xEA};
char left_1000[] = {0x3E, 0xA2, 0x01, 0x04, 0xE5, 0x6F, 0x8A, 0xFE, 0xFF, 0xF6};
char left_2000[] = {0x3E, 0xA2, 0x01, 0x04, 0xE5, 0xC0, 0xF2, 0xFC, 0xFF, 0xAD};
char left_3000[] = {0x3E, 0xA2, 0x01, 0x04, 0xE5, 0x20, 0x6C, 0xFB, 0xFF, 0x86};

char right0[] = {0x3E, 0xA2, 0x02, 0x04, 0xE6, 0x00, 0x00, 0x00, 0x00, 0x00};
char right100[] = {0x3E, 0xA2, 0x02, 0x04, 0xE6, 0x10, 0x27, 0x00, 0x00, 0x37};
char right500[] = {0x3E, 0xA2, 0x02, 0x04, 0xE6, 0x50, 0xC3, 0x00, 0x00, 0x13};
char right1000[] = {0x3E, 0xA2, 0x02, 0x04, 0xE6, 0xA0, 0x86, 0x01, 0x00, 0x27};
char right2000[] = {0x3E, 0xA2, 0x02, 0x04, 0xE6, 0x40, 0x0D, 0x03, 0x00, 0x50};
char right3000[] = {0x3E, 0xA2, 0x02, 0x04, 0xE6, 0xE0, 0x93, 0x04, 0x00, 0x77};
char right_100[] = {0x3E, 0xA2, 0x02, 0x04, 0xE6, 0xF0, 0xD8, 0xFF, 0xFF, 0xC6};
char right_500[] = {0x3E, 0xA2, 0x02, 0x04, 0xE6, 0xB0, 0x3C, 0xFF, 0xFF, 0xEA};
char right_1000[] = {0x3E, 0xA2, 0x02, 0x04, 0xE6, 0x6F, 0x8A, 0xFE, 0xFF, 0xF6};
char right_2000[] = {0x3E, 0xA2, 0x02, 0x04, 0xE6, 0xC0, 0xF2, 0xFC, 0xFF, 0xAD};
char right_3000[] = {0x3E, 0xA2, 0x02, 0x04, 0xE6, 0x20, 0x6C, 0xFB, 0xFF, 0x86};

class RS485
{
    private:
        int fd;
            void  Handler(int signo)
            {
                //System Exit
                printf("\r\nHandler:serialClose \r\n");
                serialClose(fd);

                exit(0);
            }   
public:



void InitRS485(void)
{
    if(MODE == 1){
        if(wiringPiSetupGpio() < 0) { //use BCM2835 Pin number table
            printf("set wiringPi lib failed	!!! \r\n");
            // return 1;
        } else {
            printf("set wiringPi lib success  !!! \r\n");
        }
        pinMode(EN_485, OUTPUT);
        digitalWrite(EN_485,HIGH);
    }

    printf("use device %s\r\n", UART_DEV);
    if((fd = serialOpen(UART_DEV, 115200)) < 0) {
        printf("serial err\n");
        // return -1;
    }

    serialFlush(fd);
    serialPrintf(fd,"\r");
    char str[] = "hello world\n";
    printf("send data：%s\r\n", str);
    //serialPuts(fd, str);
    // return 0;
}


void Send(int speedclass,int motor)
        {
        if(motor == 1){
          if(speedclass==1){write(fd,left500,sizeof(left500));}
          if(speedclass==0){write(fd,left0,sizeof(left0));}
          if(speedclass==2){write(fd,left1000,sizeof(left1000));}
          if(speedclass==3){write(fd,left2000,sizeof(left2000));}
          if(speedclass==4){write(fd,left3000,sizeof(left3000));}
          
          if(speedclass==-1){write(fd,left_500,sizeof(left_500));}
          if(speedclass==-2){write(fd,left_1000,sizeof(left_1000));}
          if(speedclass==-3){write(fd,left_2000,sizeof(left_2000));}
          if(speedclass==-4){write(fd,left_3000,sizeof(left_3000));}
         }
         else if(motor == 2){
          if(speedclass==1){write(fd,right500,sizeof(right500));}
          if(speedclass==0){write(fd,right0,sizeof(right0));}
          if(speedclass==2){write(fd,right1000,sizeof(right1000));}
          if(speedclass==3){write(fd,right2000,sizeof(right2000));}
          if(speedclass==4){write(fd,right3000,sizeof(right3000));} 
            
          if(speedclass==-1){write(fd,right_500,sizeof(right_500));}
          if(speedclass==-2){write(fd,right_1000,sizeof(right_1000));}
          if(speedclass==-3){write(fd,right_2000,sizeof(right_2000));}
          if(speedclass==-4){write(fd,right_3000,sizeof(right_3000));}       
         }
         else {
               write(fd,rightstop,sizeof(rightstop));
               printf("rightstop\n");
               write(fd,leftstop,sizeof(leftstop));
               printf("leftstop\n");
         }

        }

void SendClose()
        {
                serialClose(fd);
        }

};


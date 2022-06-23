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


RS485()
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
    serialPuts(fd, str);
    // return 0;
}

~RS485();

void Send()
        {
            int str_buf[] = 0x3E, 0xA2, 0x01, 0x04, 0xE5, 0x10, 0x27, 0x00, 0x00, 0x37;
            serialPuts(fd, str_buf);
        }

void SendClose()
        {
                serialClose(fd);
        }

}


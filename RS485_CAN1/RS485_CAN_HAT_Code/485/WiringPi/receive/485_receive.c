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

int fd;

void  Handler(int signo)
{
    //System Exit
    printf("\r\nHandler:serialClose \r\n");
    serialClose(fd);

    exit(0);
}

int main(void)
{
    // Exception handling:ctrl + c
    signal(SIGINT, Handler);

    if(MODE == 1){
        if(wiringPiSetupGpio() < 0) { //use BCM2835 Pin number table
            printf("set wiringPi lib failed	!!! \r\n");
            return 1;
        } else {
            printf("set wiringPi lib success  !!! \r\n");
        }
        pinMode(EN_485, OUTPUT);
        digitalWrite(EN_485,LOW);
    }

    if((fd = serialOpen(UART_DEV, 115200)) < 0) {
        printf("serial err\n");
        return -1;
    }
    printf("use device %s\r\n", UART_DEV);

    printf("You can always receive data, press Ctrl + C to exit\r\n");
    char str;
    for (;;) {
        str = serialGetchar(fd);
        if(str < 128) // ascii
            printf("%c", str);
        fflush(stdout); // Empty the output buffer and output the contents of the buffer
    }
    return 0;
}

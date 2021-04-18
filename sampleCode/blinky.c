/*
============================================================================
Name : BlinkyLED.c
Author :
Version :
Copyright : Your copyright notice
Description : Simple Hardware access example that blinks user-LED4
============================================================================
*/
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h> 
//defining the path to the file in the filesystem that controls the LED
#define LED4 "/sys/class/leds/apq8016-sbc:green:user3/brightness"
int main(void)
{
    //opening the brightness-file
    int led4_fd = open(LED4, O_WRONLY);
    if (led4_fd < 0)
    {
        printf("Could not open File: %s", LED4);
        return 0;
    }
    int i;
    for (i = 0; i < 10; i++)
    {
        //Blinky code
        write(led4_fd, "1", 2); //Turning the LED ON by writing 1 into the brightness file
        sleep(1);
        write(led4_fd, "0", 2); //Turning the LED OFF by writing 0 into the brightness file
        sleep(1);
    }
    close(led4_fd);
}
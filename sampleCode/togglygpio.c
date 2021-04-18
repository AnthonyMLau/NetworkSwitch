/*
============================================================================
Name : TogglyGPIO.c
Author :
Version :
Copyright : Your copyright notice
Description : Basic Hardware access, Ansi-style
============================================================================
*/
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#define MAX_BUF 50
#define GPIO_A 36
#define GPIO_B 12

int Export_GPIO(int gpio);
int UnExport_GPIO(int gpio);
int Write_GPIO(int gpio, int value);
int Read_GPIO(int gpio, int *value);

int main(void)
{
    char c = ' ';
    int ret;
    int out_value = 1;
    int in_value = 0;
    //
    //exporting GPIO’s
    //
    ret = Export_GPIO(GPIO_A);
    if (ret != 0)
        printf("Error exporting GPIO_%d \n", GPIO_A);
    ret = Export_GPIO(GPIO_B);
    if (ret != 0)
        printf("Error exporting GPIO_%d \n", GPIO_B);
    //
    //writing/reading GPIO’s
    //
    printf("press any key to toggle GPIO_A or 'q' to quit:\n");
    while (c != 'q')
    {
        printf("Writing GPIO_%d: value=%d \n", GPIO_A, out_value);
        ret = Write_GPIO(GPIO_A, out_value);
        if (ret != 0)
            printf("Error writing GPIO_%d \n", GPIO_A);
        ret = Read_GPIO(GPIO_B, (int *)&in_value);
        if (ret != 0)
            printf("Error reading GPIO_%d", GPIO_B);
        printf("Reading GPIO_%d: value=%d \n", GPIO_B, in_value);
        out_value = !out_value;
        c = getchar();
    }
    //
    //UnExporting GPIO’s
    //
    ret = UnExport_GPIO(GPIO_A);
    if (ret != 0)
        printf("Error UnExporting GPIO_%d \n", GPIO_A);
    ret = UnExport_GPIO(GPIO_B);
    if (ret != 0)
        printf("Error UnExporting GPIO_%d \n", GPIO_B);
    return 0;
}
int Export_GPIO(int gpio)
{
    int fd;
    char buf[MAX_BUF];
    //Export the specific GPIO
    //this will create a new folder with the gpio name
    sprintf(buf, "%d", gpio);
    fd = open("/sys/class/gpio/export", O_WRONLY);
    if (fd < 0)
        return -1;
    write(fd, buf, strlen(buf));
    close(fd);
    return 0;
}
int UnExport_GPIO(int gpio)
{
    int fd;
    char buf[MAX_BUF];
    sprintf(buf, "%d", gpio);
    fd = open("/sys/class/gpio/unexport", O_WRONLY);
    if (fd < 0)
        return -1;
    write(fd, buf, strlen(buf));
    close(fd);
    return 0;
}
int Write_GPIO(int gpio, int value)
{
    int fd;
    char buf[MAX_BUF];
    //Set the direction of the GPIO to output
    sprintf(buf, "/sys/class/gpio/gpio%d/direction", gpio);
    fd = open(buf, O_WRONLY);
    if (fd < 0)
        return -1;
    write(fd, "out", 3); // Set out direction
    close(fd);
    sprintf(buf, "/sys/class/gpio/gpio%d/value", gpio);
    fd = open(buf, O_WRONLY);
    if (fd < 0)
        return -1;
    // Write the GPIO value
    sprintf(buf, "%d", value);
    write(fd, buf, strlen(buf));
    close(fd);
    return 0;
}
int Read_GPIO(int gpio, int *value)
{
    int fd;
    char val;
    char buf[MAX_BUF];
    sprintf(buf, "/sys/class/gpio/gpio%d/value", gpio);
    fd = open(buf, O_RDONLY);
    if (fd < 0)
        return -1;
    // Read the GPIO value
    read(fd, &val, 1);
    *value = atoi(&val);
    close(fd);
    return 0;
}
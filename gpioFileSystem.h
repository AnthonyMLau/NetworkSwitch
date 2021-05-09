#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>


void exportPin(int pin){
    int fd;
    char buf[100];
    //Export the specific GPIO
    //this will create a new folder with the gpio name
    sprintf(buf, "%d", pin);
    fd = open("/sys/class/gpio/export", O_WRONLY);
    if (fd < 0){
        perror("Unable to open /sys/class/gpio/export");
    }
    write(fd, buf, strlen(buf));
    close(fd);
    return;
}

void setDirectionOut(int pin){
    // Set the pin to be an output by writing "out" to /sys/class/gpio/gpio24/direction
    int fd;
    char buf[100];
    //Set the direction of the GPIO to output
    sprintf(buf, "/sys/class/gpio/gpio%d/direction", pin);
    fd = open(buf, O_WRONLY);
    if (fd < 0){
        perror("Unable to open /sys/class/gpio/export");
    }
    write(fd, "out", 3); // Set out direction
    close(fd);
}

void setDirectionIn(int fd, int pin){
    // Set the pin to be an output by writing "in" to /sys/class/gpio/gpio24/direction
    int fd;
    char buf[100];
    //Set the direction of the GPIO to output
    sprintf(buf, "/sys/class/gpio/gpio%d/direction", pin);
    fd = open(buf, O_WRONLY);
    if (fd < 0){
        perror("Unable to open /sys/class/gpio/export");
    }
    write(fd, "in", 2); // Set in direction
    close(fd);
}

void writePin(int fd, int pin, char val){
    if (fd == -1) {
        perror("Unable to open /sys/class/gpio/export");
        return;
    }
    write(fd, &val, 1);
}

void readPin(int fd, int pin, char &val){
    if (fd == -1) {
        perror("Unable to open /sys/class/gpio/export");
        return;
    }
    read(fd, &val, 1);
}
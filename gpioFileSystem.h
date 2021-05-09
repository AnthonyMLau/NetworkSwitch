#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

void exportPin(int pin, int fd){
    //int fd = open("/sys/class/gpio/export", O_WRONLY);
    if (fd == -1) {
        perror("Unable to open /sys/class/gpio/export");
        exit(1);
    }
    if (write(fd, "418", 3) != 3) { //TODO fix hardcoded stuff
        perror("Error writing to /sys/class/gpio/export");
        exit(1);
    }
    //close(fd);
}

void setDirection(int pin, int fd){
    // Set the pin to be an output by writing "out" to /sys/class/gpio/gpio24/direction
    //fd = open("/sys/class/gpio/gpio418/direction", O_WRONLY);
    if (fd == -1) {
        perror("Unable to open /sys/class/gpio/gpio24/direction");
        exit(1);
    }
    if (write(fd, "out", 3) != 3) {
        perror("Error writing to /sys/class/gpio/gpio418/direction");
        exit(1);
    }
    //close(fd);
}

void writePin(){
    
}

void readPin(){
    
}
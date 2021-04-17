#include <time.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int togglePin(int fd){
    for (int i = 0; i < 500000; i++) {
        write(fd, "1", 1);
        write(fd, "0", 1);
    }
}


int main(){
    // export pin
    int fd = open("/sys/class/gpio/export", O_WRONLY);
    if (fd == -1) {
        perror("Unable to open /sys/class/gpio/export");
        exit(1);
    }
    if (write(fd, "418", 3) != 3) {
        perror("Error writing to /sys/class/gpio/export");
        exit(1);
    }
    close(fd);


    // Set the pin to be an output by writing "out" to /sys/class/gpio/gpio24/direction
    fd = open("/sys/class/gpio/gpio418/direction", O_WRONLY);
    if (fd == -1) {
        perror("Unable to open /sys/class/gpio/gpio24/direction");
        exit(1);
    }
    if (write(fd, "out", 3) != 3) {
        perror("Error writing to /sys/class/gpio/gpio418/direction");
        exit(1);
    }
    close(fd);

    // open pin value for writing
    fd = open("/sys/class/gpio/gpio418/value", O_WRONLY);
    if (fd == -1) {
        perror("Unable to open /sys/class/gpio/gpio418/value");
        exit(1);
    }


    clock_t t;
    t = clock();

    togglePin(fd);

    t = clock() - t;
    double seconds = ((float)t)/CLOCKS_PER_SEC;
    printf("Time taken in seconds: %f, aka %f MHz", seconds, 1000000/seconds/1000000);
    


    close(fd);


    // unexport pin
    fd = open("/sys/class/gpio/unexport", O_WRONLY);
    if (fd == -1) {
        perror("Unable to open /sys/class/gpio/unexport");
        exit(1);
    }
    if (write(fd, "418", 3) != 3) {
        perror("Error writing to /sys/class/gpio/unexport");
        exit(1);
    }
    close(fd);
}
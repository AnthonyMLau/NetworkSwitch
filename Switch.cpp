#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


#include "EthernetFrame.h"
#include "MACAddress.h"
#include "gpioFileSystem.h"
#include "circular_queue.h"

#define MAXPORTS 10
#define pinIn 418
#define pinOut 394
#define BUFFER_SIZE 10000

int addressTable[MAXPORTS][2];
CircularQueue buffers[MAXPORTS];



// template <size_t rows, size_t cols>
// void readFile(bool (&buf)[rows][cols], int len){
//     for (int i = 0; i < len; i++){
//         buf[i] = readPin();
//     }
    
// }

void *readInputSignals(void * arg){
    //read 64 bits - preamble + SFD (TODO)
    
    
    //put in process buffer

    //For now, to test logic I will just use a big array with random values and some ethernet frames instead of reading input signals

}

void *writeOutputSignals(void * arg){
    //write bits to correct port/pin
}

// TODO: fix args
void *processData(void * arg){
    int in_port = *(int*)(arg);
    free(arg);

    //detect start of frame (use a FSM to detect match the start of frame sequence)
    char prev = -1;
    char curr = -1;
    int count = 0;
    while(true){ //7 of 0xAA, aka 21 pairs of 0b10
        curr = buffers[in_port].popFront();
        if(curr == 1 && prev == -1){
            count = 1;
        }else if ((curr == 1 && prev == 0) || (curr == 0 && prev == 1)){
            count += 1;
        }
    }

    //compare data and find correct output port
    //put in output buffer

}

void setup(){
    // fill all values in addressTable to 0
    for (int i = 0; i < MAXPORTS; i++){
        for (int j = 0; j < 2; j++)
        {
            addressTable[i][j] = 0;
        }
    }
    
    //pin setup
    exportPin(pinIn);
    setDirectionOut(pinIn);

    exportPin(pinOut);
    setDirectionIn(pinOut);
}

int main (int argc, char *argv[]){
    // address : port #
    //std::map<long long int, int> addressTable;

    setup();

    for (size_t i = 0; i < MAXPORTS; i++){
        buf_arrs[i] = CircularQueue(BUFFER_SIZE);
    }
    

    

    // todo: set thread affinity to separate cores for input and output
    // todo: multiple i/o for multiple signals 
    // pthread_t input;
    // pthread_t output;
    // pthread_t analyze;

    // pthread_create(&input, NULL, readInputSignals, NULL);
    // pthread_create(&input, NULL, writeOutputSignals, NULL);
    // pthread_create(&input, NULL, processData, NULL);

    
}
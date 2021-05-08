#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


#include "EthernetFrame.h"
#include "MACAddress.h"

#define MAXPORTS 10

int addressTable[MAXPORTS][2];

void *readInputSignals(void * arg){
    //get destination and source addr
    //get and allocate size
    //write data into mem
    //put in process buffer

}

void *writeOutputSignals(void * arg){
    //write bits to correct port/pin
}

void *processData(void * arg){
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
    
}

int main (int argc, char *argv[]){
    // address : port #
    //std::map<long long int, int> addressTable;

    setup();

    // todo: set thread affinity to separate cores for input and output
    // todo: multiple i/o for multiple signals 
    pthread_t input;
    pthread_t output;
    pthread_t analyze;

    pthread_create(&input, NULL, readInputSignals, NULL);
    pthread_create(&input, NULL, writeOutputSignals, NULL);
    pthread_create(&input, NULL, processData, NULL);

    
}
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


#include "EthernetFrame.h"
#include "MACAddress.h"

void *readInputSignals(void * arg){

}

void *writeOutputSignals(void * arg){
    
}

void *processData(void * arg){
    
}

int main (int argc, char *argv[]){
    // address : port #
    std::map<long long int, int> addressTable;


    // todo: set thread affinity to separate cores for input and output
    // todo: multiple i/o for multiple signals 
    pthread_t input;
    pthread_t output;
    pthread_t analyze;

    pthread_create(&input, NULL, readInputSignals, NULL);
    pthread_create(&input, NULL, writeOutputSignals, NULL);
    pthread_create(&input, NULL, processData, NULL);

    
}
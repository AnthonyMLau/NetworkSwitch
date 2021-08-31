#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <algorithm>


#include "EthernetFrame.h"
#include "MACAddress.h"
#include "gpioFileSystem.h"
#include "circular_queue.h"

#define MAXPORTS 10
#define pinIn 418
#define pinOut 394
#define BUFFER_SIZE 10000

int connectedPorts[MAXPORTS] = {1, 1, 0, 0, 0, 0, 0, 0, 0, 0};

long long int addressTable[MAXPORTS]; //addressTable[port] = mac addr
CircularQueue in_buffers[MAXPORTS];
CircularQueue out_buffers[MAXPORTS];
std::thread threads[MAXPORTS];



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
void *processData(int in_port){


    //detect start of frame with FSM
    char prev = -1;
    char curr = -1;
    int count = 0;
    while(count < 64){
        prev = curr;
        curr = in_buffers[in_port].popFront();

        // detect last "1" which is a consecutive 1
        if(count == 63 && curr == 1 && prev == 1){
            count += 1;
        }else{
            continue;
        }

        if ((curr == 1 && prev == 0) || (curr == 0 && prev == 1)){
            count += 1;
        }else if(curr == 1){
            count = 1;
        }else{
            count = 0;
        }
    }

    // read source and destination addresses (6 octets each)
    long long int source_addr = 0;
    for (size_t i = 0; i < (6*8); i++){
        source_addr += (bool) in_buffers[in_port].popFront();
        source_addr <<= 1;
    }
    addressTable[in_port] = source_addr;

    long long int dest_addr = 0;
    for (size_t i = 0; i < (6*8); i++){
        dest_addr += (bool) in_buffers[in_port].popFront();
        dest_addr <<= 1;
    }
    
    //search address table
    long long int* item = std::find(std::begin(addressTable), std::end(addressTable), source_addr);

    if(item == std::end(addressTable)){
        // address not found, broadcast to all ports
        broadcastData();
    }else{
        int index = std::distance(addressTable, item);
        sendData(addressTable[index]);
    }

    

    //compare data and find correct output port
    //put in output buffer

}

void setup(){
    // fill all values in addressTable to 0
    for (int i = 0; i < MAXPORTS; i++){
            addressTable[i] = 0;
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
        in_buffers[i] = CircularQueue(BUFFER_SIZE);
    }
    

    

    // todo: set thread affinity to separate cores for input and output
    // todo: multiple i/o for multiple signals 
    for (size_t i = 0; i < MAXPORTS; i++){
        if(connectedPorts[i]){
            threads[i] = std::thread(processData, i);
        }
    }
    
    for (size_t i = 0; i < MAXPORTS; i++){
        if(connectedPorts[i]){
            threads[i].join();
        }
    }
    
    
}
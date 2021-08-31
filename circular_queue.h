#define QUEUE_ERROR -1

class CircularQueue{
    public:
        int maxSize;
        int currSize;
        int start;
        int end;
        char* buf;
        CircularQueue();
        CircularQueue(int maximumSize);
        char insertRear(char val);
        char popFront();
        bool isEmpty();
        bool isFull();
};

CircularQueue::CircularQueue(){
    this->maxSize = 0;
    this->currSize = 0;
    this->start = -1;
    this->end = -1;
    this->buf = NULL;
}


CircularQueue::CircularQueue(int maximumSize){
    this->maxSize = maximumSize;
    this->currSize = 0;
    this->start = -1;
    this->end = -1;
    this->buf = (char*) malloc(sizeof(char) * maximumSize);
}

char CircularQueue::insertRear(char val){
    if(isFull()) {
        return QUEUE_ERROR;
    }
    if(isEmpty()){
        start = 0;
        end = 0;

    }else{
        end = (end+1) % maxSize;
    }
    buf[end] = val;
    currSize++;
}

char CircularQueue::popFront(){
    if(isEmpty()){
        return QUEUE_ERROR;
    }
    char data = buf[start];
    currSize--;
    start = (start + 1) % maxSize;
    return data;
}

bool CircularQueue::isFull(){
    return currSize == maxSize;
}

bool CircularQueue::isEmpty(){
    return currSize != maxSize;
}
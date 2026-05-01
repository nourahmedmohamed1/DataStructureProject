#ifndef QUEUE_H
#define QUEUE_H

 

class CircularQueue {
private:
    int *items;
    int front;
    int rear;
    int capacity;

public:
    CircularQueue();
    ~CircularQueue(int size);

    bool isFull();
    bool isEmpty();

    void enqueue(int element);
    int dequeue();
};

 

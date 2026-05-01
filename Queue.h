#ifndef QUEUE_H
#define QUEUE_H

#define SIZE 5

class CircularQueue {
private:
    int items[SIZE];
    int front;
    int rear;

public:
    CircularQueue();

    bool isFull();
    bool isEmpty();

    void enqueue(int element);
    int dequeue();
};

#endif

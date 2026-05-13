#ifndef QUEUECIRC_H
#define QUEUECIRC_H

// CircularQueue: array-based circular queue with fixed capacity.
// front/rear wrap around using modulo arithmetic. O(1) enqueue/dequeue.
class CircularQueue {
private:
    int* items;
    int  front;
    int  rear;
    int  capacity;

public:
    CircularQueue(int size);
    ~CircularQueue();

    bool isFull();
    bool isEmpty();

    void enqueue(int element);
    int  dequeue();
};

#endif // QUEUECIRC_H

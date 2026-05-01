#ifndef QUEUE_H
#define QUEUE_H

#include "Node.h"
class QueueLinkedList{
private:
    Node *front;
    Node *rear;

public:
    QueueLinkedList();          // Points to the first (oldest) element
    ~QueueLinkedList();         // Points to the last  (newest) element
    void enqueue(int value);            // Add a new element to the rear
    int dequeue();
    bool isEmpty();         // Check if the queue has no elements
    bool isFull();        // Always returns false (linked list is unbounded)        
};
#endif
#ifndef QUEUELL_H
#define QUEUELL_H

#include "Node.h"

// QueueLinkedList: queue implemented with a singly linked list.
// front -> oldest element (dequeue end), rear -> newest (enqueue end).
// O(1) for both enqueue and dequeue.
class QueueLinkedList {
private:
    Node* front;
    Node* rear;

public:
    QueueLinkedList();
    ~QueueLinkedList();

    void enqueue(int value);
    int  dequeue();
    bool isEmpty();
    bool isFull();   // always false (unbounded)
};

#endif // QUEUELL_H

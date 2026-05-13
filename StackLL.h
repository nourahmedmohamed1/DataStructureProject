#ifndef STACKLL_H
#define STACKLL_H

#include "Node.h"

// StackLinkedList: a stack implemented using a singly linked list.
// 'top' always points to the most recently added node (O(1) push/pop/peek).
class StackLinkedList {
private:
    Node* top;
public:
    StackLinkedList();
    ~StackLinkedList();

    void push(int value);
    int  pop();
    int  peek();
    bool isEmpty();
};

#endif // STACKLL_H

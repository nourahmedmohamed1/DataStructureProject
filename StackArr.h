#ifndef STACK_H
#define STACK_H

#include "Node.h"

class StackArray {
private:
    int* arr;
    int top;
    int capacity;

public:
    StackArray(int cap);
    ~StackArray();
    void push(int value);
    int  pop();
    int  peek();
    bool isFull();
    bool isEmpty();
};

class StackLL {
private:
    Node* top;
public:
    StackLL();
    ~StackLL();
    void push(int value);
    int pop();
    int peek();
    bool isEmpty();
};
#endif

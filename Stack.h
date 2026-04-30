#ifndef STACK_H
#define STACK_H

class StackArray {
private:
    int* arr;
    int top;
    int capacity;

public:
    StackArray(int cap);
    void push(int value);
    int  pop();
    int  peek();
    bool isFull();
    bool isEmpty();
};

#endif
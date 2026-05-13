#include "StackArr.h"
#include <iostream>

StackArray::StackArray(int cap) {
    capacity = cap;
    arr = new int[capacity];
    top = -1;
}

StackArray::~StackArray() {
    delete[] arr;
}

bool StackArray::isEmpty() {
    return top == -1;
}

bool StackArray::isFull() {
    return top == capacity - 1;
}

void StackArray::push(int value) {
    if (isFull()) {
        std::cout << "Stack Overflow! Cannot push " << value << ", stack is full.\n";
        return;
    }
    arr[++top] = value;
}

int StackArray::pop() {
    if (isEmpty()) {
        std::cout << "Stack Underflow! Cannot pop, stack is empty.\n";
        return -1;
    }
    return arr[top--];
}

int StackArray::peek() {
    if (isEmpty()) {
        std::cout << "Stack is empty! Nothing to peek.\n";
        return -1;
    }
    return arr[top];
}

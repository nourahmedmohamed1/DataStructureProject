#include "StackArr.h"
#include <iostream>
#include <iomanip>

StackArray::StackArray(int cap) {
    capacity = cap;
    arr      = new int[capacity];
    top      = -1;
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
        std::cout << "Stack Overflow! Cannot push " << value
                  << ". Stack is full (capacity = " << capacity << ").\n";
        return;
    }
    arr[++top] = value;
    std::cout << "Pushed " << value << " onto the stack. (size = " << top + 1 << "/" << capacity << ")\n";
}

int StackArray::pop() {
    if (isEmpty()) {
        std::cout << "Stack Underflow! Cannot pop. Stack is empty.\n";
        return -1;
    }
    int val = arr[top--];
    std::cout << "Popped " << val << " from the stack. (size = " << top + 1 << "/" << capacity << ")\n";
    return val;
}

int StackArray::peek() {
    if (isEmpty()) {
        std::cout << "Stack is empty. Nothing to peek.\n";
        return -1;
    }
    std::cout << "Top of stack: " << arr[top] << "\n";
    return arr[top];
}

void StackArray::display() {
    if (isEmpty()) {
        std::cout << "  Stack is empty.\n";
        return;
    }
    std::cout << "  +-------+\n";
    // Filled slots: from TOP down to index 0
    for (int i = top; i >= 0; i--) {
        std::cout << "  |" << std::setw(6) << arr[i] << " |";
        if      (i == top && i == 0) std::cout << " <- TOP & BOTTOM";
        else if (i == top)           std::cout << " <- TOP";
        else if (i == 0)             std::cout << " <- BOTTOM";
        std::cout << "\n  +-------+\n";
    }
    // Empty slots below
    for (int i = top + 1; i < capacity; i++) {
        std::cout << "  | [---] |  (empty)\n  +-------+\n";
    }
}

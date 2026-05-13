#include "StackLL.h"
#include <iostream>
using namespace std;

StackLinkedList::StackLinkedList() {
    top = nullptr;
}

StackLinkedList::~StackLinkedList() {
    while (!isEmpty()) pop();
}

void StackLinkedList::push(int value) {
    Node* newNode  = new Node();
    newNode->data  = value;
    newNode->next  = top;
    top            = newNode;
    cout << "Pushed " << value << " onto the stack.\n";
}

int StackLinkedList::pop() {
    if (isEmpty()) {
        cout << "Stack Underflow! Cannot pop. Stack is empty.\n";
        return -1;
    }
    Node* temp = top;
    int   val  = top->data;
    top        = top->next;
    delete temp;
    cout << "Popped " << val << " from the stack.\n";
    return val;
}

int StackLinkedList::peek() {
    if (isEmpty()) {
        cout << "Stack is empty. Nothing to peek.\n";
        return -1;
    }
    cout << "Top of stack: " << top->data << "\n";
    return top->data;
}

bool StackLinkedList::isEmpty() {
    return top == nullptr;
}

void StackLinkedList::display() {
    if (isEmpty()) {
        cout << "  Stack is empty.\n";
        return;
    }
    cout << "  TOP";
    Node* cur = top;
    while (cur != nullptr) {
        cout << " -> [" << cur->data << "]";
        cur = cur->next;
    }
    cout << " -> nullptr\n";
}

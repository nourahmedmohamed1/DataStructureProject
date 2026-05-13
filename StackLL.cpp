#include "StackLL.h"
#include <iostream>
using namespace std;

// Constructor: start with an empty stack
StackLinkedList::StackLinkedList() {
    top = nullptr;
}

// Destructor: pop every node to free all heap memory
StackLinkedList::~StackLinkedList() {
    while (!isEmpty()) {
        pop();
    }
}

// push: create a new node and place it at the top
void StackLinkedList::push(int value) {
    Node* newNode = new Node();
    newNode->data = value;
    newNode->next = top;
    top = newNode;
}

// pop: remove the top node and return its value
int StackLinkedList::pop() {
    if (isEmpty()) {
        cout << "Error: Can't pop from an empty stack.\n";
        return -1;
    }
    Node* temp = top;
    int value  = top->data;
    top        = top->next;
    delete temp;
    return value;
}

// peek: return the top value WITHOUT removing it
int StackLinkedList::peek() {
    if (isEmpty()) {
        cout << "Error: Can't peek an empty stack.\n";
        return -1;
    }
    return top->data;
}

// isEmpty: returns true if there are no nodes
bool StackLinkedList::isEmpty() {
    return top == nullptr;
}

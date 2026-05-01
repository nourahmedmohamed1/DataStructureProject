#ifndef STACK_H
#define STACK_H

#include "Node.h"
// StackLinkedList: A stack implemented using a singly linked list.
// The 'top' pointer always points to the most recently added node.
class StackLinkedList{
private:
// Points to the top element of the stack    
Node* top;      
public:
    // Constructor: initializes an empty stack    
    StackLinkedList();      
    // Destructor: frees all allocated memory
    ~StackLinkedList();          
    
    // Add a new element to the top
    void push(int value);    
    // Remove and return the top element   
    int pop();
    // Return the top element WITHOUT removing it
    int peek();
    // Check if the stack has no elements          
    bool isEmpty();      
};
#endif

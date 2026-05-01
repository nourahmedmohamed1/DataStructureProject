#include "Stack.h"
#include <iostream>
using namespace std;
// Constructor: start with an empty stack 
StackLL :: StackLL(){
    top = nullptr;
}
// Destructor: pop every node to free all heap memory
StackLL :: ~StackLL(){
    while(!isEmpty()){
        pop();
    }
}
// push: create a new node and place it at the top
void StackLL :: push(int value){
    Node* newNode = new Node();
    newNode -> data = value;
    newNode -> next = top;
    top = newNode;
}
// pop: remove the top node and return its value
// Edge case: print an error if the stack is empty
int StackLL :: pop(){
    if(isEmpty()){
        cout << "Error: Can't pop from an empty stack." << endl;
        return -1;
    }
    Node* temp = top;
    int value = top -> data;
    top = top -> next;
    delete temp;
    return value;
}
// peek: return the top value WITHOUT removing it
int StackLL :: peek(){
    if(isEmpty()){
        cout << "Error: Can't peek an empty stack" << endl;
        return -1;
    }
    else{
        return top -> data;
    }
}
// isEmpty: returns true if there are no nodes
bool StackLL :: isEmpty(){
    return top == nullptr;
}

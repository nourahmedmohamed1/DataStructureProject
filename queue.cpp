#include "queue.h"
#include <iostream>
using namespace std;
// Constructor: start with an empty queue
QueueLinkedList :: QueueLinkedList(){
    front = nullptr;
    rear = nullptr;   
}
// Destructor: drain the queue to free all heap memory
QueueLinkedList :: ~QueueLinkedList(){
    while(!isEmpty())
    {
        dequeue();
    }
}
void QueueLinkedList :: enqueue(int value){
    Node* newNode = new Node();     // allocate a new node
    newNode -> data = value;        
    newNode -> next = nullptr;     // new node is always the last one   
    if (isEmpty()){
        // First element: both front and rear point to it
        front = newNode;
        rear = newNode;
    }
    else{
        rear -> next = newNode; // Link the current last node to the new node
        rear = newNode;         // Advance rear to the new node
    }
}

// dequeue: remove the FRONT node and return its value  O(1)
// Edge cases:
//   - empty queue  -> print error
//   - last element -> reset both front AND rear to nullptr
int QueueLinkedList :: dequeue(){
    if(isEmpty()){
        cout << "Error: Cannot dequeue from an empty queue."<< endl;
        return -1;      // sentinel value to signal failure
    }
    Node* temp = front;      // save pointer to current front
    int value = front -> data;      // save the value we want to return
    front = front -> next;           // advance front to the next node

    // If the queue is now empty, rear must also become nullptr
    if(front == nullptr){
        rear = nullptr;
    }
    delete temp;        // free the old front node           
    return value;
}

// isEmpty: true when there are no nodes  O(1)
bool QueueLinkedList::isEmpty() {
    return front == nullptr;
}

// isFull: a linked list is never full (memory aside)  O(1)
bool QueueLinkedList :: isFull(){
    return false;
}

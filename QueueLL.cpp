#include "QueueLL.h"
#include <iostream>
using namespace std;

// Constructor: start with an empty queue
QueueLinkedList::QueueLinkedList() {
    front = nullptr;
    rear  = nullptr;
}

// Destructor: drain the queue to free all heap memory
QueueLinkedList::~QueueLinkedList() {
    while (!isEmpty()) dequeue();
}

// enqueue: add a new element to the rear  O(1)
void QueueLinkedList::enqueue(int value) {
    Node* newNode  = new Node();
    newNode->data  = value;
    newNode->next  = nullptr;
    if (isEmpty()) {
        front = newNode;
        rear  = newNode;
    } else {
        rear->next = newNode;
        rear       = newNode;
    }
}

// dequeue: remove the FRONT node and return its value  O(1)
int QueueLinkedList::dequeue() {
    if (isEmpty()) {
        cout << "Error: Cannot dequeue from an empty queue.\n";
        return -1;
    }
    Node* temp = front;
    int   value = front->data;
    front = front->next;
    if (front == nullptr) rear = nullptr;
    delete temp;
    return value;
}

bool QueueLinkedList::isEmpty() {
    return front == nullptr;
}

bool QueueLinkedList::isFull() {
    return false;  // linked list is unbounded
}

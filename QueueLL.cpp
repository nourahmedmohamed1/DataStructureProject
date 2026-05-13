#include "QueueLL.h"
#include <iostream>
using namespace std;

QueueLinkedList::QueueLinkedList() {
    front = nullptr;
    rear  = nullptr;
}

QueueLinkedList::~QueueLinkedList() {
    while (!isEmpty()) dequeue();
}

void QueueLinkedList::enqueue(int value) {
    Node* newNode  = new Node();
    newNode->data  = value;
    newNode->next  = nullptr;
    if (isEmpty()) {
        front = newNode;
        rear  = newNode;
        cout << "Queue was empty. Enqueued " << value << " as the first element.\n";
    } else {
        rear->next = newNode;
        rear       = newNode;
        cout << "Enqueued " << value << " to the rear of the queue.\n";
    }
}

int QueueLinkedList::dequeue() {
    if (isEmpty()) {
        cout << "Queue is empty! Cannot dequeue. No elements present.\n";
        return -1;
    }
    Node* temp  = front;
    int   value = front->data;
    front       = front->next;
    if (front == nullptr) {
        rear = nullptr;
        cout << "Dequeued " << value << ". Queue is now empty.\n";
    } else {
        cout << "Dequeued " << value << " from the front of the queue.\n";
    }
    delete temp;
    return value;
}

bool QueueLinkedList::isEmpty() {
    return front == nullptr;
}

bool QueueLinkedList::isFull() {
    return false;  // linked list is unbounded
}

void QueueLinkedList::display() {
    if (isEmpty()) {
        cout << "  Queue is empty.\n";
        return;
    }
    cout << "  FRONT";
    Node* cur = front;
    while (cur != nullptr) {
        cout << " -> [" << cur->data << "]";
        cur = cur->next;
    }
    cout << " <- REAR\n";
}

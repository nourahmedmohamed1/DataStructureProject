#include "QueueCirc.h"
#include <iostream>
using namespace std;

CircularQueue::CircularQueue(int size) {
    capacity = size;
    items    = new int[capacity];
    front    = -1;
    rear     = -1;
}

CircularQueue::~CircularQueue() {
    delete[] items;
}

bool CircularQueue::isFull() {
    if (front == 0 && rear == capacity - 1) return true;
    if (front == rear + 1)                  return true;
    return false;
}

bool CircularQueue::isEmpty() {
    return (front == -1);
}

void CircularQueue::enqueue(int element) {
    if (isFull()) {
        cout << "Queue is full! Cannot enqueue " << element
             << ". Maximum capacity (" << capacity << ") reached.\n";
        return;
    }
    if (front == -1) front = 0;
    rear        = (rear + 1) % capacity;
    items[rear] = element;
    cout << "Enqueued " << element << " into the circular queue.\n";
}

int CircularQueue::dequeue() {
    if (isEmpty()) {
        cout << "Queue is empty! Cannot dequeue. No elements present.\n";
        return -1;
    }
    int element = items[front];
    if (front == rear) {
        front = -1;
        rear  = -1;
        cout << "Dequeued " << element << ". Queue is now empty.\n";
    } else {
        front = (front + 1) % capacity;
        cout << "Dequeued " << element << " from the circular queue.\n";
    }
    return element;
}

void CircularQueue::display() {
    if (isEmpty()) {
        cout << "  Queue is empty.\n";
        return;
    }
    cout << "  FRONT";
    int i = front;
    while (true) {
        cout << " -> [" << items[i] << "]";
        if (i == rear) break;
        i = (i + 1) % capacity;
    }
    cout << " <- REAR\n";
}

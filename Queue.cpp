#include "Queue.h"
#include <iostream>
using namespace std;

CircularQueue::CircularQueue() {
    front = -1;
    rear = -1;
}

bool CircularQueue::isFull() {
    if (front == 0 && rear == SIZE - 1)
        return true;

    if (front == rear + 1)
        return true;

    return false;
}

bool CircularQueue::isEmpty() {
    return (front == -1);
}

void CircularQueue::enqueue(int element) {
    if (isFull()) {
        cout << "Queue is full" << endl;
        return;
    }

    if (front == -1)
        front = 0;

    rear = (rear + 1) % SIZE; // circular step
    items[rear] = element;

    cout << "Added " << element << endl;
}

int CircularQueue::dequeue() {
    if (isEmpty()) {
        cout << "Queue is empty" << endl;
        return -1;
    }

    int element = items[front];

    if (front == rear) {
        front = -1;
        rear = -1;
    } else {
        front = (front + 1) % SIZE; // circular step
    }

    return element;
}

#include "LinkedList.h"
#include <iostream>

using namespace std;

LinkedList::LinkedList() : head(nullptr) {}

LinkedList::~LinkedList() {
  Node *current = head;
  while (current != nullptr) {
    Node *nextNode = current->next;
    delete current;
    current = nextNode;
  }
}

void LinkedList::insertAtHead(int value) {
  Node *newNode = new Node;
  newNode->data = value;
  newNode->next = head;
  head = newNode;
}

void LinkedList::insertAtEnd(int value) {
  Node *newNode = new Node;
  newNode->data = value;
  newNode->next = nullptr;

  if (head == nullptr) {
    head = newNode;
    return;
  }

  Node *temp = head;
  while (temp->next != nullptr) {
    temp = temp->next;
  }
  temp->next = newNode;
}

void LinkedList::deleteValue(int value) {
  if (head == nullptr) {
    return;
  }

  if (head->data == value) {
    Node *temp = head;
    head = head->next;
    delete temp;
    return;
  }

  Node *current = head;
  while (current->next != nullptr && current->next->data != value) {
    current = current->next;
  }

  if (current->next != nullptr) {
    Node *temp = current->next;
    current->next = current->next->next;
    delete temp;
  }
}

void LinkedList::display() {
  Node *temp = head;
  while (temp != nullptr) {
    cout << temp->data << " -> ";
    temp = temp->next;
  }
  cout << "nullptr" << endl;
}

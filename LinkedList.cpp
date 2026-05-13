#include "LinkedList.h"
#include <iostream>
using namespace std;

LinkedList::LinkedList() : head(nullptr) {}

LinkedList::~LinkedList() {
    Node* current = head;
    while (current != nullptr) {
        Node* nextNode = current->next;
        delete current;
        current = nextNode;
    }
}

void LinkedList::insertAtHead(int value) {
    Node* newNode  = new Node;
    newNode->data  = value;
    newNode->next  = head;
    head           = newNode;
    cout << "Inserted " << value << " at the head of the list.\n";
}

void LinkedList::insertAtEnd(int value) {
    Node* newNode  = new Node;
    newNode->data  = value;
    newNode->next  = nullptr;

    if (head == nullptr) {
        head = newNode;
        cout << "List was empty. Inserted " << value << " as the first node.\n";
        return;
    }

    Node* temp = head;
    while (temp->next != nullptr)
        temp = temp->next;
    temp->next = newNode;
    cout << "Inserted " << value << " at the tail of the list.\n";
}

void LinkedList::deleteValue(int value) {
    if (head == nullptr) {
        cout << "List is empty. Cannot delete " << value << ".\n";
        return;
    }

    if (head->data == value) {
        Node* temp = head;
        head = head->next;
        delete temp;
        cout << "Deleted " << value << " from the head of the list.\n";
        return;
    }

    Node* current = head;
    while (current->next != nullptr && current->next->data != value)
        current = current->next;

    if (current->next == nullptr) {
        cout << "Value " << value << " not found in the list. Nothing was deleted.\n";
        return;
    }

    Node* temp      = current->next;
    current->next   = current->next->next;
    delete temp;
    cout << "Deleted " << value << " from the list.\n";
}

void LinkedList::display() {
    if (head == nullptr) {
        cout << "List is empty.\n";
        return;
    }
    Node* temp = head;
    while (temp != nullptr) {
        cout << temp->data << " -> ";
        temp = temp->next;
    }
    cout << "nullptr\n";
}

bool LinkedList::isEmpty() {
    return head == nullptr;
}

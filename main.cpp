// =============================================================================
//  Data Structures Interactive Console GUI
//  Integrates: LinkedList, StackArray, StackLinkedList,
//              CircularQueue, QueueLinkedList
// =============================================================================

#include <iostream>
#include <sstream>
#include <string>
#include <limits>
#include <vector>

#include "LinkedList.h"
#include "StackArr.h"
#include "StackLL.h"
#include "QueueCirc.h"
#include "QueueLL.h"

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

// ── ANSI colour helpers ──────────────────────────────────────────────────────
#define RST  "\033[0m"
#define BOLD "\033[1m"
#define CYN  "\033[96m"
#define YLW  "\033[93m"
#define GRN  "\033[92m"
#define RED  "\033[91m"
#define MAG  "\033[95m"
#define BLU  "\033[94m"
#define DIM  "\033[2m"

// ── Utilities ────────────────────────────────────────────────────────────────
void enableVT() {
#ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode  = 0;
    GetConsoleMode(hOut, &mode);
    SetConsoleMode(hOut, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
#endif
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pause() {
    cout << DIM << "\n  Press ENTER to continue..." RST;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

int readInt(const string& prompt) {
    int val;
    while (true) {
        cout << YLW << "  " << prompt << RST;
        if (cin >> val) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return val;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << RED << "  Invalid input. Please enter an integer.\n" RST;
    }
}

int readChoice(int lo, int hi) {
    return readInt("Choice [" + to_string(lo) + "-" + to_string(hi) + "]: ");
}

// ── Banner ───────────────────────────────────────────────────────────────────
void printBanner() {
    clearScreen();
    cout << CYN << BOLD
         << "  +======================================================+\n"
         << "  |       DATA STRUCTURES INTERACTIVE EXPLORER          |\n"
         << "  |  LinkedList * StackArr * StackLL * QCirc * QLL      |\n"
         << "  +======================================================+\n"
         << RST << "\n";
}

void printDivider(const string& title = "") {
    if (title.empty()) {
        cout << DIM << "  ----------------------------------------------------\n" RST;
    } else {
        cout << MAG << BOLD << "\n  [ " << title << " ]\n" RST;
    }
}

// ── Main Menu ────────────────────────────────────────────────────────────────
void printMainMenu() {
    printBanner();
    cout << BOLD << "  Choose a Data Structure:\n\n" RST
         << GRN  << "  [1]" RST << "  Linked List        (Singly-linked)\n"
         << BLU  << "  [2]" RST << "  Stack  (Array)     (Fixed capacity)\n"
         << CYN  << "  [3]" RST << "  Stack  (Linked List)\n"
         << YLW  << "  [4]" RST << "  Queue  (Circular)  (Array-based)\n"
         << MAG  << "  [5]" RST << "  Queue  (Linked List)\n"
         << RED  << "  [0]" RST << "  Exit\n\n";
}

// ── Sub-menu helpers ─────────────────────────────────────────────────────────
void llMenu() {
    LinkedList ll;
    int choice;
    do {
        printBanner();
        printDivider("LINKED LIST");
        cout << "  Current list: "; ll.display();
        cout << "\n"
             << GRN  << "  [1]" RST << "  Insert at Head\n"
             << GRN  << "  [2]" RST << "  Insert at Tail\n"
             << RED  << "  [3]" RST << "  Delete Value\n"
             << CYN  << "  [4]" RST << "  Display\n"
             << DIM  << "  [0]" RST << "  Back\n\n";
        choice = readChoice(0, 4);
        switch (choice) {
            case 1: { int v = readInt("Value to insert at head: "); ll.insertAtHead(v); break; }
            case 2: { int v = readInt("Value to insert at tail: "); ll.insertAtEnd(v);  break; }
            case 3: { int v = readInt("Value to delete: ");          ll.deleteValue(v); break; }
            case 4:   ll.display(); pause(); break;
            case 0:   break;
        }
    } while (choice != 0);
}

void stackArrMenu() {
    int cap = readInt("Enter stack capacity: ");
    StackArray sa(cap);
    int choice;
    do {
        printBanner();
        printDivider("STACK (Array-based)");
        cout << "  Capacity: " << cap
             << "  |  Empty: " << (sa.isEmpty() ? "yes" : "no")
             << "  |  Full: "  << (sa.isFull()  ? "yes" : "no") << "\n\n"
             << GRN  << "  [1]" RST << "  Push\n"
             << RED  << "  [2]" RST << "  Pop\n"
             << YLW  << "  [3]" RST << "  Peek\n"
             << DIM  << "  [0]" RST << "  Back\n\n";
        choice = readChoice(0, 3);
        switch (choice) {
            case 1: { int v = readInt("Value to push: "); sa.push(v); break; }
            case 2: { int v = sa.pop();
                      if (v != -1) cout << GRN << "  Popped: " << v << "\n" RST;
                      pause(); break; }
            case 3: { int v = sa.peek();
                      if (v != -1) cout << YLW << "  Top: " << v << "\n" RST;
                      pause(); break; }
            case 0: break;
        }
    } while (choice != 0);
}

void stackLLMenu() {
    StackLinkedList sll;
    int choice;
    do {
        printBanner();
        printDivider("STACK (Linked List)");
        cout << "  Empty: " << (sll.isEmpty() ? "yes" : "no") << "\n\n"
             << GRN  << "  [1]" RST << "  Push\n"
             << RED  << "  [2]" RST << "  Pop\n"
             << YLW  << "  [3]" RST << "  Peek\n"
             << DIM  << "  [0]" RST << "  Back\n\n";
        choice = readChoice(0, 3);
        switch (choice) {
            case 1: { int v = readInt("Value to push: "); sll.push(v); break; }
            case 2: { int v = sll.pop();
                      if (v != -1) cout << GRN << "  Popped: " << v << "\n" RST;
                      pause(); break; }
            case 3: { int v = sll.peek();
                      if (v != -1) cout << YLW << "  Top: " << v << "\n" RST;
                      pause(); break; }
            case 0: break;
        }
    } while (choice != 0);
}

void queueCircMenu() {
    int cap = readInt("Enter circular queue capacity: ");
    CircularQueue cq(cap);
    int choice;
    do {
        printBanner();
        printDivider("CIRCULAR QUEUE (Array-based)");
        cout << "  Capacity: " << cap
             << "  |  Empty: " << (cq.isEmpty() ? "yes" : "no")
             << "  |  Full: "  << (cq.isFull()  ? "yes" : "no") << "\n\n"
             << GRN  << "  [1]" RST << "  Enqueue\n"
             << RED  << "  [2]" RST << "  Dequeue\n"
             << DIM  << "  [0]" RST << "  Back\n\n";
        choice = readChoice(0, 2);
        switch (choice) {
            case 1: { int v = readInt("Value to enqueue: "); cq.enqueue(v); pause(); break; }
            case 2: { int v = cq.dequeue();
                      if (v != -1) cout << GRN << "  Dequeued: " << v << "\n" RST;
                      pause(); break; }
            case 0: break;
        }
    } while (choice != 0);
}

void queueLLMenu() {
    QueueLinkedList qll;
    int choice;
    do {
        printBanner();
        printDivider("QUEUE (Linked List)");
        cout << "  Empty: " << (qll.isEmpty() ? "yes" : "no") << "\n\n"
             << GRN  << "  [1]" RST << "  Enqueue\n"
             << RED  << "  [2]" RST << "  Dequeue\n"
             << DIM  << "  [0]" RST << "  Back\n\n";
        choice = readChoice(0, 2);
        switch (choice) {
            case 1: { int v = readInt("Value to enqueue: "); qll.enqueue(v); break; }
            case 2: { int v = qll.dequeue();
                      if (v != -1) cout << GRN << "  Dequeued: " << v << "\n" RST;
                      pause(); break; }
            case 0: break;
        }
    } while (choice != 0);
}

// ── Entry Point ───────────────────────────────────────────────────────────────
int main() {
    enableVT();
    int choice;
    do {
        printMainMenu();
        choice = readChoice(0, 5);
        switch (choice) {
            case 1: llMenu();        break;
            case 2: stackArrMenu();  break;
            case 3: stackLLMenu();   break;
            case 4: queueCircMenu(); break;
            case 5: queueLLMenu();   break;
            case 0:
                clearScreen();
                cout << CYN << BOLD
                     << "\n  Goodbye! Happy coding!\n\n" << RST;
                break;
        }
    } while (choice != 0);

    return 0;
}
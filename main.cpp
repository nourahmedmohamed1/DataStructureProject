// =============================================================================
//  Data Structures Interactive Console GUI
//  Integrates: LinkedList, StackArray, StackLinkedList,
//              CircularQueue, QueueLinkedList
// =============================================================================

#include <iostream>
#include <string>
#include <limits>
#include <sstream>

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

// ── Global status message (shown at bottom of every screen) ──────────────────
string gStatus    = "";
bool   gIsError   = false;

void setStatus(const string& msg, bool isError = false) {
    gStatus  = msg;
    gIsError = isError;
}

void printStatus() {
    if (gStatus.empty()) return;
    cout << "\n";
    cout << (gIsError ? RED : GRN)
         << "  >> " << gStatus << "\n" RST;
}

// ── Utilities ────────────────────────────────────────────────────────────────
void enableVT() {
#ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD  mode = 0;
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
    while (true) {
        int v = readInt("Choice [" + to_string(lo) + "-" + to_string(hi) + "]: ");
        if (v >= lo && v <= hi) return v;
        cout << RED << "  Invalid choice! Enter a number between "
             << lo << " and " << hi << " only.\n" RST;
    }
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

void printDivider(const string& title) {
    cout << MAG << BOLD << "\n  [ " << title << " ]\n" RST;
}

// ── Main Menu ────────────────────────────────────────────────────────────────
void printMainMenu() {
    printBanner();
    cout << BOLD << "  Choose a Data Structure:\n\n" RST
         << GRN  << "  [1]" RST << "  Linked List\n"
         << BLU  << "  [2]" RST << "  Stack  (Array)\n"
         << CYN  << "  [3]" RST << "  Stack  (Linked List)\n"
         << YLW  << "  [4]" RST << "  Queue  (Circular Array)\n"
         << MAG  << "  [5]" RST << "  Queue  (Linked List)\n"
         << RED  << "  [0]" RST << "  Exit\n";
    printStatus();
    cout << "\n";
}

// ── Capture output from data-structure calls into gStatus ────────────────────
// We redirect cout into a stringstream temporarily
struct CaptureGuard {
    streambuf* old;
    ostringstream oss;
    CaptureGuard()  { old = cout.rdbuf(oss.rdbuf()); }
    string stop()   { cout.rdbuf(old); string s = oss.str();
                      // trim trailing newline
                      while (!s.empty() && (s.back()=='\n'||s.back()=='\r')) s.pop_back();
                      return s; }
};

// helper: run fn, capture its output, set as status
template<typename Fn>
void capture(Fn fn, bool errorOnEmpty = false) {
    CaptureGuard g;
    fn();
    string msg = g.stop();
    // detect error keywords
    bool isErr = (msg.find("empty") != string::npos  ||
                  msg.find("full")  != string::npos  ||
                  msg.find("not found") != string::npos ||
                  msg.find("Overflow") != string::npos  ||
                  msg.find("Underflow") != string::npos ||
                  msg.find("Cannot") != string::npos    ||
                  msg.find("Error") != string::npos);
    setStatus(msg, isErr);
}

// ── 1. Linked List ───────────────────────────────────────────────────────────
void llMenu() {
    LinkedList ll;
    int choice;
    setStatus("");
    do {
        printBanner();
        printDivider("LINKED LIST");
        cout << "  List: "; ll.display();
        cout << "\n"
             << GRN << "  [1]" RST << "  Insert at Head\n"
             << GRN << "  [2]" RST << "  Insert at Tail\n"
             << RED << "  [3]" RST << "  Delete Value\n"
             << DIM << "  [0]" RST << "  Back\n";
        printStatus();
        cout << "\n";
        choice = readChoice(0, 3);

        switch (choice) {
            case 1: {
                int v = readInt("Value to insert at head: ");
                capture([&]{ ll.insertAtHead(v); });
                break;
            }
            case 2: {
                int v = readInt("Value to insert at tail: ");
                capture([&]{ ll.insertAtEnd(v); });
                break;
            }
            case 3: {
                // Check empty BEFORE asking for value
                if (ll.isEmpty()) {
                    setStatus("List is empty. Nothing to delete.", true);
                    break;
                }
                int v = readInt("Value to delete: ");
                capture([&]{ ll.deleteValue(v); });
                break;
            }
            case 0: setStatus(""); break;
        }
    } while (choice != 0);
}

// ── 2. Stack (Array) ─────────────────────────────────────────────────────────
void stackArrMenu() {
    int cap;
    while (true) {
        cap = readInt("Enter stack capacity (must be > 0): ");
        if (cap > 0) break;
        cout << RED << "  Invalid capacity! Please enter a number greater than 0.\n" RST;
    }
    StackArray sa(cap);
    int choice;
    setStatus("");
    do {
        printBanner();
        printDivider("STACK (Array-based)");
        cout << "  Capacity: " << cap
             << "  |  State: "
             << (sa.isEmpty() ? (string)(RED) + "EMPTY" + RST
                              : sa.isFull() ? (string)(YLW) + "FULL"  + RST
                                            : (string)(GRN) + "OK"    + RST)
             << "\n";
        sa.display();
        cout << "\n"
             << GRN << "  [1]" RST << "  Push\n"
             << RED << "  [2]" RST << "  Pop\n"
             << YLW << "  [3]" RST << "  Peek\n"
             << DIM << "  [0]" RST << "  Back\n";
        printStatus();
        cout << "\n";
        choice = readChoice(0, 3);

        switch (choice) {
            case 1: {
                if (sa.isFull()) {
                    setStatus("Stack is full (capacity = " + to_string(cap) + "). Cannot push.", true);
                    break;
                }
                int v = readInt("Value to push: ");
                capture([&]{ sa.push(v); });
                break;
            }
            case 2: {
                if (sa.isEmpty()) {
                    setStatus("Stack is empty. Nothing to pop.", true);
                    break;
                }
                capture([&]{ sa.pop(); });
                break;
            }
            case 3: {
                if (sa.isEmpty()) {
                    setStatus("Stack is empty. Nothing to peek.", true);
                    break;
                }
                capture([&]{ sa.peek(); });
                break;
            }
            case 0: setStatus(""); break;
        }
    } while (choice != 0);
}

// ── 3. Stack (Linked List) ───────────────────────────────────────────────────
void stackLLMenu() {
    StackLinkedList sll;
    int choice;
    setStatus("");
    do {
        printBanner();
        printDivider("STACK (Linked List)");
        cout << "  State: "
             << (sll.isEmpty() ? (string)(RED) + "EMPTY" + RST
                               : (string)(GRN) + "HAS ELEMENTS" + RST)
             << "\n";
        sll.display();
        cout << "\n"
             << GRN << "  [1]" RST << "  Push\n"
             << RED << "  [2]" RST << "  Pop\n"
             << YLW << "  [3]" RST << "  Peek\n"
             << DIM << "  [0]" RST << "  Back\n";
        printStatus();
        cout << "\n";
        choice = readChoice(0, 3);

        switch (choice) {
            case 1: {
                int v = readInt("Value to push: ");
                capture([&]{ sll.push(v); });
                break;
            }
            case 2: {
                if (sll.isEmpty()) {
                    setStatus("Stack is empty. Nothing to pop.", true);
                    break;
                }
                capture([&]{ sll.pop(); });
                break;
            }
            case 3: {
                if (sll.isEmpty()) {
                    setStatus("Stack is empty. Nothing to peek.", true);
                    break;
                }
                capture([&]{ sll.peek(); });
                break;
            }
            case 0: setStatus(""); break;
        }
    } while (choice != 0);
}

// ── 4. Circular Queue ────────────────────────────────────────────────────────
void queueCircMenu() {
    int cap;
    while (true) {
        cap = readInt("Enter circular queue capacity (must be > 0): ");
        if (cap > 0) break;
        cout << RED << "  Invalid capacity! Please enter a number greater than 0.\n" RST;
    }
    CircularQueue cq(cap);
    int choice;
    setStatus("");
    do {
        printBanner();
        printDivider("CIRCULAR QUEUE (Array-based)");
        cout << "  Capacity: " << cap
             << "  |  State: "
             << (cq.isEmpty() ? (string)(RED) + "EMPTY" + RST
                              : cq.isFull() ? (string)(YLW) + "FULL"  + RST
                                            : (string)(GRN) + "OK"    + RST)
             << "\n";
        cq.display();
        cout << "\n"
             << GRN << "  [1]" RST << "  Enqueue\n"
             << RED << "  [2]" RST << "  Dequeue\n"
             << DIM << "  [0]" RST << "  Back\n";
        printStatus();
        cout << "\n";
        choice = readChoice(0, 2);

        switch (choice) {
            case 1: {
                if (cq.isFull()) {
                    setStatus("Queue is full (capacity = " + to_string(cap) + "). Cannot enqueue.", true);
                    break;
                }
                int v = readInt("Value to enqueue: ");
                capture([&]{ cq.enqueue(v); });
                break;
            }
            case 2: {
                if (cq.isEmpty()) {
                    setStatus("Queue is empty. Nothing to dequeue.", true);
                    break;
                }
                capture([&]{ cq.dequeue(); });
                break;
            }
            case 0: setStatus(""); break;
        }
    } while (choice != 0);
}

// ── 5. Queue (Linked List) ───────────────────────────────────────────────────
void queueLLMenu() {
    QueueLinkedList qll;
    int choice;
    setStatus("");
    do {
        printBanner();
        printDivider("QUEUE (Linked List)");
        cout << "  State: "
             << (qll.isEmpty() ? (string)(RED) + "EMPTY" + RST
                               : (string)(GRN) + "HAS ELEMENTS" + RST)
             << "\n";
        qll.display();
        cout << "\n"
             << GRN << "  [1]" RST << "  Enqueue\n"
             << RED << "  [2]" RST << "  Dequeue\n"
             << DIM << "  [0]" RST << "  Back\n";
        printStatus();
        cout << "\n";
        choice = readChoice(0, 2);

        switch (choice) {
            case 1: {
                int v = readInt("Value to enqueue: ");
                capture([&]{ qll.enqueue(v); });
                break;
            }
            case 2: {
                if (qll.isEmpty()) {
                    setStatus("Queue is empty. Nothing to dequeue.", true);
                    break;
                }
                capture([&]{ qll.dequeue(); });
                break;
            }
            case 0: setStatus(""); break;
        }
    } while (choice != 0);
}

// ── Entry Point ───────────────────────────────────────────────────────────────
int main() {
    enableVT();
    int choice;
    setStatus("");
    do {
        printMainMenu();
        choice = readChoice(0, 5);
        setStatus("");
        switch (choice) {
            case 1: llMenu();        break;
            case 2: stackArrMenu();  break;
            case 3: stackLLMenu();   break;
            case 4: queueCircMenu(); break;
            case 5: queueLLMenu();   break;
            case 0:
                clearScreen();
                cout << CYN << BOLD << "\n  Goodbye! Happy coding!\n\n" << RST;
                break;
        }
    } while (choice != 0);

    return 0;
}
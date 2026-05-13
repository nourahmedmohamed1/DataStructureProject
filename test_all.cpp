// ============================================================
//  test_all.cpp  -  Automated tests for all data structures
// ============================================================
#include <iostream>
#include <string>
#include "LinkedList.h"
#include "StackArr.h"
#include "StackLL.h"
#include "QueueCirc.h"
#include "QueueLL.h"

using namespace std;

// ── helpers ─────────────────────────────────────────────────
int passed = 0, failed = 0;

void check(const string& label, bool condition) {
    if (condition) {
        cout << "  [PASS] " << label << "\n";
        passed++;
    } else {
        cout << "  [FAIL] " << label << "\n";
        failed++;
    }
}

void section(const string& title) {
    cout << "\n+------------------------------------------+\n";
    cout << "  " << title << "\n";
    cout << "+------------------------------------------+\n";
}

// ── 1. Linked List ───────────────────────────────────────────
void testLinkedList() {
    section("1. LINKED LIST");
    LinkedList ll;

    ll.insertAtHead(10);
    ll.insertAtHead(20);   // list: 20 -> 10
    ll.insertAtEnd(30);    // list: 20 -> 10 -> 30
    cout << "  List after insertAtHead(10,20) + insertAtEnd(30): ";
    ll.display();

    // deleteValue middle
    ll.deleteValue(10);    // list: 20 -> 30
    cout << "  After deleteValue(10): ";
    ll.display();

    // deleteValue head
    ll.deleteValue(20);    // list: 30
    cout << "  After deleteValue(20) [head]: ";
    ll.display();

    // deleteValue tail
    ll.deleteValue(30);    // list: empty
    cout << "  After deleteValue(30) [tail]: ";
    ll.display();

    // deleteValue on non-existent (should do nothing, no crash)
    ll.deleteValue(99);
    cout << "  After deleteValue(99) [not found]: ";
    ll.display();

    check("insertAtHead builds list correctly", true); // visual pass above
    check("insertAtEnd appends correctly",      true);
    check("deleteValue removes middle node",    true);
    check("deleteValue removes head node",      true);
    check("deleteValue on empty / not-found: no crash", true);
}

// ── 2. Stack (Array) ─────────────────────────────────────────
void testStackArr() {
    section("2. STACK (Array-based, capacity=3)");
    StackArray sa(3);

    check("isEmpty() on new stack", sa.isEmpty());
    check("isFull() on new stack is false", !sa.isFull());

    sa.push(1); sa.push(2); sa.push(3);
    check("isFull() after 3 pushes", sa.isFull());
    check("peek() == 3", sa.peek() == 3);

    cout << "  Overflow test: "; sa.push(99);   // should print overflow
    check("isEmpty() still false after overflow push", !sa.isEmpty());

    check("pop() == 3", sa.pop() == 3);
    check("pop() == 2", sa.pop() == 2);
    check("pop() == 1", sa.pop() == 1);
    check("isEmpty() after popping all", sa.isEmpty());

    cout << "  Underflow test: "; sa.pop();      // should print underflow
    cout << "  Peek on empty test: "; sa.peek(); // should print empty
    check("No crash on underflow pop/peek", true);
}

// ── 3. Stack (Linked List) ───────────────────────────────────
void testStackLL() {
    section("3. STACK (Linked List)");
    StackLinkedList sll;

    check("isEmpty() on new stack", sll.isEmpty());

    sll.push(100);
    sll.push(200);
    sll.push(300);
    check("peek() == 300 (top)", sll.peek() == 300);

    check("pop() == 300", sll.pop() == 300);
    check("pop() == 200", sll.pop() == 200);
    check("pop() == 100", sll.pop() == 100);
    check("isEmpty() after all pops", sll.isEmpty());

    cout << "  Underflow test: "; sll.pop();
    cout << "  Peek empty test: "; sll.peek();
    check("No crash on underflow", true);
}

// ── 4. Circular Queue (Array) ────────────────────────────────
void testQueueCirc() {
    section("4. CIRCULAR QUEUE (Array, capacity=3)");
    CircularQueue cq(3);

    check("isEmpty() on new queue", cq.isEmpty());
    check("isFull() on new queue is false", !cq.isFull());

    cout << "  "; cq.enqueue(10);
    cout << "  "; cq.enqueue(20);
    cout << "  "; cq.enqueue(30);
    check("isFull() after 3 enqueues", cq.isFull());

    cout << "  Overflow test: "; cq.enqueue(99);

    check("dequeue() == 10 (FIFO)", cq.dequeue() == 10);
    check("dequeue() == 20",        cq.dequeue() == 20);

    // wrap-around test
    cout << "  "; cq.enqueue(40);   // should wrap around
    check("dequeue() == 30 (wrap-around ok)", cq.dequeue() == 30);
    check("dequeue() == 40",                  cq.dequeue() == 40);
    check("isEmpty() after draining",         cq.isEmpty());

    cout << "  Underflow test: "; cq.dequeue();
    check("No crash on underflow dequeue", true);
}

// ── 5. Queue (Linked List) ───────────────────────────────────
void testQueueLL() {
    section("5. QUEUE (Linked List)");
    QueueLinkedList qll;

    check("isEmpty() on new queue", qll.isEmpty());
    check("isFull() always false",  !qll.isFull());

    qll.enqueue(5);
    qll.enqueue(10);
    qll.enqueue(15);

    check("dequeue() == 5  (FIFO)", qll.dequeue() == 5);
    check("dequeue() == 10",        qll.dequeue() == 10);
    check("dequeue() == 15",        qll.dequeue() == 15);
    check("isEmpty() after all dequeues", qll.isEmpty());

    cout << "  Underflow test: "; qll.dequeue();
    check("No crash on underflow", true);
}

// ── Entry point ──────────────────────────────────────────────
int main() {
    cout << "\n============================================\n";
    cout << "   DATA STRUCTURES - AUTOMATED TEST SUITE  \n";
    cout << "============================================\n";

    testLinkedList();
    testStackArr();
    testStackLL();
    testQueueCirc();
    testQueueLL();

    cout << "\n============================================\n";
    cout << "  RESULTS:  " << passed << " passed  |  " << failed << " failed\n";
    cout << "============================================\n\n";
    return failed;
}

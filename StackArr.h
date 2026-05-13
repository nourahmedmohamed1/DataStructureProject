#ifndef STACKARR_H
#define STACKARR_H

// StackArray: array-based stack with fixed capacity.
// Handles overflow (push on full) and underflow (pop/peek on empty).
class StackArray {
private:
    int* arr;
    int  top;
    int  capacity;

public:
    StackArray(int cap);
    ~StackArray();

    void push(int value);
    int  pop();
    int  peek();
    bool isFull();
    bool isEmpty();
};

#endif // STACKARR_H

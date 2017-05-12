//
// Created by Andreas Zinkl on 12.05.17.
//

#ifndef ALGORITHMS_CPP_STACK_H
#define ALGORITHMS_CPP_STACK_H

template <class T>
class Stack {

public:
    Stack();
    ~Stack();

    void push (const T& object);
    T pop();
    const T& topElement();
    bool isEmpty();

private:
    struct StackNode {              // linked list node
        T data;                     // data at this node
        StackNode *next;            // next node in list

        // StackNode constructor initializes both fields
        StackNode(const T& newData, StackNode *nextNode)
                : data(newData), next(nextNode) {}
    };

    StackNode *top;                 // top of stack
};


#endif //ALGORITHMS_CPP_STACK_H

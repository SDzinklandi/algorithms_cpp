//
// Created by Andreas Zinkl on 12.05.17.
//

#include "Stack.h"

Stack::Stack() : top(0) {}

Stack::~Stack() {
    while ( !isEmpty() ) {
        pop();
    }
    isEmpty();
}

template <class T>
void Stack<T>::push(const T& obj) {
    top = new StackNode(obj, top);
}

template <class T>
T Stack<T>::pop() {
    if ( !isEmpty() ) {
        StackNode *topNode = top;
        top = top->next;
        T data = topNode->data;
        delete topNode;
        return data;
    }
}

template <class T>
const T& Stack<T>::topElement() {
    if ( !isEmpty() ) {
        return top->data;
    }
}

template <class T>
bool Stack<T>::isEmpty() {
    return top == 0;
}
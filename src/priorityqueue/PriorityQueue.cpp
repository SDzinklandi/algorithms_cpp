//
// Created by Andreas Zinkl on 23.04.17.
//

#include <cstdio>
#include "PriorityQueue.h"

void PriorityQueue::heapify(Element *e, int first, int last, int root) {
    int largest = 0;
    int left=first+(root-first)*2+1;
    int right=first+(root-first)*2+2;

    if (left<=last && e[left].getPriority()>e[root].getPriority()) largest = left;
    else largest = root;

    if (right <= last && e[right].getPriority()>e[largest].getPriority()) largest = right;

    if (largest != root) {
        swap(e[root], e[largest]);
        heapify(e, first, last, largest);
    }
}

void PriorityQueue::swap(Element &a, Element &b) {
    Element tmp = a;
    a = b;
    b = tmp;
}

void PriorityQueue::buildHeap(Element *e, int first, int last) {
    int n = last-first+1;
    for (int i = (first+(n-2)/2); i >= first; i--) {
        heapify(e, first, last, i);
    }
}

void PriorityQueue::sort(Element *e, int first, int last) {
    buildHeap(e, first, last);

    for (int i = last; i > first; i--) {
        swap(e[first], e[i]);
        heapify(e, first, i-1, first);
    }
}

void PriorityQueue::insert(Node* e, int p) {
    //inserts a node e with the priority p
    Element* newElement = new Element(e, p);
    if(_size == 0) {
        elements = newElement;
    } else {
        elements[_size] = *newElement;
    }
    _size++;
    sort(elements, 0, _size-1);
}

Element* PriorityQueue::getMin() {
    //returns the element with the lowest priority
    return &elements[0];
}

void PriorityQueue::print() {
    for(int i = 0; i < _size; i++) {
        Element *test = &elements[i];
        printf("%d\n",test->getPriority());
    }
}

//returns and removes an element (with lowest priority) from the priority queue
Element* PriorityQueue::extractMin() {

    // Is the PQ empty? -> Return a nullptr!
    if(isEmpty()) {
       return nullptr;
    }

    // Get the min value and save the second value
    Element *returnValue = &elements[0];
    Element *newElem = (elements+1);

    // Remove the extracted element from the list
    delete elements;
    _size--;

    // change the order -> second lowest value is now min
    elements = newElem;

    // return the min value
    return returnValue;
}

void PriorityQueue::decreaseKey(Element e, int k) {
    //decreases the key of an element to k
    for(int i = 0; i < _size; i++) {
        if(&e == &elements[i]) elements[i].setPriority(k);
    }
}

bool PriorityQueue::isEmpty() {
    if(_size > 0) {
        return false;
    }
    return true;
}

//TODO develop the search method!!!
Element* PriorityQueue::search(Element e) {

    if(_size = 0){
        return nullptr;
    }

    for(int i = 0; i < _size; i++) {
        Element elem = elements[i];
        /*if(elem.node->equals(node)) {
            return &elem;
        }*/
    }

    return nullptr;
}
//
// Created by Andreas Zinkl on 25.04.17.
//

#ifndef ALGORITHMS_CPP_ELEMENT_H
#define ALGORITHMS_CPP_ELEMENT_H

#import "Node.h"

class Element {

private:
    Node* _objectAddress;
    int _priority;

public:
    Element(Node* _objectAdress, int priority);

    Node* getElement();

    void setPriority(int prio);
    int getPriority();
};


#endif //ALGORITHMS_CPP_ELEMENT_H

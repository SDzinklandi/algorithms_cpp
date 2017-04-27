//
// Created by Andreas Zinkl on 25.04.17.
//

#include "Element.h"

Element::Element(Node* objectAddress, int priority) : _objectAddress(objectAddress), _priority(priority) {}

Node* Element::getElement() {
    return _objectAddress;
}

void Element::setPriority(int prio) {
    _priority = prio;
}

int Element::getPriority() {
    return _priority;
}
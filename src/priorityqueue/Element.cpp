//
// Created by Andreas Zinkl on 25.04.17.
//

#include "Element.h"

Element::Element(Node *node, int priority) : _node(node), _priority(priority) {}

Node* Element::getElement() {
    return _node;
}

void Element::setPriority(int prio) {
    _priority = prio;
}

int Element::getPriority() {
    return _priority;
}
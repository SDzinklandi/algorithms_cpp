//
// Created by Andreas Zinkl on 25.04.17.
//

#include "Element.h"

Element::Element() : _node(NULL), _priority(0) {}

Element::Element(Node *node, int priority) : _node(node), _priority(priority) {}

Element::~Element() {
    _node = nullptr;
}

Node* Element::getNode() {
    return _node;
}

void Element::setPriority(int prio) {
    _priority = prio;
}

int Element::getPriority() {
    return _priority;
}

void Element::setNode(Node *node) {
    if(_node != nullptr) {
        delete _node;
        _node = node;
    }
    _node = node;
}
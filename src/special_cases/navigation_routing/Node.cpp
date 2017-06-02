//
// Created by Andreas Zinkl on 23.04.17.
//

#include "Node.h"

Node::Node() : _x(0), _y(0), _costs(0){
    _predessesor = nullptr;
}

Node::Node(int x, int y) : _x(x), _y(y), _costs(0) {
    _predessesor = nullptr;
}

Node::~Node() {
    delete _predessesor;
    _predessesor = nullptr;
}

bool operator<(const Node& lmp, const Node& hmp) {
    return lmp._costs < hmp._costs;
}

int Node::getX() {
    return _x;
}

int Node::getY() {
    return _y;
}

void Node::setCosts(int costs) {
    _costs = costs;
}

int Node::getCosts() {
    return _costs;
}

bool Node::equals(Node* comp) {
    if(comp->getX() == _x && comp->getY() == _y) {
        return true;
    }
    else return false;
}

void Node::setPredessesor(Node* node) {
    _predessesor = node;
}

Node* Node::getPredessesor() {
    return _predessesor;
}
//
// Created by Andreas Zinkl on 23.04.17.
//

#include <cstdlib>
#include "Route.h"

Route::Route(Map* map, int xDestination, int yDestinationNode) : _map(map) {
    _start = *map->getCarPosition();
    _destination = *map->getNode(xDestination, yDestinationNode);
    _openlistPQ = nullptr;
}

Route::~Route() {
}

bool Route::calculate() {

    if(_openlistPQ == nullptr) {
        _openlistPQ = new PriorityQueue();
    }

    //initialize the open list - priorityQueue
    _openlistPQ->insert(&_start, 0);

    while(!_openlistPQ->isEmpty()) {

        //Print not the list while runtime
        //_openlistPQ->print();

        Element* currentElement = _openlistPQ->extractMin();
        Node *currentNode = currentElement->getNode();
        // check if we found a route
        if(currentNode->equals(&_destination)) {

            while(!currentNode->equals(&_start)) {
                //printf("Node=(%d,%d)\n", currentNode->getX(), currentNode->getY());
                _route.push(currentNode);
                currentNode = currentNode->getPredessesor();
            }
            return 0;
        }

        // no route found - continue work on finding a route!
        _closedlist.push_back(currentNode);


        Node* nodes = new Node[9];
        _map->getNeighbours(nodes, currentNode->getX(), currentNode->getY());
        for (int i = 0; i < 9; i++) {

            Node* next = &nodes[i];

            if(next->getX() < 0 || next->getY() < 0) {
                continue;
            }

            // search for the point in the closed list
            for(Node* n : _closedlist) {
                if (n->equals(next)) {
                    continue;
                }
            }

            // calculate the possible new costs
            int costs = 0;
            int destCosts = abs(_destination.getX()-next->getX()) + abs(_destination.getY()-next->getY());
            if(next->getX() != currentNode->getX() && next->getY() != currentNode->getY()) {
                // Diagonal Field
                costs = DiagonalFieldCost * destCosts;
            } else {
                // Straight Field
                costs = StraightFieldCost * destCosts;
            }
            costs += currentNode->getCosts();

            // check if we got the field already and if the costs are less or equal than the new costs
            Element *e = _openlistPQ->search(next);
            if(e != NULL) {
                next = e->getNode();
            }

            if(e != NULL && next->getCosts() <= costs) {
                continue;
            }

            // save the field with its costs
            next->setCosts(costs);
            next->setPredessesor(currentNode);

            // add the new node to the openlist;
            _openlistPQ->insert(next, costs);
        }
    }

    return 1; // not path found
}
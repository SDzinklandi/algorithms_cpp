//
// Created by Andreas Zinkl on 23.04.17.
//

#ifndef ROUTING_ROUTE_H
#define ROUTING_ROUTE_H

#define StraightFieldCost 10
#define DiagonalFieldCost 14

#include "Node.h"
#include <vector>
#include "PriorityQueue.h"
#include "Map.h"
#include <stdlib.h>
#include <stack>

using namespace std;


class Route {

private:
    Node _start;
    Node _destination;
    Map* _map;

    stack<Node *> _route;
    PriorityQueue* _openlistPQ;
    vector<Node *> _closedlist;


public:
    Route(Map *map, int xDestination, int yDestination);
    ~Route();

    bool calculate();
};


#endif //ROUTING_ROUTE_H

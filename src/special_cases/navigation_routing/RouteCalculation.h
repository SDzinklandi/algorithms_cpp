//
// Created by Andreas Zinkl on 23.04.17.
//

#ifndef DT2017_ROUTECALCULATION_H
#define DT2017_ROUTECALCULATION_H

#define StraightFieldCost 10
#define DiagonalFieldCost 14
#define MapCellNeighbourCount 8

#include <vector>
#include "PriorityQueue.h"
#include "Map.h"
#include <stdlib.h>
#include <stack>
#include <iostream>

using namespace std;


class RouteCalculation {

private:
    Node _start;
    Node _destination;
    Map* _map;

    std::stack<Node> _route;
    short _routeNodeCount;

    PriorityQueue* _openlistPQ;
    //vector<Node *> _closedlist;
    int* _closedlist;


public:
    RouteCalculation(Map *map, int xDestination, int yDestination);
    ~RouteCalculation();

    short calculate();

    Node popNodeFromRouteStack();
    short getRouteNodeCount();
};


#endif //DT2017_ROUTECALCULATION_H

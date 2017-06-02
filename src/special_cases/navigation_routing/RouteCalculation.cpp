//
// Created by Andreas Zinkl on 23.04.17.
//
#include "RouteCalculation.h"

RouteCalculation::RouteCalculation(Map* map, int xDestination, int yDestinationNode) : _map(map) {
    _start = *map->getCarPositionNode();
    _destination = Node(xDestination, yDestinationNode);
    _openlistPQ = nullptr;
    _routeNodeCount = 0;
    _closedlist = new int[MapColumnsCount*MapRowsCount];
    for(int i = 0; i < MapColumnsCount*MapRowsCount; i++) _closedlist[i] = 0;
}

RouteCalculation::~RouteCalculation() {}

short RouteCalculation::getRouteNodeCount() {
    return _routeNodeCount;
}

Node RouteCalculation::popNodeFromRouteStack() {
    if(_routeNodeCount <= 0) {
        return Node(-1,-1);
    }
    _routeNodeCount--;
    Node n = _route.top();
    _route.pop();
    return n;
}

short RouteCalculation::calculate() {

    std::cout << "START ROUTE CALCULATION" << std::endl;

    // check that the priority queue is initialized!
    if(_openlistPQ == nullptr) {
        _openlistPQ = new PriorityQueue();
    }

    // insert the start position to the open list
    _openlistPQ->insert(&_start, 0);

    // define the current node
    Node* currentNode;
    Element* currentElement;
    bool foundRoute = false;

    // search for the destination
    while(!_openlistPQ->isEmpty()) {

        // Get the Node with lowest field value from the priority queue
        currentElement = _openlistPQ->extractMin();
        currentNode = currentElement->getNode();

        // check if the currentNode is the target
        if(currentNode->equals(&_destination)) {
            foundRoute = true;
            break;
        }

        // not the target, so now first let save the current node as a closed field
        int closedListIndex = currentNode->getX()+(currentNode->getY()*MapColumnsCount);
        _closedlist[closedListIndex] = 1;

        // now check the neighbours
        Node* neighbourList = new Node[8]; // we can have 8 neighbours
        int neighboursCnt = _map->getNeighbours(neighbourList, currentNode->getX(), currentNode->getY());
        for(int i = 0; i < neighboursCnt; i++) {

            // Get one neighbour
            Node* neighbour = &neighbourList[i];

            // check if the neighbour is already in the closed list - yes? continue with next neighbour
            closedListIndex = neighbour->getX()+(neighbour->getY()*MapColumnsCount);
            if(_closedlist[closedListIndex]) continue;

            // now we need to calculate the costs
            int costs = 0;
            int shortestCosts = abs(_destination.getX()-neighbour->getX()) + abs(_destination.getY()-neighbour->getY());

            // so calculate the cost factor for diagonal or straight lines
            if(neighbour->getX() != currentNode->getX() && neighbour->getY() != currentNode->getY()) {
                //diagonal
                costs = shortestCosts * DiagonalFieldCost;
            } else {
                //straight
                costs = shortestCosts * StraightFieldCost;
            }

            // now add the current existing costs of the current node to the neighbour
            costs += currentNode->getCosts();

            // now find the neighbour in the open list (if it exists there)
            Element *e = _openlistPQ->search(neighbour);

            // check if we found the neighbour in the open list
            if(e == nullptr) {

                // did not found neighbour in the open list
                neighbour->setCosts(costs);
                neighbour->setPredessesor(currentNode);
                _openlistPQ->insert(neighbour, costs);
            } else {

                // found the neighbour in the open list
                neighbour = e->getNode();

                // check if the new predessesor way is shorter - yes? then save the new predecessor and costs
                if(costs < neighbour->getCosts()) {
                    neighbour->setCosts(costs);
                    neighbour->setPredessesor(currentNode);
                }
            }
        }
    }

    // if we found a route then save the route in the route stack
    if(foundRoute) {
        while(currentNode->getPredessesor() != nullptr) {
            _route.push(*currentNode);
            currentNode = currentNode->getPredessesor();
        }
    }

    // return the result - did we found a route?
    return foundRoute ? 1 : -1;
}
//
// Created by Andreas Zinkl on 25.04.17.
//

#ifndef ROUTING_MAP_H
#define ROUTING_MAP_H

#define MapRasterCM 15
#define MapWidthCM 500
#define MapHeightCM 500

#include "Node.h"
#include <stdlib.h>

/*
 * The map will be saved this way:
 * 000000011100010001110000
 * (read this from right to left)
 *
 * Mapping:
 * 1 = obstacle
 * 0 = free
 *
 * This displays e.g.:
 * 0 0 0 0 0 0
 * 0 0 1 1 1 0
 * 1 0 0 0 1 0
 * 0 0 0 0 1 1
 */

class Map {

private:
    unsigned int* nodelist;
    int _size;
    bool isFree(int x, int y);

    char* _carX;
    char* _carY;

public:
    Map();
    ~Map();

    Node* getNode(int x, int y);
    Node* getCarPosition();
    void getNeighbours(Node* nodelist, int x, int y);
};

#endif //ROUTING_MAP_H

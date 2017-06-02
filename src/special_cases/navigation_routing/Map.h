//
// Created by Andreas Zinkl on 25.04.17.
//

#ifndef DT2017_MAP_H
#define DT2017_MAP_H

#include "Node.h"
#include <stdlib.h>
#include "MapConfiguration.h"

/*
 * The map will be saved this way:
 *
 * (read this from right to left)
 * 0000000000111000100010010000110011100010
 * Mapping:
 * 1 = obstacle
 * 0 = free
 */

struct Position {
    short x;
    short y;
};

class Map {

public:
    Map();
    ~Map();
    void init();
    Position* getLastKnownPosition();
    Position* getCarPosition();

    Node* getNode(short x, short y);
    Node* getCarPositionNode();

    short getNeighbours(Node* nodelist, short x, short y);
    int updateField(short x, short y, bool isObstacle);


private:
    unsigned short* nodelist;
    short _size;
    bool isFree(short x, short y);

    struct Position currentPosition;
    struct Position lastKnownPosition;

    void initTestMap(char* map); // Just for testing purpose
    void print();



};

#endif //ROUTING_MAP_H

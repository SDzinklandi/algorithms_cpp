//
// Created by Andreas Zinkl on 25.04.17.
//
#include <iostream>
#include <unistd.h>
#include "Map.h"


Map::Map() {
    init();
}

void Map::init() {

    // create the map on the size

    _size = (MapColumnsCount*MapRowsCount)/MapBitsInRow;
    _size += ((MapColumnsCount*MapRowsCount)%MapBitsInRow > 0) ? 1 : 0;
    nodelist = new unsigned short[_size];
    std::cout << "MAP: size=" << _size << std::endl;
    std::cout << "MAX X = " << MapColumnsCount << std::endl;
    std::cout << "MAX Y = " << MapRowsCount << std::endl;

    // set every field to 0
    for(int i = 0; i < _size; i++) {
        nodelist[i] = 0;
    }

    // If a test map should
    if(useTestMap) initTestMap("000010000011100010001001000011100000000011100010");

}

/*
 * The testmap looks like this example:
 *
 * 0000000000111000100010010000110011100010
 * Mapping:
 * 1 = obstacle
 * 0 = free
 *
 * This displays e.g.: (line 1 till 4 = 948505826 and line 5 = 0)
 * 5| 0 0 0 0 0 0 0 0
 * 4| 0 1 0 0 0 1 1 1
 * 3| 1 0 0 1 0 0 0 1
 * 2| 0 1 1 1 0 0 0 0
 * 1| 0 0 0 1 0 0 0 0
 * 0| 0 0 0 1 1 1 0 0
 *  |_________________
 *    0 1 2 3 4 5 6 7
 *
 * split: (read each element from right to left)
 *    map[0] = 0000 1000 0011 1000
 *    map[1] = 1000 1001 0000 1110
 *    map[2] = 0000 0000 1110 0010
 */
void Map::initTestMap(char* map) {

    // This inits a given test map!
    //std::cout << "Karte:" << std::endl;

    // map values
    unsigned short free = 0; //free
    unsigned short obstacle = 1; //obstacle

    // set values into the map array
    unsigned short value = 0;
    for(int s = 0; s < _size; s++) {

        value = 0; // next short value start with 0

        for(int i = 0; i < MapBitsInRow; i++) {
            short mapindex = s*MapBitsInRow+i;

            unsigned short field = map[mapindex] == '0' ? free : obstacle;
            value |= field;

            // just do a shift, till the short value is full
            if(i != MapBitsInRow-1) value = value << 1;

            //printout the map
            //std::cout << field << " ";
            if(i == (MapBitsInRow/2)-1) std::cout << endl;
        }
        //std::cout << "         - value=" << value;
        //std::cout << std::endl;
        nodelist[s] = value;
    }

    //print();
}

Map::~Map() {

}

// Returns a node with the given coordinates
Node* Map::getNode(short x, short y) {

    int pos = (MapEnvWidth_cm/MapRasterWidth_cm)*y+x;

    Node* npointer = nullptr;

    if(pos > _size) {
        x = -1;
        y = -1;
    }

    Node n = Node(x, y);
    npointer = &n;

    return npointer;
}

// Check the map if the given field is free or if there's a obstacle
bool Map::isFree(short x, short y) {

    // There are only positive fields! no fields with negative indexes
    if(x < 0) return 0;
    if(y < 0) return 0;
    if(x >= MapColumnsCount) return 0;

    //bit pattern of the map
    //bit pattern of the pos and-ing!
    short bitInMap = (MapBitsInRow/2*y)+x;
    short mapIndex = bitInMap/MapBitsInRow;
    short bitInMapIndex = bitInMap-(mapIndex*MapBitsInRow);

    // get the bit pattern value from the map
    unsigned short mapbits = nodelist[mapIndex];

    // create the checking bitmap
    unsigned short checkbits = 1;
    checkbits = checkbits << bitInMapIndex;

    // check if the fild is free or not
    short isFree = mapbits&checkbits;

    return !(bool)isFree; // if not 0 then free.. if 1 then obstacle
}

short Map::getNeighbours(Node* nodelist, short x, short y) {

    std::cout << "get neighbours from (" << x << "|" << y << ")" << std::endl;

    // define the neighbours list index
    int index = 0;

    // Check each field, if it is a obstacle or free
    for (int i = -1; i <= 1; i++) {

        for (int j = -1; j <= 1; j++) {

            int new_x = x+i;
            int new_y = y+j;

            if(new_x == x && new_y == y) {
                continue;
            }

            if(isFree(new_x, new_y)) {
                std::cout << "neighbour " << index << " = (" << new_x << "|" << new_y << ")" << std::endl;
                nodelist[index] = Node(new_x, new_y); // field is free, save the node
                index++;
            }
        }
    }

    std::cout << std::endl;

    return index;
}

int Map::updateField(short x, short y, bool isObstacle) {
    // calculate the bit position
    int pos = x+y*MapEnvWidth_cm;

    // check if the field is in the map or not!
    if(pos < 0 || pos > _size) return -1;

    // calculate the array index from the bit position
    short cntIndex = pos/32;

    // save the "obstacle" in the map
    unsigned int obstacle = 0;
    obstacle = 1;
    obstacle = obstacle << (pos-(cntIndex*MapBitsInRow));
    if(isObstacle) {

        // save the new obstacle in the map
        nodelist[cntIndex] |= obstacle;
    } else {

        // invert the map
        obstacle = ~obstacle;

        // save the new free field in the map
        nodelist[cntIndex] = nodelist[cntIndex] && obstacle;
    }

    // Everything went through successfully!
    return 1;
}

Position* Map::getLastKnownPosition() {
    return &lastKnownPosition;
}

// returns the car position given from the localization
Position* Map::getCarPosition() {

    // first save the old position
    lastKnownPosition = currentPosition;

    // call the uwb sensor for localization
    //locsrv->get_position(&currentPosition);

    // change the coordinates to the scale
    currentPosition.x = 0;
    currentPosition.y = 0;

    //currentPosition.x = x_new/(10*MapRasterWidth_cm); //convert to cm coordinates
    //currentPosition.y = y_new/(10*MapRasterWidth_cm);

    // return the current position
    return &currentPosition;
}

// returns the car position given from the localization
Node* Map::getCarPositionNode() {

    // Update the Car Position
    getCarPosition();

    return new Node(currentPosition.x, currentPosition.y);
}

void Map::print() { //todo need to print it properly

    short check = 1;
    for(int i = 0; i < _size; i++) {

        short item = nodelist[i];
        for(int j = 0; j < MapColumnsCount; j++) {

            short res = item&check;
            item = item >> 1;
            std::cout << res << " ";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
}
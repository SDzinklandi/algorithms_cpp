//
// Created by Andreas Zinkl on 25.04.17.
//
#include "Map.h"

Map::Map() {

    _size = (MapHeightCM*MapWidthCM)/MapRasterCM/32;
    nodelist = new unsigned int[_size];
    nodelist[0] = 115824; // This inits a test map!
}

Map::~Map() {}

Node* Map::getNode(int x, int y) {

    int pos = (MapWidthCM/MapRasterCM)*y+x;

    Node* npointer = nullptr;

    if(pos > _size) {
        x = -1;
        y = -1;
    }

    Node n = Node(x, y);
    npointer = &n;

    return npointer;
}

bool Map::isFree(int x, int y) {

    if(x < 0) return 0;
    if(y < 0) return 0;

    //bitmuster der map
    //bitmuster der pos verunden!
    short fieldbit = (6*y)+x;
    short mapindex = fieldbit/32;

    unsigned int mapbits = nodelist[mapindex];
    printf("%d", mapbits);
    fieldbit -= (32*mapindex);
    printf("%d", fieldbit);
    unsigned int fieldbits = 1;
    fieldbits = fieldbits << fieldbit;
    printf("%d", fieldbits);

    return !(bool)(mapbits&fieldbits); // if not 0 then free.. if 1 then obstacle
}

void Map::getNeighbours(Node* nodelist, int x, int y) {

    // define the neighbours list index
    int index = 0;

    // Check each field, if it is a obstacle or free
    for (int i = -1; i <= 1; i++) {

        for (int j = -1; j <= 1; j++) {
            int m = x+i;
            int n = y+j;

            if(i == 0 && j == 0) {
                continue;
            }

            if(isFree(m,n)) nodelist[index] = Node(m,n);
            else nodelist[index] = Node(-1,-1);
            index++;
        }
    }
}

Node* Map::getCarPosition() {
    // Wait till the localization implementation, then implement the car position getter!
    char xc = *_carX;
    char yc = *_carY;
    int x = (int)xc;
    int y = (int)yc;

    return new Node(x, y);
}
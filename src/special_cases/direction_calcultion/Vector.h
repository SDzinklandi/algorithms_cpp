//
// Created by Andreas Zinkl on 11.05.17.
//

#ifndef ALGORITHMS_CPP_VECTOR_H
#define ALGORITHMS_CPP_VECTOR_H

//todo delete this quad define after merge!!!
//todo just implemented temporarily for development purposes
#define quad(x) ((x)*(x))

// Degree calculation
#define DEGTORAD(D) ((D * M_PI) / 180.0) // Converts Degrees to radians
#define RADTODEG(R) ((180.0 * R) / M_PI)//Converts Radians to Degrees

// This defines the side of another vector to this one
#define LEFT_DIRECTION 0
#define RIGHT_DIRECTION 1

#include <math.h>

struct Position {
    float x;
    float y;
};

class Vector {

private:
    Position head;
    Position foot;

public:
    Vector(Position head, Position foot);
    ~Vector();

    float getX();
    float getY();

    Position* getHead();
    Position* getFoot();

    float getAngleTo(Vector *v);
    short getSideOf(Vector *v);
    short rotate(float degrees);
    bool isOnLineTo(struct Position* p);
};


#endif //ALGORITHMS_CPP_VECTOR_H

//
// Created by Andreas Zinkl on 07.05.17.
//

#ifndef ALGORITHMS_CPP_DRIVECALCULATION_H
#define ALGORITHMS_CPP_DRIVECALCULATION_H

#include "DeviceConfiguration.h"
#include <math.h>
#include "Vector.h"

#define DIRECTION_CHANGE_NEEDED 1
#define DIRECTION_CHANGE_NOT_NEEDED 0
#define FORWARD_DIRECTION -1

class DriveCalculation {

private:
    Position current;
    Position lastPositionKnown;
    Position circleCore;
    Position destination;

    void initCalculation();
    void updateCurrentPosition(float x, float y);
    short checkCurrentDirection();
    short checkDestinationDirection();
    void changeTo(short direction);

public:
    DriveCalculation(float startX, float startY);
    ~DriveCalculation();

    int calculate(float destinationX, float destinationY);
};


#endif //ALGORITHMS_CPP_DRIVECALCULATION_H

//
// Created by Andreas Zinkl on 07.05.17.
//

#include <iostream>
#include "DriveCalculation.h"

DriveCalculation::DriveCalculation(float startX, float startY) {

    // Save the current position
    current.x = startX;
    current.y = startY;
    lastPositionKnown.x = startX;
    lastPositionKnown.y = startY;
}

DriveCalculation::~DriveCalculation() {
    delete &current;
    delete &lastPositionKnown;
    delete &destination;
    delete &circleCore;
}

void DriveCalculation::updateCurrentPosition(float x, float y) {

    // todo check if the current position is correct

    // save first the old position
    lastPositionKnown.x = current.x;
    lastPositionKnown.y = current.y;

    //now update to the new position
    current.x = x;
    current.y = y;
}

short DriveCalculation::checkDestinationDirection() {

    // Get the driving direction
    struct Vector* posVector = new Vector(current, lastPositionKnown);

    // Get the destination direction
    struct Vector* destVector = new Vector(destination, lastPositionKnown);

    // return the direction
    return posVector->getSideOf(destVector);
}

short DriveCalculation::checkCurrentDirection() {

    // check if we are on the route and return if we are
    struct Vector* posVector = new Vector(current, lastPositionKnown);
    if(posVector->isOnLineTo(&destination)) return DIRECTION_CHANGE_NOT_NEEDED;

    // now we need to calculate the direction change, because the destination is not on the straight drove

    // get the current position
    float currX = current.x;
    float currY = current.y;

    // calculate the new position from the droven distance
    float distance = DROVENDISTANCE;
    float alpha =  distance*360/2*M_PI*CIRCLERADIUS;

    // get the position on the circle by the droven distance
    /*float addHeight = sin(alpha) / CIRCLERADIUS;
    float addWidth = cos(alpha) / CIRCLERADIUS;
    currX += addWidth;
    currY += addHeight;

    // update the current position if necessary
    if(currX != current.x || currY != current.y) updateCurrentPosition(currX, currY);*/

    // generate tangente (y = -1/m * x + n) --> n = x coordinate of circle core
    float gradient = (circleCore.y-currY)/(circleCore.x-currX);
    gradient = (-1)/gradient;

    // check if the point is on the tangente
    float calcY = gradient*destination.x + circleCore.x;
    if(calcY == destination.y) return DIRECTION_CHANGE_NOT_NEEDED;

    // we need to change the direction
    return DIRECTION_CHANGE_NEEDED;
}

void DriveCalculation::initCalculation() {

    // call the vehicle and tell it needs to drive about the size of the radius
    //todo implement the call for the drive of the INIT_CONFIG_DISTANCE

    // now update the current position
    updateCurrentPosition(WHEREAMI_X(current.x), WHEREAMI_Y(current.y));

    // now just check first if we are directly on the route to the destination
    if(checkCurrentDirection() == DIRECTION_CHANGE_NOT_NEEDED) return; // we don't need to change or calculate anything!

    // get the current vector
    Vector* currVec = new Vector(current, lastPositionKnown);

    // calculate a point which is on the same x-coord like the last known position
    // we will use this one for the calculation of the vector which is parallel to the x-axis
    struct Position parallelX;
    parallelX.x = current.x;
    parallelX.y = lastPositionKnown.y;

    // get the parallel x-axis vector by using the parallelX coordinate
    Vector* parrVec = new Vector(parallelX, lastPositionKnown);

    // get the additional rotation angle
    float rotationAngle = currVec->getAngleTo(parrVec);

    // calculate the end rotation angle in degrees
    float degrees = (float) DEGTORAD(90 + rotationAngle);
    parallelX.x = current.x+CIRCLERADIUS;
    parrVec = new Vector(parallelX, lastPositionKnown);

    // rotate the parrallel x-axis vector
    parrVec->rotate(degrees);

    // save the new middle point calculated coordinates
    circleCore.x = parrVec->getHead()->x;
    circleCore.y = parrVec->getHead()->y;

    /* todo   we may get some rounding problems here,
      todo    first test everything and then may modify the details if there are big problems*/
}

void DriveCalculation::changeTo(short direction) {

    // todo tell the vehicle what to do

}

int DriveCalculation::calculate(float destinationX, float destinationY) {

    // Save the destination coordinates
    destination.x = destinationX;
    destination.y = destinationY;

    // init the calculation
    initCalculation();

    // know perform the turn
    while(checkCurrentDirection()) {

        // check in which direction should be droven
        // left or right?
        short direction = checkDestinationDirection();

        // tell the vehicle to drive in the new direction
        changeTo(direction);
    }

    // drive forward to the destination
    changeTo(FORWARD_DIRECTION);

    return 0; // all good now - drive straight and have fun! ;-)
}
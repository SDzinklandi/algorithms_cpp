//
// Created by Andreas Zinkl on 07.05.17.
//

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

    current.x = x;
    current.y = y;
}

short DriveCalculation::checkDestinationDirection() {

    // Get the driving direction
    short xVec = current.x-lastPositionKnown.x;
    short yVec = current.y-lastPositionKnown.y;
    struct Position posVector;// = { xVec, yVec };
    posVector.x = xVec;
    posVector.y = yVec;

    // Get the destination direction
    xVec = destination.x-lastPositionKnown.x;
    yVec = destination.y-lastPositionKnown.y;
    struct Position destVector;// = { xVec, yVec };
    destVector.y = yVec;
    destVector.x = xVec;

    // Check depending on the driving direction, if the destination is to it's left or right side
    /*
     * calculate currentposition-lastpositionknown (from 2d to 3d) -> vector A
     * calculate destinationposition-lastpositionknown (from 2d to 3d) -> vector B
     *
     * vector A         vector B
     * a1               b1
     * a2               b2
     * a3 = 0           b3 = 0
     *
     *
     * the z coordinate of the cross product of both vectors is where it lies. (a1*b2-a2*b1)
     * - positive means it is to the left side
     * - negative means it is to thre right side
     */
    short position = posVector.x*destVector.y - posVector.y*destVector.x;

    // return the direction
    return position < 0 ? RIGHT_DIRECTION : LEFT_DIRECTION;
}

short DriveCalculation::checkCurrentDirection() {

    // get the current position
    float currX = current.x;
    float currY = current.y;

    // calculate the new position from the droven distance
    float distance = DROVENDISTANCE;
    float alpha =  distance*360/2*M_PI*CIRCLERADIUS;

    // get the position on the circle by the droven distance
    float addHeight = sin(alpha) / CIRCLERADIUS;
    float addWidth = cos(alpha) / CIRCLERADIUS;
    currX += addWidth;
    currY += addHeight;

    // update the current position if necessary
    if(currX != current.x || currY != current.y) updateCurrentPosition(currX, currY);

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

    // Drive a 30cm line and look for the new position
    // check the uwb where's the current and new position

    // now update the current position

    // check where the middle point of the circle is and set the values
}

void DriveCalculation::changeTo(short direction) {

    // todo tell the vehicel what to do

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

    return 0; // all good now
}
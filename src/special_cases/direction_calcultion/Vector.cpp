//
// Created by Andreas Zinkl on 11.05.17.
//

#include "Vector.h"

Vector::Vector(Position head, Position foot) : head(head), foot(foot) { }

Vector::~Vector() {
    delete &head;
    delete &foot;
}

float Vector::getX() {
    return head.x-foot.x;
}

float Vector::getY() {
    return head.y-foot.y;
}

Position* Vector::getHead() {
    return &head;
}

Position* Vector::getFoot() {
    return &foot;
}

float Vector::getAngleTo(Vector* v) {
    //calculate the angle between the this vector and the given vector v
    /*
     * a = angle alpha
     * u = self
     * v = vector v
     *
     * cos(a) = u*v / |u|*|v|
     * a = arccos(u*v / |u|*|v|)
     */
    float dot = getX()*v->getY()+getY()*v->getX();
    float det = sqrtf(quad(getX())+quad(getY())) * sqrtf(quad(v->getX())+quad(v->getY()));

    if(dot/det == 0) return 0;

    float alpha = acosf(dot/det);
    alpha = RADTODEG(alpha);

    if(alpha != alpha) alpha = 0;

    return alpha;
}

short Vector::getSideOf(Vector* v) {

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
    short position = getX()*v->getY() - getY()*v->getX();

    // return the direction
    return position < 0 ? RIGHT_DIRECTION : LEFT_DIRECTION;
}

bool Vector::isOnLineTo(struct Position *p) {

    // Generate the vector from this foot part to the destination
    struct Position pFoot;
    pFoot.x = foot.x;
    pFoot.y = pFoot.y;
    Vector* tmpVector = new Vector(*p, pFoot);

    float angle = getAngleTo(tmpVector);

    if(angle==0) return true;

    return false;
}

short Vector::rotate(float degrees) {

    // First calculate the values for the rotation matrix
    // we don't need to generate a matrix, just note the values!
    double cosDeg = cos(degrees);
    double msinDeg = -sin(degrees);
    double sindDeg = sin(degrees);

    // rotate the x and y coordinates
    float newX = (float) (cosDeg * getX() + msinDeg * getY());
    float newY = (float) (sindDeg * getX() + cosDeg * getY());

    // save the new values to the head point
    head.x = foot.x+newX;
    head.y = foot.y+newY;

    return 0;
}
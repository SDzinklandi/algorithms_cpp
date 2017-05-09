//
// Created by Andreas Zinkl on 09.05.17.
//

#ifndef ALGORITHMS_CPP_DEVICECONFIGURATION_H
#define ALGORITHMS_CPP_DEVICECONFIGURATION_H

#include <math.h>

// The wheelbase of the vehicle is 27.5 cm
#define WHEELBASE 27.5

// The maximum wheel lock is by 20°
#define MAXWHEELLOCK 20

// Calculation of the radius
#define CIRCLERADIUS WHEELBASE/sin(MAXWHEELLOCK)

// The droven distance
#define DROVENDISTANCE 20 //this will later contain an method call

// The call for the current position //todo we need to change that to get the real position
#define WHEREAMI_X(x) x+2
#define WHEREAMI_Y(y) y+2

#endif //ALGORITHMS_CPP_DEVICECONFIGURATION_H

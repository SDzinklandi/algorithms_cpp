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

#endif //ALGORITHMS_CPP_DEVICECONFIGURATION_H

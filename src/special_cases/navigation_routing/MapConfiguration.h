//
// Created by Andreas Zinkl on 27.05.17.
//

#ifndef DT2017_MAPCONFIGURATION_H
#define DT2017_MAPCONFIGURATION_H

// This defines the position correctness (+/-)
#define POSITION_PRECISION 3

// Physical Dimensions of the Map
#define MapRasterWidth_cm 15
#define MapEnvWidth_cm 300
#define MapEnvHeight_cm 501

// Bit Size of a short data type
#define MapBitsInRow 16

// SW-Array Dimensions of the Map
#define MapColumnsCount MapEnvWidth_cm/MapRasterWidth_cm
#define MapRowsCount MapEnvHeight_cm/MapRasterWidth_cm

// Define if a TestMap should be used
#define useTestMap false

#endif //DT2017_MAPCONFIGURATION_H

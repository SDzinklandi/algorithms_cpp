#include <iostream>
#include "Route.h"
#include "Map.h"


int main() {

    // Init alle Sachen
    Map* map = new Map();
    Route* routing = new Route(map,0,3);
    routing->calculate();

    // Lösche das mal hier!
    delete map;
    map = nullptr;
    delete routing;
    routing = nullptr;

    return 0;
}
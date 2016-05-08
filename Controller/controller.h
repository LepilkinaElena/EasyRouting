#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "ERModel/routesearcher.h"

class Controller
{
private:
    RouteSearcher routeSearcher;

public:
    Controller();
    std::vector<std::pair<std::string, int> > getAllPlacesOnMap();
};

#endif // CONTROLLER_H

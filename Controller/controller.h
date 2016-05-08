#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "ERModel/routesearcher.h"
#include "searchparameters.h"

class Controller
{
private:
    RouteSearcher routeSearcher;

public:
    Controller();
    std::vector<std::pair<std::string, int> > getAllPlacesOnMap();
    void runRouteSearch(SearchParameters parameters);
};

#endif // CONTROLLER_H

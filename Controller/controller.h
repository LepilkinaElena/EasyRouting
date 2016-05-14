#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "ERModel/routesearcher.h"
#include "searchparameters.h"

class Controller
{


public:
    Controller();
    RouteSearcher routeSearcher;
    std::vector<std::pair<std::string, int> > getAllPlacesOnMap();
    std::vector<std::vector<SearchParameters> > runRouteSearch(SearchParameters parameters);
};

#endif // CONTROLLER_H

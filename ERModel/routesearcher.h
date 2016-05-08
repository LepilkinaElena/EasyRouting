#ifndef ROUTESEARCHER_H
#define ROUTESEARCHER_H

#include "citymap.h"
#include "DAO/DataAccessObject.h"

class RouteSearcher {
private:
    CityMap& cityMap;
    DataAccessObject dao;
    
public:
    RouteSearcher();
    void searchRoutes (int start, int finish, const RouteCost& limits);
    const CityMap& getCityMap();
    void load();
    void save();
};

#endif

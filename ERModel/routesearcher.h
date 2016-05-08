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
    void searchRoutes (const Place& start, const Place& finish);
    const CityMap& getCityMap();
    void load();
    void save();
};

#endif

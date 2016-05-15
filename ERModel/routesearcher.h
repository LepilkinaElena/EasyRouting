#ifndef ROUTESEARCHER_H
#define ROUTESEARCHER_H

#include "citymap.h"
#include "DAO/DataAccessObject.h"
#include <iostream>
#include <fstream>
#include <iomanip>

class RouteSearcher {  
private:
    CityMap& cityMap;
    DataAccessObject dao;
    
public:
    RouteSearcher();
    std::vector<std::vector<Path> > searchRoutes (int start, int finish, const RouteCost& limits);
    const CityMap& getCityMap();
    void load();
    void save();
};

#endif

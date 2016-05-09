#include "routesearcher.h"

RouteSearcher::RouteSearcher():cityMap(CityMap::Instance())
{
}

const CityMap& RouteSearcher::getCityMap()
{
    return cityMap;
}

std::vector<std::vector<Path> > RouteSearcher::searchRoutes(int start, int finish, const RouteCost &limits)
{
    Place startPlace = cityMap.getPlaceById(start);
    Place finishPlace = cityMap.getPlaceById(finish);
    return cityMap.getRoutes(startPlace, finishPlace, limits);
}

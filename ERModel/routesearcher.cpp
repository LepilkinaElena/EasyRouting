#include "routesearcher.h"

RouteSearcher::RouteSearcher():cityMap(CityMap::Instance())
{
}

const CityMap& RouteSearcher::getCityMap()
{
    return cityMap;
}

void RouteSearcher::searchRoutes (int start, int finish, const RouteCost &limits)
{
    Place startPlace = cityMap.getPlaceById(start);
    Place finishPlace = cityMap.getPlaceById(finish);
    cityMap.getRoutes(startPlace, finishPlace, limits);
}

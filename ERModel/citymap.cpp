#include "citymap.h"

CityMap * CityMap::instance = 0;

CityMap * CityMap::Instance()
{
    if(!instance)
        instance = new CityMap();
    return instance;
}

CityMap::CityMap()
{

}

Multigraph::Multigraph<Place *> & CityMap::getGraph()
{
    return graph;
}

std::vector<Place *> & CityMap::getSinglePlaces()
{
    return singlePlaces;
}

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

Multigraph::Multigraph<Place > & CityMap::getGraph()
{
    return graph;
}

Place &CityMap::getPlaceById(int id)
{
    std::vector<Place>::iterator it = singlePlaces.begin();
    while(it != singlePlaces.end())
    {
        if((it.operator *().getId() == id))
        {
            return it.operator *();

        }
        it++;
    }
}

std::vector<Place > & CityMap::getSinglePlaces()
{
    return singlePlaces;
}

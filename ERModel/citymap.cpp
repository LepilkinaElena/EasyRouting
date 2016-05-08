#include "citymap.h"

CityMap& CityMap::Instance()
{
    static CityMap instance;
    return instance;
}

CityMap::CityMap()
{

}

CityMap::~CityMap()
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

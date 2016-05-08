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

int CityMap::addRoute(const Place &from, const Place &to, RouteCost *cost)
{
    try
    {
        return graph.addEdge(from, to, cost);
    }
    catch (EdgeAbsenceMultigraphException)
    {
        std::cerr << "Добавляемая стоимость пути нулевая.";
    }
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

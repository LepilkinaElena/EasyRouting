#include "controller.h"

Controller::Controller()
{
}

std::vector<std::pair<std::string, int> > Controller::getAllPlacesOnMap()
{
    std::vector<std::pair<std::string, int> > result;
    std::vector<Place> places = routeSearcher.getCityMap().getAllPlaces();
    for (std::vector<Place>::iterator it = places.begin(); it != places.end(); ++it)
    {
        result.emplace_back(std::pair<std::string, int>((*it).getName(), (*it).getId()));
    }
    return result;
}

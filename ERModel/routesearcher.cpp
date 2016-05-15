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

void RouteSearcher::save() {
    std::ofstream f;
    f.open("data", std::ios::binary | std::ios::out);
    if (!f.fail()) {
        f << cityMap;
    }
    f.close();
}

void RouteSearcher::load() {
    std::ifstream f;
    f.open("data", std::ios::binary | std::ios::in);
    if (!f.fail()) {
        std::cout << "File found" << std::endl;
        f >> cityMap;
    }
    f.close();
}

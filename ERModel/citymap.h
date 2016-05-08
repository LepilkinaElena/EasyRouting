#ifndef CITYMAP_H
#define CITYMAP_H

#include "Multigraph/multigraph.h"
#include "place.h"
#include "routecost.h"

class CityMap
{
public:
    static CityMap& Instance();
    std::vector<Place > & getSinglePlaces();
    int addRoute(const Place& from, const Place& to, RouteCost *cost);
    Place & getPlaceById(int id);
    std::vector<Place> getAllPlaces() const;

private:
    CityMap();
    ~CityMap();
    Multigraph::Multigraph<Place> graph;
    std::vector<Place> singlePlaces;
};

#endif // CITYMAP_H

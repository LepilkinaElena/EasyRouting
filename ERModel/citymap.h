#ifndef CITYMAP_H
#define CITYMAP_H

#include "Multigraph/multigraph.h"
#include "place.h"
#include "routecost.h"

class CityMap
{
public:
    static CityMap * Instance();

    std::vector<Place > & getSinglePlaces();
    Multigraph::Multigraph<Place > & getGraph();
    Place & getPlaceById(int id);
private:
    CityMap();
    static CityMap * instance;
    Multigraph::Multigraph<Place> graph;
    std::vector<Place> singlePlaces;
};

#endif // CITYMAP_H

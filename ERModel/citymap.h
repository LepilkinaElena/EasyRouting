#ifndef CITYMAP_H
#define CITYMAP_H

#include "Multigraph/multigraph.h"
#include "place.h"
#include "routecost.h"
#include "path.h"
#include <typeinfo>

class CityMap
{
public:
    struct routeId
    {
        int id;
        int from;
        int to;
    };

    static CityMap& Instance();
    //std::vector<Place > & getSinglePlaces();
    int addRoute(const Place& from, const Place& to, RouteCost *cost);
    Place getPlaceById(unsigned int id);
    std::vector<Place> getAllPlaces() const;
    std::vector<routeId> getAllRoutes();
    void removePlaceById(unsigned int id);
    void removeRouteById(int id);
    std::vector<std::vector<Path> > getRoutes(const Place &start, const Place &finish,
                   const RouteCost& limits);
    friend std::ostream& operator<< (std::ostream& output, const CityMap& object);
    friend std::istream& operator>> (std::istream& input, CityMap& object);

    void loadDefaultMap();
private:
    CityMap();
    ~CityMap();
    Multigraph::Multigraph<Place> graph;
    //std::vector<Place> singlePlaces;
};

#endif // CITYMAP_H

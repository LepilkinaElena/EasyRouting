#ifndef PATH_H
#define PATH_H

#include "place.h"
#include "routecost.h"

class Path {
private:
    const Place from;
    const Place to;
    const RouteCost cost;
    
public:
    Path(const Place& from, const Place& to, const RouteCost& cost);
    const Place& getFrom() const;
    const Place& getTo() const;
    const RouteCost& getRouteCost() const;
    int getTotalCost();
    int getTotalTime();
};

#endif

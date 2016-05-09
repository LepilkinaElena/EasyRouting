#include "path.h"


Path::Path(const Place& from, const Place& to, const RouteCost& cost):
    from(from), to(to), cost(cost)
{

}

const Place& Path::getFrom() const
{
    return from;
}

const Place& Path::getTo() const
{
    return to;
}

const RouteCost& Path::getRouteCost() const
{
    return cost;
}

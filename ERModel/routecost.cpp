#include "routecost.h"
#include <typeinfo>
#include <iostream>

RouteCost::RouteCost() : Multigraph::Cost()
{
}

RouteCost::RouteCost(int money, int time, std::set<Interest> interest, std::set<Transport> transport) : Multigraph::Cost()
{
    this->moneyCost = money;
    this->timeCost = time;
    this->interests = interest;
    this->transports = transport;
}

Multigraph::Cost RouteCost::operator +(const Cost &other)
{
    std::set<Transport> resultTransport = this->transports;
    std::set<Interest> resultInterests = this->interests;

    try
    {
        const RouteCost& routeOther = dynamic_cast<const RouteCost&>(other);
        resultTransport.insert(routeOther.transports.begin(), routeOther.transports.end());
        resultInterests.insert(routeOther.interests.begin(), routeOther.interests.end());
        RouteCost result = RouteCost(this->moneyCost + routeOther.moneyCost,
                         this->timeCost + routeOther.timeCost,
                         resultInterests, resultTransport);
        return result;
    }
    catch (const std::bad_cast& e)
    {
        std::cerr << e.what() << std::endl;
        std::cerr << "Этот объект не является объектом типа RouteCost" << std::endl;
    }
}

#include "routecost.h"
#include <typeinfo>
#include <iostream>

RouteCost::RouteCost() : Multigraph::Cost()
{
}

RouteCost::RouteCost(int money, QTime time, std::set<Interest> interest, std::set<Transport> transport) : Multigraph::Cost()
{
    this->moneyCost = money;
    this->timeCost = time;
    this->interests = interest;
    this->transports = transport;
}

Multigraph::Cost *RouteCost::operator +(const Cost &other) const
{
    std::set<Transport> resultTransport = this->transports;
    std::set<Interest> resultInterests = this->interests;

    try
    {
        const RouteCost& routeOther = dynamic_cast<const RouteCost&>(other);
        resultTransport.insert(routeOther.transports.begin(), routeOther.transports.end());
        resultInterests.insert(routeOther.interests.begin(), routeOther.interests.end());
        RouteCost* result = new RouteCost(this->moneyCost + routeOther.moneyCost,
                         QTime(this->timeCost.hour() + routeOther.timeCost.hour(), this->timeCost.minute() + routeOther.timeCost.minute()),
                         resultInterests, resultTransport);
        return result;
    }
    catch (const std::bad_cast& e)
    {
        std::cerr << e.what() << std::endl;
        std::cerr << "Этот объект не является объектом типа RouteCost" << std::endl;
    }
}

bool RouteCost::operator <=(const Cost &other) const
{
    try
    {
        const RouteCost& routeOther = dynamic_cast<const RouteCost&>(other);
        bool transportFlag = true;
        for (std::set<Transport>::iterator it = transports.begin(); it != transports.end(); ++it)
        {
            transportFlag = transportFlag && routeOther.transports.find(*it) != routeOther.transports.end();
        }
        bool interestsFlag = true;
        for (std::set<Interest>::iterator it = interests.begin(); it != interests.end(); ++it)
        {
            interestsFlag = interestsFlag && routeOther.interests.find(*it) != routeOther.interests.end();
        }
        return moneyCost <= routeOther.moneyCost && timeCost <= routeOther.timeCost && transportFlag && interestsFlag;
    }
    catch (const std::bad_cast& e)
    {
        std::cerr << e.what() << std::endl;
        std::cerr << "Этот объект не является объектом типа RouteCost" << std::endl;
    }
}

int RouteCost::getMoneyCost() const
{
    return moneyCost;
}

QTime RouteCost::getTimeCost() const
{
    return timeCost;
}

std::set<Interest> RouteCost::getInterests() const
{
    return interests;
}

std::set<Transport> RouteCost::getTransport() const
{
    return transports;
}

std::ostream& RouteCost::save (std::ostream& output) const {
//    output.write((char*) &moneyCost, sizeof(moneyCost));
//    output.write((char*) &timeCost, sizeof(timeCost));

    return output;
}


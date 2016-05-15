#include "routecost.h"
#include <typeinfo>
#include <iostream>

RouteCost::RouteCost() : Multigraph::Cost()
{
}

RouteCost::~RouteCost()
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
    return NULL;
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
    return NULL;
}

bool RouteCost::operator ==(const Cost &other) const
{
    try
    {
        const RouteCost& routeOther = dynamic_cast<const RouteCost&>(other);
        bool transportFlag = transports.size() == routeOther.transports.size();
        for (std::set<Transport>::iterator it = transports.begin(); it != transports.end(); ++it)
        {
            transportFlag = transportFlag && routeOther.transports.find(*it) != routeOther.transports.end();
        }
        bool interestsFlag = interests.size() == routeOther.interests.size();
        for (std::set<Interest>::iterator it = interests.begin(); it != interests.end(); ++it)
        {
            interestsFlag = interestsFlag && routeOther.interests.find(*it) != routeOther.interests.end();
        }
        return moneyCost == routeOther.moneyCost && timeCost == routeOther.timeCost && transportFlag && interestsFlag;
    }
    catch (const std::bad_cast& e)
    {
        std::cerr << e.what() << std::endl;
        std::cerr << "Этот объект не является объектом типа RouteCost" << std::endl;
    }
    return false;
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
    output.write((char*) &moneyCost, sizeof(moneyCost));
    int hour = timeCost.hour();
    int min = timeCost.minute();
    int sec = timeCost.second();
    output.write((char*) &hour, sizeof(int));
    output.write((char*) &min, sizeof(int));
    output.write((char*) &sec, sizeof(int));
    unsigned int interestsCount = (unsigned int) interests.size();
    unsigned int transportsCount = (unsigned int) transports.size();
    output.write((char*) &interestsCount, sizeof(interestsCount));
    for (auto const& element : interests) {
        output.write((char*) &element, sizeof(element));
    }
    output.write((char*) &transportsCount, sizeof(transportsCount));
    for (auto const& element : transports) {
        output.write((char*) &element, sizeof(element));
    }

    return output;
}

std::istream& RouteCost::load(std::istream& input)
{
    char moneyBuf[sizeof(int)];
    input.read(moneyBuf, sizeof(int));
    this->moneyCost = (int) *moneyBuf;

    char timeBuf[sizeof(int)];
    input.read(timeBuf, sizeof(int));
    int hour = (int) *timeBuf;
    input.read(timeBuf, sizeof(int));
    int min = (int) *timeBuf;
    input.read(timeBuf, sizeof(int));
    int sec = (int) *timeBuf;
    this->timeCost = QTime(hour, min, sec);

    char countBuf[sizeof(unsigned int)];
    input.read(countBuf, sizeof(unsigned int));
    unsigned int interestsCount = (unsigned int) *countBuf;
    interests = std::set<Interest>();

    char interestBuf[sizeof(Interest)];
    for (int i = 0; i < interestsCount; i++) {
        input.read(interestBuf, sizeof(Interest));
        interests.insert((Interest) *interestBuf);
    }

    input.read(countBuf, sizeof(unsigned int));
    unsigned int transportsCount = (unsigned int) *countBuf;
    transports = std::set<Transport>();

    char transportBuf[sizeof(Transport)];
    for (int i = 0; i < transportsCount; i++) {
        input.read(transportBuf, sizeof(Transport));
        transports.insert((Transport) *transportBuf);
    }

    return input;
}


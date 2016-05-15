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
    char intBuf[sizeof(int)];
    strncpy(intBuf, reinterpret_cast<const char*>(&moneyCost), sizeof(int));
    output.write(intBuf, sizeof(moneyCost));
    int hour = timeCost.hour();
    strncpy(intBuf, reinterpret_cast<const char*>(&hour), sizeof(int));
    output.write(intBuf, sizeof(hour));
    int min = timeCost.minute();
    strncpy(intBuf, reinterpret_cast<const char*>(&min), sizeof(int));
    output.write(intBuf, sizeof(min));
    int sec = timeCost.second();
    strncpy(intBuf, reinterpret_cast<const char*>(&sec), sizeof(int));
    output.write(intBuf, sizeof(sec));

    unsigned int interestsCount = (unsigned int) interests.size();
    unsigned int transportsCount = (unsigned int) transports.size();
    strncpy(intBuf, reinterpret_cast<const char*>(&interestsCount), sizeof(int));
    output.write(intBuf, sizeof(interestsCount));
    char interestBuf[sizeof(Interest)];
    for (auto const& element : interests) {
        strncpy(interestBuf, reinterpret_cast<const char*>(&element), sizeof(Interest));
        output.write(interestBuf, sizeof(Interest));
    }
    strcpy(intBuf, reinterpret_cast<const char*>(&transportsCount));
    output.write(intBuf, sizeof(transportsCount));
    char transportBuf[sizeof(Transport)];
    for (auto const& element : transports) {
        strncpy(transportBuf, reinterpret_cast<const char*>(&element), sizeof(Interest));
        output.write(transportBuf, sizeof(Transport));
    }

    return output;
}

std::istream& RouteCost::load(std::istream& input)
{
    char intBuf[sizeof(int)];
    input.read(intBuf, sizeof(int));
    moneyCost = *(reinterpret_cast<int*>(intBuf));
    std::cout << "read moneyCost "<<moneyCost<<std::endl;

    int hour,min,sec;
    input.read(intBuf, sizeof(int));
    hour = *(reinterpret_cast<int*>(intBuf));
    input.read(intBuf, sizeof(int));
    min = *(reinterpret_cast<int*>(intBuf));
    input.read(intBuf, sizeof(int));
    sec = *(reinterpret_cast<int*>(intBuf));
    this->timeCost = QTime(hour, min, sec);

    std::cout << "read time "<<hour<<" "<<min<<" "<<sec<<std::endl;

    input.read(intBuf, sizeof(int));
    unsigned int interestsCount = *(reinterpret_cast<int*>(intBuf));
    interests = std::set<Interest>();

    std::cout<<"read interests count "<<interestsCount << std::endl;

    for (int i = 0; i < interestsCount; i++) {
        input.read(intBuf, sizeof(int));
        Interest interest = *(reinterpret_cast<Interest*>(intBuf));
        interests.insert(interest);
    }

    input.read(intBuf, sizeof(int));
    unsigned int transportsCount = *(reinterpret_cast<int*>(intBuf));
    transports = std::set<Transport>();

    std::cout<<"read transports count "<<transportsCount << std::endl;

    for (int i = 0; i < transportsCount; i++) {
        input.read(intBuf, sizeof(int));
        Transport transport = *(reinterpret_cast<Transport*>(intBuf));
        transports.insert((Transport) transport);
    }

    return input;
}


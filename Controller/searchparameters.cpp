#include "searchparameters.h"

SearchParameters::SearchParameters()
{
}

void SearchParameters::setStart(int start)
{
    this->start = start;
}

void SearchParameters::setFinish(int finish)
{
    this->finish = finish;
}

void SearchParameters::setTravellersNumber(int number)
{
    travellersNumber = number;
}

void SearchParameters::setTime(QTime time)
{
    this->time = time;
}

void SearchParameters::setMoney(int money)
{
    this->money = money;
}

void SearchParameters::addTransport(Transport transport)
{
    this->transport.insert(transport);
}

void SearchParameters::addInterest(Interest interest)
{
    this->interests.insert(interest);
}

int SearchParameters::getStart()
{
    return start;
}

int SearchParameters::getFinish()
{
    return finish;
}

RouteCost SearchParameters::toRouteCost()
{
    return RouteCost(money/travellersNumber, time, interests, transport);
}

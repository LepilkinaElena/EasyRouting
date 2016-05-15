#ifndef SEARCHPARAMETERS_H
#define SEARCHPARAMETERS_H

#include<QTime>
#include"ERModel/routecost.h"

class SearchParameters
{
private:
    int start;
    int finish;
    int travellersNumber;
    QTime time;
    int money;
    std::set<Transport> transport;
    std::set<Interest> interests;

public:
    SearchParameters();
    void setStart(int start);
    void setFinish(int finish);
    void setTravellersNumber(int number);
    void setTime(QTime time);
    void setMoney(int money);
    void addTransport(Transport transport);
    void addInterest(Interest interest);

    int getMoney();
    QTime getTime();
    int getStart();
    int getFinish();
    int getTravellersNumber();

    RouteCost toRouteCost();
};

#endif // SEARCHPARAMETERS_H

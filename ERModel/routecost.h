/*!\file routecost.h
*\brief Файл с классом для описания веса маршрута
*/
#include <Multigraph/cost.h>
#include "place.h"
#include <set>

enum Transport {CAR, UNDERGROUND, BUS, TROLLEYBUS, TRAM, TAXI, FOOT};

/*!\class RouteCost
*\brief Класс веса маршрута
*\ref RouteCost
*/
class RouteCost : public Multigraph::Cost
{
private:
    /*!\var RouteCost::moneyCost
    *\brief денежные затраты
    */
    int moneyCost;

    /*!\var RouteCost::timeCost
    *\brief временные затраты
    */
    int timeCost;

    /*!\var RouteCost::interests
    *\brief категория интересов для данного маршрута
    */
    std::set<Interest> interests;

    /*!\var RouteCost::transports
    *\brief виды транспорта для данного маршрута
    */
    std::set<Transport> transports;

public:
    RouteCost();

    /*!\fn RouteCost(int money, int time, std::set<Interest> interest = std::set<Interest>(),
              std::set<Transport> transport = std::set<Transport>());
    *\brief Конструктор веса маршрута
    *\param [in] money - денежные затраты
    *\param [in] time - временные затраты
    *\param [in] interest - категории интересов для данного маршрута
    *\param [in] transport - виды транспорта для данного маршрута
    *\return вес маршрута
    */
    RouteCost(int money, int time, std::set<Interest> interest = std::set<Interest>(),
              std::set<Transport> transport = std::set<Transport>());

    Cost operator +(const Cost& other);
};

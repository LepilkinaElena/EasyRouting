/*!\file routesearcher.h
*\brief Файл с классом поисковика маршрутов
*/
#ifndef ROUTESEARCHER_H
#define ROUTESEARCHER_H

#include "citymap.h"
#include "DAO/DataAccessObject.h"
#include <iostream>
#include <fstream>
#include <iomanip>

/*!\class RouteSearcher
*\brief Класс поисковика маршрутов
*\ref RouteSearcher
*/
class RouteSearcher {  
private:
    /*!\var RouteSearcher::cityMap
    *\brief карта
    */
    CityMap& cityMap;

    DataAccessObject dao;
    
public:
    RouteSearcher();
    /*!\fn searchRoutes (int start, int finish, const RouteCost& limits);
    *\brief Найти пути
    *\param [in] start - начало маршрута
    *\param [in] finish - конец маршрута
    *\param [in] limits - ограничения на поиск маршрута
    *\return подходящие пути
    */
    std::vector<std::vector<Path> > searchRoutes (int start, int finish, const RouteCost& limits);
    const CityMap& getCityMap();
    /*!\fn load ();
     *\brief Десериализация карты
    */
    void load();
    /*!\fn load ();
     *\brief Сериализация карты
    */
    void save();
};

#endif

/*!\file controller.h
*\brief Файл с классом контроллера
*/
#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "ERModel/routesearcher.h"
#include "searchparameters.h"

/*!\class Controller
*\brief Класс контроллера
*\ref Controller
*/
class Controller
{
private:
    /*!\var Controller::routeSearcher
    *\brief поисковик путей
    */
    RouteSearcher routeSearcher;

public:
    Controller();
    /*!\fn getRouteSearcher();
    *\brief Метод получения поисковика
    *\return поисковик путей
    */

    RouteSearcher getRouteSearcher() { return routeSearcher; }
    /*!\fn getAllPlacesOnMap();
    *\brief Метод получения всех мест на карте
    *\return все места на карте
    */

    std::vector<std::pair<std::string, int> > getAllPlacesOnMap();

    /*!\fn runRouteSearch(SearchParameters parameters);
    *\brief Метод запуска поиска путей
    *\param [in] parameters - параметры для поиска
    *\return найденные пути
    */
    std::vector<std::vector<SearchParameters> > runRouteSearch(SearchParameters parameters);
    /*!\fn load ();
     *\brief Вызов сериализации из UI
    */
    void save();
    /*!\fn load ();
     *\brief Вызов десериализации из UI
    */
    void load();
};

#endif // CONTROLLER_H

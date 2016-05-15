/*!\file path.h
*\brief Файл с классом пути
*/
#ifndef PATH_H
#define PATH_H

#include "place.h"
#include "routecost.h"

/*!\class Path
*\brief Класс пути
*\ref Path
*/
class Path {
private:

    /*!\var Path::from
     *\brief место, из которого ведет путь
    */
    const Place from;
    /*!\var Path::to
     *\brief место, в которое ведет путь
    */
    const Place to;
    /*!\var RouteCost::cost
     *\brief стоимость пути
    */
    const RouteCost cost;
    
public:
    Path(const Place& from, const Place& to, const RouteCost& cost);

    /*!\fn getFrom() const;
     *\brief Метод для получения места, из которого ведет путь
     *\return место, из которого ведет путь
    */
    const Place& getFrom() const;
    /*!\fn  getTo() const;
     *\brief Метод для получения места, в которое ведет путь
     *\return место, из которого ведет путь
    */
    const Place& getTo() const;
    /*!\fn  RouteCost& getRouteCost() const;
     *\brief Метод получения стоимости пути
     *\return стоимость пути
    */
    const RouteCost& getRouteCost() const;
};

#endif

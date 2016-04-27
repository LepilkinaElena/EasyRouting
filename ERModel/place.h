/*!\file place.h
*\brief Файл с классом для описания места посещения
*/
#ifndef PLACE_H
#define PLACE_H
#include <string>

enum Interest { SIGHT, CULTURE, PARK, ENTERTAINMENT };

/*!\class Place
*\brief Класс места посещения
*\ref Place
*/
class Place
{
private:
    /*!\var Place::geoCoordX
    *\brief координата x на карте
    */
    double geoCoordX;

    /*!\var Place::geoCoordY
    *\brief координата y на карте
    */
    double geoCoordY;

    /*!\var Place::name
    *\brief название объекта
    */
    std::string name;

    /*!\var Place::intersestCategory
    *\brief категория интересов, которой принадлежит объект
    */
    Interest intersestCategory;

    static int counter;

    int id;

public:

    /*!\fn Place(double x, double y, std::string& placeName, Interest interest);
    *\brief Конструктор места посещения
    *\param [in] x - координата x
    *\param [in] y - координата y
    *\param [in] placeName - название места
    *\param [in] interest - категория интересов, которой принадлежит объект
    *\return место посещения
    */
    Place(double x, double y, std::string placeName, Interest interest);

    bool operator<(const Place other) const;
    bool operator ==(const Place other) const;

    int getId() const;
    double getGeoCoordX() const;
    double getGeoCoordY() const;
    std::string getName() const;
};

#endif

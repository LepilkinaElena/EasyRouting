/*!\file place.h
*\brief Файл с классом для описания места посещения
*/
#ifndef PLACE_H
#define PLACE_H
#include <string>
#include <iostream>
#include <cstring>

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

    static unsigned int counter;

    unsigned int id;

public:

    /*!\fn Place(double x, double y, std::string& placeName, Interest interest);
    *\brief Конструктор места посещения
    *\param [in] x - координата x
    *\param [in] y - координата y
    *\param [in] placeName - название места
    *\param [in] interest - категория интересов, которой принадлежит объект
    *\return место посещения
    */
    Place();
    Place(double x, double y, std::string placeName, Interest interest);
    Place(const Place& other);

    bool operator<(const Place other) const;
    bool operator ==(const Place other) const;

    bool operator !=(const Place other) const;

    unsigned int getId() const;
    double getGeoCoordX() const;
    double getGeoCoordY() const;
    std::string getName() const;
    Interest getIntersestCategory() const;

    friend std::ostream& operator<< (std::ostream& output, const Place& object);
    friend std::istream& operator>> (std::istream& input, Place& object);
};

#endif

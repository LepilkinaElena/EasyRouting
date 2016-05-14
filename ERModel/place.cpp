#include "place.h"

unsigned int Place::counter = 0;

unsigned int Place::getId() const
{
    return id;
}

double Place::getGeoCoordX() const
{
    return geoCoordX;
}

double Place::getGeoCoordY() const
{
    return geoCoordY;
}

std::string Place::getName() const
{
    return name;
}

Interest Place::getIntersestCategory() const
{
    return intersestCategory;
}

Place::Place(double x, double y, std::string placeName, Interest interest):
    geoCoordX(x), geoCoordY(y), name(placeName), intersestCategory(interest) {
    id = counter;
    counter++;
}

bool Place::operator<(const Place other) const
{
    return geoCoordX < other.geoCoordX;
}

bool Place::operator ==(const Place other) const
{
    return geoCoordX == other.geoCoordX &&
           geoCoordY == other.geoCoordY &&
           name == other.name &&
           intersestCategory == other.intersestCategory;
}

bool Place::operator !=(const Place other) const
{
    return !((*this) == other);
}

Place::Place(const Place &other)
{
    geoCoordX = other.geoCoordX;
    geoCoordY = other.geoCoordY;
    name = other.name;
    id = other.id;
    intersestCategory = other.intersestCategory;
}

std::ostream& operator<< (std::ostream& output, const Place& object) {
    unsigned int id = object.getId();
    double x = object.getGeoCoordX();
    double y = object.getGeoCoordY();
    Interest interest = object.getIntersestCategory();
    std::string name = object.getName();

    output.write((char*) &id, sizeof(id));
    output.write((char*) &x, sizeof(x));
    output.write((char*) &y, sizeof(y));
    output.write((char*) &interest, sizeof(interest));
    output.write((char*) &name, sizeof(name));

    return output;
}


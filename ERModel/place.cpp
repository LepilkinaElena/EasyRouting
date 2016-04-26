#include "place.h"

int Place::counter = 0;

int Place::getId() const
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

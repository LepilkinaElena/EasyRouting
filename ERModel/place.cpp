#include "place.h"

Place::Place(double x, double y, std::string placeName, Interest interest):
    geoCoordX(x), geoCoordY(y), name(placeName), intersestCategory(interest) {}

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

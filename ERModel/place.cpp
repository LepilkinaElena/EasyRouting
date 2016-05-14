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

Place::Place()
{

}

Place::Place(const Place &other)
{
    geoCoordX = other.geoCoordX;
    geoCoordY = other.geoCoordY;
    name = other.name;
    id = other.id;
    intersestCategory = other.intersestCategory;
}

std::ostream& operator<< (std::ostream& output, const Place& object)
{
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

std::istream& operator>> (std::istream& input, Place& object)
{
    char idBuf[sizeof(unsigned int)];
    input.read(idBuf, sizeof(unsigned int));
    unsigned int id = (int) *idBuf;
    char coordBuf[sizeof(double)];
    input.read(coordBuf, sizeof(double));
    double x = (double) *coordBuf;
    input.read(coordBuf, sizeof(double));
    double y = (double) *coordBuf;
    char interestBuf[sizeof(Interest)];
    input.read(interestBuf, sizeof(Interest));
    Interest interest = (Interest) *interestBuf;
    char nameBuf[sizeof(std::string)];
    input.read(nameBuf, sizeof(std::string));
    std::string name(nameBuf);

    object.id = id;
    object.geoCoordX = x;
    object.geoCoordY = y;
    object.intersestCategory = interest;
    object.name = name;

    return input;
}



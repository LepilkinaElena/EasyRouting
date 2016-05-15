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
    const char* name = object.getName().c_str();

    output.write(reinterpret_cast<char*>(&id), sizeof(id));
    output.write(reinterpret_cast<char*>(&x), sizeof(x));
    output.write(reinterpret_cast<char*>(&y), sizeof(y));
    output.write(reinterpret_cast<char*>(&interest), sizeof(interest));
    output.write(name, sizeof(char)*strlen(name));

//    output << id << x << y << interest << name;

    return output;
}

std::istream& operator>> (std::istream& input, Place& object)
{
    char idBuf[sizeof(unsigned int)];
    input.read(idBuf, sizeof(unsigned int));
    unsigned int id = *(reinterpret_cast<unsigned int*>(idBuf));
    char coordBuf[sizeof(double)];
    input.read(coordBuf, sizeof(double));
    double x = *(reinterpret_cast<double*>(coordBuf));
    input.read(coordBuf, sizeof(double));
    double y = *(reinterpret_cast<double*>(coordBuf));
    char interestBuf[sizeof(Interest)];
    input.read(interestBuf, sizeof(Interest));
    Interest interest = *(reinterpret_cast<Interest*>(interestBuf));
    input.read(idBuf, sizeof(unsigned int));
    unsigned int nameLen = *(reinterpret_cast<unsigned int*>(idBuf));
    char nameBuf[sizeof(char)*nameLen];
    input.read(nameBuf, sizeof(std::string));
    std::string name(nameBuf);

    object.id = id;
    object.geoCoordX = x;
    object.geoCoordY = y;
    object.intersestCategory = interest;
    object.name = name;

//    int category = (int) object.intersestCategory;
//    input >> object.id >> object.geoCoordX >> object.geoCoordY >> category >> object.name;

    return input;
}



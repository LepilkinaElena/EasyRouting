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
    unsigned int nameLen = strlen(name);

    output.write(reinterpret_cast<char*>(&nameLen), sizeof(unsigned int));
    std::cout<<"write nameLen " << nameLen<<std::endl;
    output.write(name, strlen(name));
    std::cout<<"write name " << name<<std::endl;

    output.write(reinterpret_cast<char*>(&id), sizeof(unsigned int));
    std::cout<<"write id " << id<<std::endl;
    output.write(reinterpret_cast<char*>(&x), sizeof(double));
    std::cout<<"write x " << x<<std::endl;
    output.write(reinterpret_cast<char*>(&y), sizeof(double));
    std::cout<<"write y " << y<<std::endl;
    unsigned int inter = (unsigned int)interest;
    output.write(reinterpret_cast<char*>(&inter), sizeof(unsigned int));
    std::cout<<"write interest " << (int)interest<<std::endl;

    return output;
}

std::istream& operator>> (std::istream& input, Place& object)
{
    char idBuf[sizeof(unsigned int)];
    memset(idBuf,0,sizeof(int));

    input.read(idBuf, sizeof(unsigned int));
    unsigned int nameLen = *(reinterpret_cast<unsigned int*>(idBuf));
    std::cout<<"read nameLen " << nameLen<<std::endl;
    char nameBuf[nameLen+1];
    memset(nameBuf,0,nameLen+1);
    input.read(nameBuf, nameLen);
    std::string name(nameBuf);
    std::cout<<"read name " << name<<std::endl;

    input.read(idBuf, sizeof(unsigned int));
    unsigned int id = *(reinterpret_cast<unsigned int*>(idBuf));
    std::cout<<"read id " << id<<std::endl;
    char coordBuf[sizeof(double)];
    memset(coordBuf, 0 , sizeof(double));
    input.read(coordBuf, sizeof(double));
    double x = *(reinterpret_cast<double*>(coordBuf));
    std::cout<<"read x " << x<<std::endl;
    input.read(coordBuf, sizeof(double));
    double y = *(reinterpret_cast<double*>(coordBuf));
    std::cout<<"read y " << y<<std::endl;
    char interestBuf[sizeof(unsigned int)];
    memset(interestBuf, 0 , sizeof(unsigned int));
    input.read(interestBuf, sizeof(unsigned int));
    Interest interest = *(reinterpret_cast<Interest*>(interestBuf));
    std::cout<<"read interest " << (int)interest<<std::endl;

    object.id = id;
    if (id >= Place::counter) {
        Place::counter = id + 1;
        std::cout<<"====="<<Place::counter<<std::endl;
    }
    object.geoCoordX = x;
    object.geoCoordY = y;
    object.intersestCategory = interest;
    object.name = name;

    return input;
}



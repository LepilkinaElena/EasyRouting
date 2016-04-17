#include "place.h"

Place::Place(double x, double y, std::string& placeName, Interest interest):
    geoCoordX(x), geoCoordY(y), name(placeName), intersestCategory(interest) {}

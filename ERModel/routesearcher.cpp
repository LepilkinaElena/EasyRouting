#include "routesearcher.h"
#include <Exceptions/nullpointerexception.h>

const std::string KEY = "easyroutingdata";

RouteSearcher::RouteSearcher():cityMap(CityMap::Instance())
{
}

const CityMap& RouteSearcher::getCityMap()
{
    return cityMap;
}

std::vector<std::vector<Path> > RouteSearcher::searchRoutes(int start, int finish, const RouteCost &limits)
{
    Place startPlace = cityMap.getPlaceById(start);
    Place finishPlace = cityMap.getPlaceById(finish);
    return cityMap.getRoutes(startPlace, finishPlace, limits);
}

/*!\fn decorate (std::ostream& stream);
 *\brief Манипулятор для ввода ключа в начало файла
 *\param [in] stream - манипулируемый поток
 *\return декорированный поток
 */
std::ostream& decorate(std::ostream& stream) {
    stream << KEY;
    return stream;
}

void RouteSearcher::save() {
    std::ofstream f;
    f.open("data", std::ios::binary | std::ios::out);
    if (!f.fail()) {
        f << decorate << cityMap;
    }
    f.close();
}

void RouteSearcher::load() {
    std::ifstream f;
    f.open("data", std::ios::binary | std::ios::in);
    if (!f.fail()) {
        f.seekg(0, f.end);
//        fileLength = f.tellg();
        f.seekg(0, f.beg);
        char buffer[KEY.length()];
        memset(buffer, 0, KEY.length());
        f.read(buffer, KEY.length());
        if (strncmp(buffer, KEY.c_str(), KEY.length()) == 0) {
           f >> cityMap;
        } else {
            std::cerr << "File is incorrect" << std::endl;
        }
    } else {
        std::cerr << "Error load file" << std::endl;
    }
    f.close();
}


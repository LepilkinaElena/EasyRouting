#include "citymap.h"

CityMap& CityMap::Instance()
{
    static CityMap instance;
    return instance;
}

CityMap::CityMap()
{
    // TODO load from file

}

CityMap::~CityMap()
{

}

int CityMap::addRoute(const Place &from, const Place &to, RouteCost *cost)
{
    try
    {
        return graph.addEdge(from, to, cost);
    }
    catch (EdgeAbsenceMultigraphException)
    {
        std::cerr << "Добавляемая стоимость пути нулевая.";
    }
}

std::vector<Place> CityMap::getAllPlaces() const
{
    return graph.getAllVertexes();
}

std::vector<CityMap::routeId> CityMap::getAllRoutes()
{
    std::vector<CityMap::routeId> result;
    std::vector<int> edges = graph.getAllEdges();
    std::vector<int>::iterator it = edges.begin();
    while(it != edges.end())
    {
        int id = *it;
        CityMap::routeId routeTemp;
        routeTemp.id = id;
        routeTemp.from = graph.getFrom(id).getId();
        routeTemp.to = graph.getTo(id).getId();
        result.push_back(routeTemp);

        it++;
    }
    return result;
}

void CityMap::removePlaceById(unsigned int id)
{
    std::vector<Place> places = graph.getAllVertexes();
    std::vector<Place>::iterator it = places.begin();
    while(it != places.end())
    {
        if(it.operator *().getId() == id)
        {
            graph.removeVertex((it.operator *()));
            break;
        }
        it++;
    }
}

void CityMap::removeRouteById(int id)
{
    graph.removeEdge(id);
}

Place CityMap::getPlaceById(unsigned int id)
{
    std::vector<Place> places = graph.getAllVertexes();
    std::vector<Place>::iterator it = places.begin();
    while(it != places.end())
    {
        if(it.operator *().getId() == id)
        {
            return (it.operator *());
        }
        it++;
    }
    return places.back();
}

/*std::vector<Place > & CityMap::getSinglePlaces()
{
    return singlePlaces;
}*/

std::vector<std::vector<Path> > CityMap::getRoutes(const Place &start, const Place &finish,
                        const RouteCost& limits)
{
    std::vector<std::vector<Path> > routes;
    std::vector<std::vector<int> > result = graph.searchRoutesWithLimits(start, finish, limits);
    std::vector<std::vector<int> >::iterator it;

    for (it = result.begin(); it != result.end(); ++it)
    {
        std::vector<int> current = (*it);
        std::vector<Path> route = std::vector<Path>();
        for (std::vector<int>::iterator iter = current.begin(); iter != current.end(); ++iter)
        {
            try
            {
                const RouteCost* routeCost = dynamic_cast<const RouteCost*>(graph.getCost(*iter));
                Path path = Path(graph.getFrom(*iter), graph.getTo(*iter), *routeCost);
                route.emplace_back(path);
            }
            catch (const std::bad_cast& e)
            {
                std::cerr << e.what() << std::endl;
                std::cerr << "Этот объект не является объектом типа RouteCost" << std::endl;
            }
        }
        routes.emplace_back(route);
    }
    return routes;
}

void CityMap::loadDefaultMap()
{
    Place place1 = Place(59.9165, 30.3072, std::string("Эрмитаж"), Interest::SIGHT);
    Place place2 = Place(59.9539, 30.3113, std::string("Кино"), Interest::ENTERTAINMENT);
    Place place3 = Place(59.9465, 30.4143, std::string("Парк Победы"), Interest::PARK);
    Place place4 = Place(59.9746, 30.3673, std::string("Театр"), Interest::CULTURE);
    Place place5 = Place(59.9632, 30.1874, std::string("Казанский собор"), Interest::SIGHT);
    Place place6 = Place(59.9413, 30.2775, std::string("Выставка"), Interest::CULTURE);
    Place place7 = Place(59.9528, 30.2763, std::string("Медный всадник"), Interest::SIGHT);

    std::set<Interest> set1 = std::set<Interest>();
    set1.insert(Interest::CULTURE);

    std::set<Interest> set2 = std::set<Interest>();
    set2.insert(Interest::SIGHT);

    std::set<Interest> set3 = std::set<Interest>();
    set3.insert(Interest::PARK);

    std::set<Interest> set4 = std::set<Interest>();
    set4.insert(Interest::ENTERTAINMENT);

    std::set<Transport> set5 = std::set<Transport>();
    set5.insert(Transport::CAR);

    std::set<Transport> set6 = std::set<Transport>();
    set6.insert(Transport::UNDERGROUND);

    std::set<Transport> set7 = std::set<Transport>();
    set7.insert(Transport::BUS);

    std::set<Transport> set8 = std::set<Transport>();
    set8.insert(Transport::TROLLEYBUS);

    std::set<Transport> set9 = std::set<Transport>();
    set9.insert(Transport::TRAM);

    std::set<Transport> set10 = std::set<Transport>();
    set10.insert(Transport::TAXI);

    std::set<Transport> set11 = std::set<Transport>();
    set11.insert(Transport::FOOT);

    RouteCost* aCost = new RouteCost(100, QTime(0, 58, 0), set1, set6 );
    RouteCost* bCost = new RouteCost(132, QTime(1, 2, 0), set4, set7);
    RouteCost* cCost = new RouteCost(160, QTime(0, 48, 0), set4, set5);
    RouteCost* dCost = new RouteCost(35, QTime(0, 32, 0), set3, set6);
    RouteCost* eCost = new RouteCost(120, QTime(2, 0, 0), set1, set10);
    RouteCost* fCost = new RouteCost(205, QTime(1, 24, 0), set1, set11);
    RouteCost* hCost = new RouteCost(140, QTime(1, 2, 0), set1, set8);
    RouteCost* gCost = new RouteCost(130, QTime(1, 15, 0), set2, set9);
    RouteCost* kCost = new RouteCost(0, QTime(0, 12, 0), set2, set11);
    RouteCost* lCost = new RouteCost(0, QTime(0, 20, 0), set2, set11);
    RouteCost* mCost = new RouteCost(80, QTime(0, 51, 0), set2, set7);
    RouteCost* nCost = new RouteCost(205, QTime(1, 23, 0), set1, set6);

    graph.addEdge(place1, place4, aCost);
    graph.addEdge(place1, place3, dCost);
    graph.addEdge(place1, place2, bCost);
    graph.addEdge(place1, place2, cCost);
    graph.addEdge(place3, place6, fCost);
    graph.addEdge(place3, place4, eCost);
    graph.addEdge(place2, place5, gCost);
    graph.addEdge(place5, place4, hCost);
    graph.addEdge(place4, place7, kCost);
    graph.addEdge(place5, place7, lCost);
    graph.addEdge(place6, place5, mCost);
    graph.addEdge(place5, place6, nCost);
}

std::ostream& operator<< (std::ostream& output, const CityMap& object)
{
    output << object.graph;
    return output;
}

std::istream& operator>> (std::istream& input, CityMap& object)
{
    input >> object.graph;
    return input;
}

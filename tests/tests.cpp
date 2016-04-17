#include "tests.h"

Multigraph::Multigraph<Place>Tests::getGraph()
{
    Multigraph::Multigraph<Place> graph = Multigraph::Multigraph<Place>();

    // Создаем места

    Place place1 = Place(0, 0, std::string("Эрмитаж"), Interest::SIGHT);
    Place place2 = Place(1, 1, std::string("Кино"), Interest::ENTERTAINMENT);
    Place place3 = Place(2, 2, std::string("Парк Победы"), Interest::PARK);
    Place place4 = Place(3, 3, std::string("Театр"), Interest::CULTURE);
    Place place5 = Place(4, 4, std::string("Казанский собор"), Interest::SIGHT);
    Place place6 = Place(5, 5, std::string("Выставка"), Interest::CULTURE);
    Place place7 = Place(6, 6, std::string("Медный всадник"), Interest::SIGHT);



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

    RouteCost aCost = RouteCost(100, QTime(0, 58, 0), set1, set6 );

    graph.addEdge(place1, place2, (Cost)aCost);
}

void Tests::test1()
{
    Multigraph::Multigraph<Place> graph = Multigraph::Multigraph<Place>();
}

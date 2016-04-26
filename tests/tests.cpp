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
    RouteCost bCost = RouteCost(132, QTime(1, 2, 0), set4, set7);
    RouteCost cCost = RouteCost(160, QTime(0, 48, 0), set4, set5);
    RouteCost dCost = RouteCost(35, QTime(0,32, 0), set3, set6);
    RouteCost eCost = RouteCost(120, QTime(2, 0, 0), set1, set10);
    RouteCost fCost = RouteCost(205, QTime(1, 24, 0), set1, set11);
    RouteCost hCost = RouteCost(140, QTime(1, 2, 0), set1, set8);
    RouteCost gCost = RouteCost(130, QTime(1, 15, 0), set2, set9);
    RouteCost kCost = RouteCost(0, QTime(0, 12, 0), set2, set11);
    RouteCost lCost = RouteCost(0, QTime(0, 20, 0), set2, set11);
    RouteCost mCost = RouteCost(80, QTime(0, 51, 0), set2, set7);
    RouteCost nCost = RouteCost(205, QTime(1, 23, 0), set1, set6);

    graph.addEdge(place1, place4, (Cost)aCost);
    graph.addEdge(place1, place3, (Cost)dCost);
    graph.addEdge(place1, place2, (Cost)bCost);
    graph.addEdge(place1, place2, (Cost)cCost);
    graph.addEdge(place3, place6, (Cost)fCost);
    graph.addEdge(place3, place4, (Cost)eCost);
    graph.addEdge(place2, place5, (Cost)gCost);
    graph.addEdge(place5, place4, (Cost)hCost);
    graph.addEdge(place4, place7, (Cost)kCost);
    graph.addEdge(place5, place7, (Cost)lCost);
    graph.addEdge(place6, place5, (Cost)mCost);
    graph.addEdge(place5, place6, (Cost)nCost);

    return graph;
}

void Tests::no_route()
{
    Multigraph::Multigraph<Place> graph = getGraph();
    Place place1 = Place(0, 0, std::string("Эрмитаж"), Interest::SIGHT);
    Place place6 = Place(5, 5, std::string("Выставка"), Interest::CULTURE);

    std::set<Transport> set11 = std::set<Transport>();
    set11.insert(Transport::FOOT);
    std::set<Interest> set1 = std::set<Interest>();
    set1.insert(Interest::CULTURE);

    RouteCost cost = RouteCost(20, QTime(4, 0, 0), set1, set11);
    std::vector<std::vector<int> > actual = graph.waveAlgorithm(place1, place6, (Cost)cost);
    std::vector<std::vector<int> > expected = std::vector<std::vector<int> >();
    QCOMPARE(actual, expected);
}

void Tests::one_route()
{
    Multigraph::Multigraph<Place> graph = getGraph();

    Place place3 = Place(2, 2, std::string("Парк Победы"), Interest::PARK);
    Place place5 = Place(4, 4, std::string("Казанский собор"), Interest::SIGHT);

    std::set<Interest> interests = std::set<Interest>();
    interests.insert(Interest::CULTURE);
    interests.insert(Interest::SIGHT);

    std::set<Transport> transport = std::set<Transport>();
    transport.insert(Transport::BUS);
    transport.insert(Transport::FOOT);

    RouteCost cost = RouteCost(1000, QTime(2, 50, 0), interests, transport);
    std::vector<std::vector<int> > actual = graph.waveAlgorithm(place3, place5, (Cost)cost);
    std::vector<std::vector<int> > expected = std::vector<std::vector<int> >();
    std::vector<int> route = std::vector<int>();
    route.emplace_back(5);
    route.emplace_back(10);
    expected.emplace_back(route);
    QCOMPARE(actual, expected);
}

void Tests::several_routes()
{
    Multigraph::Multigraph<Place> graph = getGraph();

    Place place1 = Place(0, 0, std::string("Эрмитаж"), Interest::SIGHT);
    Place place4 = Place(3, 3, std::string("Театр"), Interest::CULTURE);

    std::set<Interest> interests = std::set<Interest>();
    interests.insert(Interest::CULTURE);
    interests.insert(Interest::SIGHT);
    interests.insert(Interest::ENTERTAINMENT);
    interests.insert(Interest::PARK);

    std::set<Transport> transport = std::set<Transport>();
    transport.insert(Transport::BUS);
    transport.insert(Transport::FOOT);
    transport.insert(Transport::TRAM);
    transport.insert(Transport::CAR);
    transport.insert(Transport::UNDERGROUND);
    transport.insert(Transport::TROLLEYBUS);
    transport.insert(Transport::TAXI);

    RouteCost cost = RouteCost(5000, QTime(10, 0, 0), interests, transport);
    std::vector<std::vector<int> > actual = graph.waveAlgorithm(place1, place4, (Cost)cost);
    std::vector<std::vector<int> > expected = std::vector<std::vector<int> >();
    std::vector<int> route1 = std::vector<int>();
    route1.emplace_back(0);
    std::vector<int> route2 = std::vector<int>();
    route2.emplace_back(3);
    route2.emplace_back(4);
    std::vector<int> route3 = std::vector<int>();
    route3.emplace_back(1);
    route3.emplace_back(7);
    route3.emplace_back(6);
    std::vector<int> route4 = std::vector<int>();
    route4.emplace_back(2);
    route4.emplace_back(7);
    route4.emplace_back(6);
    expected.emplace_back(route1);
    expected.emplace_back(route2);
    expected.emplace_back(route3);
    expected.emplace_back(route4);
    QCOMPARE(actual, expected);
}

void Tests::cycle_route()
{
    Multigraph::Multigraph<Place> graph = getGraph();
    Place place2 = Place(1, 1, std::string("Кино"), Interest::ENTERTAINMENT);
    Place place6 = Place(5, 5, std::string("Выставка"), Interest::CULTURE);

    std::set<Interest> interests = std::set<Interest>();
    interests.insert(Interest::CULTURE);
    interests.insert(Interest::SIGHT);
    interests.insert(Interest::ENTERTAINMENT);
    interests.insert(Interest::PARK);

    std::set<Transport> transport = std::set<Transport>();
    transport.insert(Transport::BUS);
    transport.insert(Transport::FOOT);
    transport.insert(Transport::TRAM);
    transport.insert(Transport::CAR);
    transport.insert(Transport::UNDERGROUND);
    transport.insert(Transport::TROLLEYBUS);
    transport.insert(Transport::TAXI);

    RouteCost cost = RouteCost(5000, QTime(10, 0, 0), interests, transport);
    std::vector<std::vector<int> > actual = graph.waveAlgorithm(place2, place6, (Cost)cost);
    std::vector<std::vector<int> > expected = std::vector<std::vector<int> >();
    std::vector<int> route = std::vector<int>();
    route.emplace_back(7);
    route.emplace_back(11);
    expected.emplace_back(route);

    QCOMPARE(actual, expected);
}

void Tests::one_suitable_route()
{
    Multigraph::Multigraph<Place> graph = getGraph();

    Place place1 = Place(0, 0, std::string("Эрмитаж"), Interest::SIGHT);
    Place place7 = Place(6, 6, std::string("Медный всадник"), Interest::SIGHT);

    std::set<Interest> interests = std::set<Interest>();
    interests.insert(Interest::CULTURE);

    std::set<Transport> transport = std::set<Transport>();
    transport.insert(Transport::FOOT);
    transport.insert(Transport::UNDERGROUND);

    RouteCost cost = RouteCost(100, QTime(1, 10, 0), interests, transport);
    std::vector<std::vector<int> > actual = graph.waveAlgorithm(place1, place7, (Cost)cost);
    std::vector<std::vector<int> > expected = std::vector<std::vector<int> >();
    std::vector<int> route = std::vector<int>();
    route.emplace_back(0);
    route.emplace_back(8);
    expected.emplace_back(route);
    QCOMPARE(actual, expected);
}

void Tests::no_physical_route()
{
    Multigraph::Multigraph<Place> graph = getGraph();

    Place place1 = Place(0, 0, std::string("Эрмитаж"), Interest::SIGHT);
    Place place7 = Place(6, 6, std::string("Медный всадник"), Interest::SIGHT);

    std::set<Interest> interests = std::set<Interest>();
    interests.insert(Interest::CULTURE);
    interests.insert(Interest::SIGHT);
    interests.insert(Interest::ENTERTAINMENT);
    interests.insert(Interest::PARK);

    std::set<Transport> transport = std::set<Transport>();
    transport.insert(Transport::BUS);
    transport.insert(Transport::FOOT);
    transport.insert(Transport::TRAM);
    transport.insert(Transport::CAR);
    transport.insert(Transport::UNDERGROUND);
    transport.insert(Transport::TROLLEYBUS);
    transport.insert(Transport::TAXI);

    RouteCost cost = RouteCost(5000, QTime(10, 0, 0), interests, transport);
    std::vector<std::vector<int> > actual = graph.waveAlgorithm(place7, place1, (Cost)cost);
    std::vector<std::vector<int> > expected = std::vector<std::vector<int> >();
    QCOMPARE(actual, expected);
}

void Tests::iterator_work()
{
    Place place1 = Place(0, 0, std::string("Эрмитаж"), Interest::SIGHT);
    Place place2 = Place(1, 1, std::string("Кино"), Interest::ENTERTAINMENT);
    Place place3 = Place(2, 2, std::string("Парк Победы"), Interest::PARK);
    Place place4 = Place(3, 3, std::string("Театр"), Interest::CULTURE);
    Place place5 = Place(4, 4, std::string("Казанский собор"), Interest::SIGHT);
    Place place6 = Place(5, 5, std::string("Выставка"), Interest::CULTURE);
    Place place7 = Place(6, 6, std::string("Медный всадник"), Interest::SIGHT);

    Multigraph::Multigraph<Place> graph = getGraph();
    Multigraph::Multigraph<Place>::iterator it = graph.begin();
    Place actual = (*it).first;
    QCOMPARE(actual, place1);
    QCOMPARE((*it).second.getTo(), place4);
    ++it;
    QCOMPARE((*it).first, place1);
    QCOMPARE((*it).second.getTo(), place3);
    ++it;
    QCOMPARE((*it).first, place1);
    QCOMPARE((*it).second.getTo(), place2);
    ++it;
    QCOMPARE((*it).first, place1);
    QCOMPARE((*it).second.getTo(), place2);
    ++it;
    QCOMPARE((*it).first, place2);
    QCOMPARE((*it).second.getTo(), place5);
    ++it;
    QCOMPARE((*it).first, place3);
    QCOMPARE((*it).second.getTo(), place6);
    ++it;
    QCOMPARE((*it).first, place3);
    QCOMPARE((*it).second.getTo(), place4);
    ++it;
    QCOMPARE((*it).first, place4);
    QCOMPARE((*it).second.getTo(), place7);
    ++it;
    QCOMPARE((*it).first, place5);
    QCOMPARE((*it).second.getTo(), place4);
    ++it;
    QCOMPARE((*it).first, place5);
    QCOMPARE((*it).second.getTo(), place7);
    ++it;
    QCOMPARE((*it).first, place5);
    QCOMPARE((*it).second.getTo(), place6);
    ++it;
    QCOMPARE((*it).first, place6);
    QCOMPARE((*it).second.getTo(), place5);
}

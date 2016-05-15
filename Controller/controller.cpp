#include "controller.h"

Controller::Controller()
{
}

std::vector<std::pair<std::string, int> > Controller::getAllPlacesOnMap()
{
    std::vector<std::pair<std::string, int> > result;
    std::vector<Place> places = routeSearcher.getCityMap().getAllPlaces();
    for (std::vector<Place>::iterator it = places.begin(); it != places.end(); ++it)
    {
        result.emplace_back(std::pair<std::string, int>((*it).getName(), (*it).getId()));
    }
    return result;
}

std::vector<std::vector<SearchParameters> > Controller::runRouteSearch(SearchParameters parameters)
{
    std::vector<std::vector<Path> > result = routeSearcher.searchRoutes(parameters.getStart(), parameters.getFinish(),
                               parameters.toRouteCost());

    std::vector<std::vector<SearchParameters> > routes;
    std::vector<std::vector<Path> >::iterator it;
    for (it = result.begin(); it != result.end(); it++)
    {
        std::vector<Path> current = (*it);
        std::vector<SearchParameters> route = std::vector<SearchParameters>();
        for (std::vector<Path>::iterator iter = current.begin(); iter != current.end(); ++iter)
        {
            SearchParameters routeParams;
            routeParams.setStart(iter->getFrom().getId());
            routeParams.setFinish(iter->getTo().getId());
            routeParams.setMoney(parameters.getTravellersNumber()*(iter->getRouteCost().getMoneyCost()));
            routeParams.setTime(iter->getRouteCost().getTimeCost());
            std::set<Interest> interests = iter->getRouteCost().getInterests();
            std::set<Transport> transports = iter->getRouteCost().getTransport();
            for (std::set<Interest>::iterator i = interests.begin(); i != interests.end(); ++i)
            {
                routeParams.addInterest(*i);
            }

            for (std::set<Transport>::iterator i = transports.begin(); i != transports.end(); ++i)
            {
                routeParams.addTransport(*i);
            }
            route.emplace_back(routeParams);
        }
        routes.emplace_back(route);
    }
    return routes;
}

void Controller::save() {
    routeSearcher.save();
}

void Controller::load() {
    routeSearcher.load();
}

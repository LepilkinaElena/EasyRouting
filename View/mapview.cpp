#include "mapview.h"


MapView::MapView(QWidget *parent) : QWebView(parent)
{
    this->page()->mainFrame()->addToJavaScriptWindowObject( QString("Js2CppSuperAPI"), this );
    this->state = MapState::VIEW;
}

void MapView::drawMark(double x, double y, std::string img, int placeId, std::string placeName)
{
    this->page()->mainFrame()->evaluateJavaScript("drawMark("+QString::number(x)+","+QString::number(y)+",\""+QString(img.c_str())+"\","+QString::number(placeId)+",\""+QString(placeName.c_str())+"\")");
}

void MapView::drawLine(double x1, double y1, double x2, double y2, int id)
{
    this->page()->mainFrame()->evaluateJavaScript("drawLine("+QString::number(x1)+","+QString::number(y1)+","+QString::number(x2)+","+QString::number(y2)+","+QString::number(id)+")");
}

void MapView::removeMark(int id)
{
    this->page()->mainFrame()->evaluateJavaScript("removeMark("+QString::number(id)+")");
}

void MapView::removeLine(int id)
{
    this->page()->mainFrame()->evaluateJavaScript("removeLine("+QString::number(id)+")");
}

void MapView::createPlace()
{
    this->page()->mainFrame()->evaluateJavaScript("crosshairCursor()");
    this->state = MapState::PLACE;
}

void MapView::createRoute()
{
    this->page()->mainFrame()->evaluateJavaScript("crosshairCursor()");
    this->state = MapState::ROUTE_BEGIN;

}

void MapView::removeElement()
{
    this->page()->mainFrame()->evaluateJavaScript("crosshairCursor()");
    this->state = MapState::REMOVE;
}

void MapView::onMapLoaded()
{
    this->page()->mainFrame()->evaluateJavaScript("defaultCursor()");
    emit mapReady();
}

void MapView::onMapClicked(double geoCoordX, double geoCoordY)
{
    qDebug()<<"Clicked at coords: "<<geoCoordX<<":"<<geoCoordY;
    if(this->state == MapState::PLACE)
    {
        this->state = MapState::VIEW;
        this->page()->mainFrame()->evaluateJavaScript("defaultCursor()");
        emit placeCreated(geoCoordX,geoCoordY);
    }
}

void MapView::onPlaceClicked(int placeId)
{
    qDebug() << "Clicked on place #"<< placeId;
    if(this->state == MapState::ROUTE_BEGIN)
    {
        this->state = MapState::ROUTE_END;
        beginPlaceId = placeId;
        emit firstPlaceSelected();
    }
    else if(this->state == MapState::ROUTE_END)
    {
        this->state = MapState::VIEW;
        this->page()->mainFrame()->evaluateJavaScript("defaultCursor()");
        emit secondPlaceSelected();
        emit routeCreated(beginPlaceId,placeId);
    }
    else if(this->state == MapState::REMOVE)
    {
        qDebug() << "remove place: " << placeId;
        removeMark(placeId);
        this->page()->mainFrame()->evaluateJavaScript("defaultCursor()");
        this->state = MapState::VIEW;
        CityMap::Instance().removePlaceById(placeId);
        redrawMap(true);
        emit elementRemoved();
    }
}

void MapView::onLineClicked(int lineId)
{
    qDebug() << "Clicked on line #" << lineId;
    if(this->state == MapState::REMOVE)
    {
        qDebug() << "remove route: " << lineId;
        this->page()->mainFrame()->evaluateJavaScript("defaultCursor()");
        this->state = MapState::VIEW;
        removeLine(lineId);
        CityMap::Instance().removeRouteById(lineId);
        redrawMap(true);
        emit elementRemoved();
    }
}

void MapView::loadingFinished()
{
    qDebug("HTML loaded!");
}

MapState MapView::getState() const
{
    return state;
}

bool MapView::hasSinglePlaces()
{
    return !(singlePlaces.empty());
}

Place MapView::getPlaceById(unsigned int id)
{
    std::vector<Place>::iterator it = singlePlaces.begin();
    while(it != singlePlaces.end())
    {
        Place & ref = *it;
        if(ref.getId() == id)
            return ref;
        it++;
    }
    std::vector<Place> multigraphPlaces = CityMap::Instance().getAllPlaces();
    std::vector<Place>::iterator it2 = multigraphPlaces.begin();
    while(it2 != multigraphPlaces.end())
    {
        Place & ref = *it2;
        if(ref.getId() == id)
            return ref;
        it2++;
    }
}

bool MapView::isSinglePlace(unsigned int id)
{
    std::vector<Place>::iterator it = singlePlaces.begin();
    while(it != singlePlaces.end())
    {
        Place & ref = *it;
        if(ref.getId() == id)
            return true;
        it++;
    }
    return false;
}

void MapView::addSinglePlace(Place &ref)
{
    singlePlaces.push_back(ref);
}

void MapView::removeSinglePlace(unsigned int id)
{
    std::vector<Place>::iterator it = singlePlaces.begin();
    while(it != singlePlaces.end())
    {
        Place & ref = *it;
        if(ref.getId() == id) {
            singlePlaces.erase(it);
            break;
        }
        it++;
    }
}

void MapView::redrawMap(bool drawLines)
{
    this->page()->mainFrame()->evaluateJavaScript("clearMap()");
    this->page()->mainFrame()->evaluateJavaScript("clearPath()");
    std::vector<Place> places = CityMap::Instance().getAllPlaces();
    std::vector<Place>::iterator it = places.begin();
    while(it != places.end())
    {
        //qDebug((it.operator *()).getName().c_str());
        double x = it.operator *().getGeoCoordX();
        double y = it.operator *().getGeoCoordY();
        int id = it.operator *().getId();
        std::string str = it.operator *().getName();

        //qDebug() << "x: " << x << " y: " << y;
        drawMark(x,y,"icons/building.png",id,str);
        it++;
    }
    if(drawLines) {
        std::vector<CityMap::routeId> routeIds = CityMap::Instance().getAllRoutes();
        std::vector<CityMap::routeId>::iterator it2 = routeIds.begin();
        while(it2!=routeIds.end())
        {
            int id = it2.operator *().id;
            int idFrom = it2.operator *().from;
            int idTo = it2.operator *().to;
            const Place & from = CityMap::Instance().getPlaceById(idFrom);
            const Place & to = CityMap::Instance().getPlaceById(idTo);
            double x1 = from.getGeoCoordX();
            double y1 = from.getGeoCoordY();
            double x2 = to.getGeoCoordX();
            double y2 = to.getGeoCoordY();
            drawLine(x1,y1,x2,y2,id);
            it2++;
        }
    }
}

void MapView::clearDrawed() {
    this->page()->mainFrame()->evaluateJavaScript("clearPath()");
}

void MapView::drawPath(std::vector<SearchParameters> pathList) {

    this->page()->mainFrame()->evaluateJavaScript("clearPath()");

    for(int i = 0; i < pathList.size(); i++) {
        SearchParameters searchParameters = pathList.at(i);
        int startIndex = searchParameters.getStart();
        int finishIndex = searchParameters.getFinish();

        Place from = CityMap::Instance().getPlaceById(startIndex);
        Place to = CityMap::Instance().getPlaceById(finishIndex);

        double x1 = from.getGeoCoordX();
        double y1 = from.getGeoCoordY();
        double x2 = to.getGeoCoordX();
        double y2 = to.getGeoCoordY();

        qDebug() << "x1=" << x1 << ", y1=" << y1 << ", x2=" << x2 << ", y2=" << y2;

        this->page()->mainFrame()->evaluateJavaScript("drawPathLine("+
                                                      QString::number(x1)+","+
                                                      QString::number(y1)+","+
                                                      QString::number(x2)+","+
                                                      QString::number(y2)+")");
    }
}



void MapView::drawPath(std::vector<Path> &ref)
{
    this->page()->mainFrame()->evaluateJavaScript("clearPath()");
    std::vector<Path>::iterator it = ref.begin();
    while(it != ref.end())
    {
        const Place & from = (*it).getFrom();
        const Place & to = (*it).getTo();
        double x1 = from.getGeoCoordX();
        double y1 = from.getGeoCoordY();
        double x2 = to.getGeoCoordX();
        double y2 = to.getGeoCoordY();
        this->page()->mainFrame()->evaluateJavaScript("drawPathLine("+QString::number(x1)+","+QString::number(y1)+","+QString::number(x2)+","+QString::number(y2)+")");

        it++;
    }
}

void MapView::resetMode()
{
    this->page()->mainFrame()->evaluateJavaScript("defaultCursor()");
    this->state = MapState::VIEW;
}

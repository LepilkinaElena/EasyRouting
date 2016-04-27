#include "mapview.h"


MapView::MapView(QWidget *parent) : QWebView(parent)
{
    Q_ASSERT(connect(this,SIGNAL(loadFinished(bool)),this,SLOT(loadingFinished(bool))));
    this->page()->mainFrame()->addToJavaScriptWindowObject( QString("Js2CppSuperAPI"), this );
    this->state = MapState::VIEW;
}

void MapView::drawMark(double x, double y, std::string img, int placeId, std::string placeName)
{
    this->page()->mainFrame()->evaluateJavaScript("drawMark("+QString::number(x)+","+QString::number(y)+",\""+QString(img.c_str())+"\","+QString::number(placeId)+",\""+QString(placeName.c_str())+"\")");
}

void MapView::drawLine(double x1, double y1, double x2, double y2, Transport type, int id)
{
    this->page()->mainFrame()->evaluateJavaScript("drawLine("+QString::number(x1)+","+QString::number(y1)+","+QString::number(x2)+","+QString::number(y2)+","+"\"FOOT\""+","+QString::number(id)+")");
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

void MapView::onMapClicked(double geoCoordX, double geoCoordY)
{
    qDebug()<<"User clicked at: "<<geoCoordX<<":"<<geoCoordY;
    if(this->state == MapState::PLACE)
    {
        //drawMark(geoCoordX,geoCoordY,"icons/building.png",rand()%100);
        this->state = MapState::VIEW;
        this->page()->mainFrame()->evaluateJavaScript("defaultCursor()");
        emit placeCreated(geoCoordX,geoCoordY);
    }
}

void MapView::onPlaceClicked(int placeId)
{
    qDebug() << "Place id: "<< placeId;
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
}

void MapView::onLineClicked(int lineId)
{
    qDebug() << "Clicked on line #" << lineId;
}

void MapView::loadingFinished(bool status)
{
    qDebug("Map loaded!");
    this->page()->mainFrame()->evaluateJavaScript("defaultCursor()");
}


MapState MapView::getState() const
{
    return state;
}

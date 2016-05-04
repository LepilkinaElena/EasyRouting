#ifndef MAPVIEW_H
#define MAPVIEW_H

#include <QWidget>
#include <QDebug>
#include <QWebElement>
#include <QtWebKit>
#include <QtWebKitWidgets>
#include <QtWebKitWidgets/QWebFrame>

#include "ERModel/routecost.h"

enum MapState { VIEW, PLACE, ROUTE_BEGIN, ROUTE_END, REMOVE };

/*!\class MapView
*\brief Класс виджета карты
*\ref MapView
*/
class MapView : public QWebView
{
    Q_OBJECT
public:
    explicit MapView(QWidget *parent = 0);
    void drawMark(double x, double y, std::string img, int placeId, std::string placeName);
    void drawLine(double x1, double y1, double x2, double y2, Transport type, int id);
    void removeMark(int id);
    void removeLine(int id);
    MapState getState() const;

signals:
    void placeCreated(double x, double y);
    void routeCreated(int begin, int end);
    void removePlace(int placeId);
    void removeRoute(int routeId);
    void firstPlaceSelected();
    void secondPlaceSelected();
public slots:
    void createPlace();
    void createRoute();
    void removeElement();
    void onMapClicked(double geoCoordX, double geoCoordY);
    void onPlaceClicked(int placeId);
    void onLineClicked(int lineId);
    void loadingFinished(bool status);
private:

    int beginPlaceId;
    MapState state;
};

#endif // MAPVIEW_H

#ifndef MAPVIEW_H
#define MAPVIEW_H

#include <QWidget>
#include <QDebug>
#include <QWebElement>
#include <QtWebKit>
#include <QtWebKitWidgets>
#include <QtWebKitWidgets/QWebFrame>

enum MapState { VIEW, PLACE, ROUTE_BEGIN, ROUTE_END };

/*!\class MapView
*\brief Класс виджета карты
*\ref MapView
*/
class MapView : public QWebView
{
    Q_OBJECT
public:
    explicit MapView(QWidget *parent = 0);
    void drawMark(double x, double y, QString img, int placeId);
    void drawLine(double x1, double y1, double x2, double y2);
    MapState getState() const;

signals:
    void placeCreated(double x, double y);
    void routeCreated(int begin, int end);
public slots:
    void createPlace();
    void createRoute();
    void onMapClicked(double geoCoordX, double geoCoordY);
    void onPlaceClicked(int placeId);
    void loadingFinished(bool status);
private:

    int beginPlaceId;
    MapState state;
};

#endif // MAPVIEW_H

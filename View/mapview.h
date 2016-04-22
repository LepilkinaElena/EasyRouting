#ifndef MAPVIEW_H
#define MAPVIEW_H

#include <QWidget>
#include <QDebug>
#include <QWebElement>
#include <QtWebKit>
#include <QtWebKitWidgets>
#include <QtWebKitWidgets/QWebFrame>


/*!\class MapView
*\brief Класс виджета карты
*\ref MapView
*/
class MapView : public QWebView
{
    Q_OBJECT
public:
    explicit MapView(QWidget *parent = 0);
    void drawMark(double x, double y, QString img);
    void drawLine(double x1, double y1, double x2, double y2);
signals:

public slots:
    void onMapClicked(double geoCoordX, double geoCoordY);
    void loadingFinished(bool status);
};

#endif // MAPVIEW_H

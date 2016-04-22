#include "mapview.h"


MapView::MapView(QWidget *parent) : QWebView(parent)
{
    Q_ASSERT(connect(this,SIGNAL(loadFinished(bool)),this,SLOT(loadingFinished(bool))));
    this->page()->mainFrame()->addToJavaScriptWindowObject( QString("Js2CppSuperAPI"), this );
}

void MapView::drawMark(double x, double y, QString img)
{
    this->page()->mainFrame()->evaluateJavaScript("drawMark("+QString::number(x)+","+QString::number(y)+",\""+img+"\")");
}

void MapView::drawLine(double x1, double y1, double x2, double y2)
{
    this->page()->mainFrame()->evaluateJavaScript("drawLine("+QString::number(x1)+","+QString::number(y1)+","+QString::number(x2)+","+QString::number(y2)+")");
}

void MapView::onMapClicked(double geoCoordX, double geoCoordY)
{
    qDebug()<<"User clicked at: "<<geoCoordX<<":"<<geoCoordY;
    drawMark(geoCoordX,geoCoordY,"1.png");
}

void MapView::loadingFinished(bool status)
{
    qDebug("Map loaded!");
}

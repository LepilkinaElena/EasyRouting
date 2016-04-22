#include "mapview.h"


MapView::MapView(QWidget *parent) : QWebView(parent)
{
    Q_ASSERT(connect(this,SIGNAL(loadFinished(bool)),this,SLOT(loadingFinished(bool))));
    Q_ASSERT(connect(this,SIGNAL(done(QString)),this,SLOT(recieved(QString))));

    this->page()->mainFrame()->addToJavaScriptWindowObject( QString("Js2CppSuperAPI"), this );
}

void MapView::recieved(QString message)
{
    qDebug()<<"Recieved from js: "<<message<<endl;
}

void MapView::loadingFinished(bool status)
{
    qDebug("LOADED!");
}

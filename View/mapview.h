#ifndef MAPVIEW_H
#define MAPVIEW_H

#include <QWidget>
#include <QDebug>
#include <QWebElement>
#include <QtWebKit>
#include <QtWebKitWidgets>
#include <QtWebKitWidgets/QWebFrame>



class MapView : public QWebView
{
    Q_OBJECT
public:
    explicit MapView(QWidget *parent = 0);


signals:
    void done(QString message);
public slots:
    void recieved(QString message);
    void loadingFinished(bool status);
};

#endif // MAPVIEW_H

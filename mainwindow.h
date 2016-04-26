#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "View/selectionitem.h"
#include "View/placedialog.h"
#include "View/routedialog.h"
#include <ERModel/place.h>
#include <ERModel/citymap.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_createPlaceButton_clicked();
    void onPlaceCreated(double x, double y);
    void onRouteCreated(int begin, int end);

    void on_createRouteButton_clicked();

private:
    void setupUI();

    PlaceDialog placeDialog;
    RouteDialog routeDialog;

    QStandardItemModel interestsModel;
    QStandardItemModel transportModel;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
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

    void onPlaceDataEntered();
    void onRouteDataEntered();
    void onFirstPlaceSelected();
    void onSecondPlaceSelected();

    void on_removeButton_clicked();
    void editMode();

private:
    void setupUI();
    bool editModeOn;
    QLabel statusLabel;

    PlaceDialog placeDialog;
    RouteDialog routeDialog;

    QStandardItemModel interestsModel;
    QStandardItemModel transportModel;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

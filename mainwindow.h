#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QMainWindow>
#include <QComboBox>
#include <QTableWidget>

#include "View/selectionitem.h"
#include "View/placedialog.h"
#include "View/routedialog.h"
#include "View/savedialog.h"
#include <ERModel/place.h>
#include <ERModel/citymap.h>
#include "Controller/controller.h"
#include "Controller/searchparameters.h"

namespace Ui {
class MainWindow;
}

struct RoutesTableItemModel {
    QString start;
    QString end;
    int cost;
    QTime time;
    std::vector<SearchParameters> pathVector;
};

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
    void runRouteSearching();
    void initMap();
    void cancelCreatingPlace();
    void cancelCreatingRoute();

    void onElementRemoved();
    void save();
    void cancel();

    void drawPath();

    void on_sortTypeComboBox_currentIndexChanged(int index);

    void on_clearButton_clicked();

private:
    void setupUI();

    void fillRoutesList(std::vector<std::vector<SearchParameters> > foundedRoutes);
    void fillRoutesTableWidget(std::vector<RoutesTableItemModel> routesItemList, QTableWidget* routesTableWidget, int index);
    void fillPlaces(QComboBox* box);
    void activateButton(QAbstractButton* button);
    void deactivateButton(QAbstractButton* button);
    bool editModeOn;
    bool placeCreatedModeOn;
    bool routeCreatedModeOn;
    bool removeModeOn;
    void endEditing();
    Controller controller;
    QLabel statusLabel;

    PlaceDialog placeDialog;
    RouteDialog routeDialog;
    SaveDialog saveDialog;

    QStandardItemModel interestsModel;
    QStandardItemModel transportModel;
    Ui::MainWindow *ui;

    // список найденных маршрутов
    std::vector<RoutesTableItemModel> tableRoutesList;
};

#endif // MAINWINDOW_H

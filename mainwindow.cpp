#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Api-key:  AIzaSyBZlzCLJx325LcgMVz363Byy4AmHshs6us
    QUrl url("qrc:///map/google_map.html");
    ui->mapWidget->load(url);

    setupUI();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupUI()
{
    ui->interestsListView->setModel( &interestsModel );
    //enum Interest { SIGHT, CULTURE, PARK, ENTERTAINMENT };
    interestsModel.appendRow(new SelectionItem("Достопримечательности"));
    interestsModel.appendRow(new SelectionItem("Культура"));
    interestsModel.appendRow(new SelectionItem("Парки"));
    interestsModel.appendRow(new SelectionItem("Развлечения"));

    ui->transportListView->setModel( &transportModel );
    //enum Transport {CAR, UNDERGROUND, BUS, TROLLEYBUS, TRAM, TAXI, FOOT};
    transportModel.appendRow(new SelectionItem("Автомобиль"));
    transportModel.appendRow(new SelectionItem("Метро"));
    transportModel.appendRow(new SelectionItem("Автобус"));
    transportModel.appendRow(new SelectionItem("Троллейбус"));
    transportModel.appendRow(new SelectionItem("Трамвай"));
    transportModel.appendRow(new SelectionItem("Такси"));
    transportModel.appendRow(new SelectionItem("Пешком"));
}

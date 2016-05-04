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
    ui->statusBar->addWidget(&statusLabel);

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
    transportModel.appendRow(new SelectionItem("Маршрутка"));
    transportModel.appendRow(new SelectionItem("Пешком"));

    Q_ASSERT(connect(&placeDialog,SIGNAL(accepted()),ui->mapWidget,SLOT(createPlace())));
    Q_ASSERT(connect(&placeDialog,SIGNAL(accepted()),this,SLOT(onPlaceDataEntered())));
    Q_ASSERT(connect(&routeDialog,SIGNAL(accepted()),ui->mapWidget,SLOT(createRoute())));
    Q_ASSERT(connect(&routeDialog,SIGNAL(accepted()),this,SLOT(onRouteDataEntered())));
    Q_ASSERT(connect(ui->mapWidget,SIGNAL(placeCreated(double,double)),this,SLOT(onPlaceCreated(double,double))));
    Q_ASSERT(connect(ui->mapWidget,SIGNAL(routeCreated(int,int)),this,SLOT(onRouteCreated(int,int))));
    Q_ASSERT(connect(ui->mapWidget,SIGNAL(firstPlaceSelected()),this,SLOT(onFirstPlaceSelected())));
    Q_ASSERT(connect(ui->mapWidget,SIGNAL(secondPlaceSelected()),this,SLOT(onSecondPlaceSelected())));
}

void MainWindow::on_createPlaceButton_clicked()
{
    placeDialog.show();
}

void MainWindow::onPlaceCreated(double x, double y)
{
    Place pPlace(x,y,placeDialog.getPlaceName().toStdString(),placeDialog.getInterest());
    CityMap::Instance()->getSinglePlaces().push_back(pPlace);

    ui->mapWidget->drawMark(x,y,"icons/building.png",pPlace.getId(),pPlace.getName());
    statusLabel.setText("");
}

void MainWindow::onRouteCreated(int begin, int end)
{
    double x1 = 0.0, y1 = 0.0, x2 = 0.0, y2 = 0.0;

    Place & p1 = CityMap::Instance()->getPlaceById(begin);
    x1 = p1.getGeoCoordX();
    y1 = p1.getGeoCoordY();
    Place & p2 = CityMap::Instance()->getPlaceById(end);
    x2 = p2.getGeoCoordX();
    y2 = p2.getGeoCoordY();

    Interest inter = p2.getIntersestCategory();
    std::set<Interest> interests;
    interests.insert(inter);

    std::set<Transport> transports;
    transports.insert(routeDialog.getTransport());
    RouteCost* cost = new RouteCost(routeDialog.getCost(), routeDialog.getTime(), interests, transports);

    int edgeIndex = CityMap::Instance()->getGraph().addEdge(p1,p2,cost);
    ui->mapWidget->drawLine(x1,y1,x2,y2, routeDialog.getTransport(), edgeIndex);
}

void MainWindow::on_createRouteButton_clicked()
{
    routeDialog.show();
}

void MainWindow::onPlaceDataEntered()
{
    statusLabel.setText("Укажите место на карте");
}

void MainWindow::onRouteDataEntered()
{
    statusLabel.setText("Выберите первое место");
}

void MainWindow::onFirstPlaceSelected()
{
    statusLabel.setText("Выберите второе место");
}

void MainWindow::onSecondPlaceSelected()
{
    statusLabel.setText("");
}

void MainWindow::on_removeButton_clicked()
{
    ui->mapWidget->removeElement();
}

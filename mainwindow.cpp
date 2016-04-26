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

    Q_ASSERT(connect(&placeDialog,SIGNAL(accepted()),ui->mapWidget,SLOT(createPlace())));
    Q_ASSERT(connect(&routeDialog,SIGNAL(accepted()),ui->mapWidget,SLOT(createRoute())));
    Q_ASSERT(connect(ui->mapWidget,SIGNAL(placeCreated(double,double)),this,SLOT(onPlaceCreated(double,double))));
    Q_ASSERT(connect(ui->mapWidget,SIGNAL(routeCreated(int,int)),this,SLOT(onRouteCreated(int,int))));
}

void MainWindow::on_createPlaceButton_clicked()
{
    placeDialog.show();
}

void MainWindow::onPlaceCreated(double x, double y)
{
    Place * pPlace = new Place(x,y,placeDialog.getPlaceName().toStdString(),placeDialog.getInterest());
    CityMap::Instance()->getSinglePlaces().push_back(pPlace);

    ui->mapWidget->drawMark(x,y,"icons/building.png",pPlace->getId());
}

void MainWindow::onRouteCreated(int begin, int end)
{
    double x1 = 0.0, y1 = 0.0, x2 = 0.0, y2 = 0.0;
    Place * p1,p2;
    std::vector<Place*>::iterator it = CityMap::Instance()->getSinglePlaces().begin();
    while(it != CityMap::Instance()->getSinglePlaces().end())
    {
        Place * pPlace = it.operator *();
        if((pPlace->getId() == begin))
        {
            x1 = pPlace->getGeoCoordX();
            y1 = pPlace->getGeoCoordY();
            p1 = pPlace;
        }
        if((pPlace->getId() == end))
        {
            x2 = pPlace->getGeoCoordX();
            y2 = pPlace->getGeoCoordY();
            p2 = pPlace;
        }
        it++;
    }
    ui->mapWidget->drawLine(x1,y1,x2,y2);
    //TODO: добавление элементов в граф
    //CityMap::Instance()->getGraph().addEdge(p1,p2,new Cost());

}

void MainWindow::on_createRouteButton_clicked()
{
    routeDialog.show();
}

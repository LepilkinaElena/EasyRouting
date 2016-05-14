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
    editModeOn = false;
    placeCreatedModeOn = false;
    routeCreatedModeOn = false;
    removeModeOn = false;
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

    ui->createPlaceButton->setEnabled(false);
    ui->createRouteButton->setEnabled(false);
    ui->removeButton->setEnabled(false);

    fillPlaces(ui->startList);
    fillPlaces(ui->finishList);

    connect(&placeDialog,SIGNAL(accepted()),ui->mapWidget,SLOT(createPlace()));
    connect(&placeDialog,SIGNAL(rejected()), this, SLOT(cancelCreatingPlace()));
    connect(&placeDialog,SIGNAL(accepted()),this,SLOT(onPlaceDataEntered()));
    connect(&routeDialog,SIGNAL(accepted()),ui->mapWidget,SLOT(createRoute()));
    connect(&routeDialog,SIGNAL(rejected()), this, SLOT(cancelCreatingRoute()));
    connect(&routeDialog,SIGNAL(accepted()),this,SLOT(onRouteDataEntered()));
    connect(ui->mapWidget,SIGNAL(placeCreated(double,double)),this,SLOT(onPlaceCreated(double,double)));
    connect(ui->mapWidget,SIGNAL(routeCreated(int,int)),this,SLOT(onRouteCreated(int,int)));
    connect(ui->mapWidget,SIGNAL(firstPlaceSelected()),this,SLOT(onFirstPlaceSelected()));
    connect(ui->mapWidget,SIGNAL(secondPlaceSelected()),this,SLOT(onSecondPlaceSelected()));
    connect(ui->mapWidget, SIGNAL(mapReady()), this, SLOT(initMap()));
    connect(ui->mapWidget, SIGNAL(elementRemoved()), this, SLOT(onElementRemoved()));
    connect(ui->editMapButton, SIGNAL(clicked()), this, SLOT(editMode()));
    connect(ui->searchRoutesButton, SIGNAL(clicked()), this, SLOT(runRouteSearching()));

}

void MainWindow::initMap()
{
    qDebug("Map ready!");
    ui->mapWidget->redrawMap(false);

}

void MainWindow::runRouteSearching()
{
    // Собрать всю информацию
    SearchParameters parameters;
    parameters.setStart(ui->startList->currentData().toInt());
    parameters.setFinish(ui->finishList->currentData().toInt());
    parameters.setTravellersNumber(ui->peopleCount->value());
    parameters.setTime(ui->timeEdit->time());
    if (ui->timeEdit->time() == QTime(0,0))
    {
        QMessageBox::warning(this,"Ошибка в вводе праметров", "Не задано время! Ничего найдено не будет!");
    }
    parameters.setMoney(ui->moneyCount->value());
    int count = 0;
    for (int i = 0; i <= ENTERTAINMENT; i++)
    {
        if (interestsModel.item(i)->checkState())
        {
            parameters.addInterest((Interest)i);
            count++;
        }
    }

    if (count == 0)
    {
        QMessageBox::warning(this,"Ошибка в вводе праметров", "Не выбрана ни одна категория интересов!");
    }

    count = 0;
    for (int i = 0; i <= FOOT; i++)
    {
        if (transportModel.item(i)->checkState())
        {
            parameters.addTransport((Transport)i);
            count++;
        }
    }

    if (count == 0)
    {
        QMessageBox::warning(this,"Ошибка в вводе праметров", "Не выбран ни один вид транспорта!");
    }
    std::vector<std::vector<SearchParameters> > routes = controller.runRouteSearch(parameters);
}

void MainWindow::fillPlaces(QComboBox *box)
{
    box->clear();
    // Получить все места на карте
    std::vector<std::pair<std::string, int> > places = controller.getAllPlacesOnMap();
    std::vector<std::pair<std::string, int> >::iterator it;
    for (it = places.begin(); it != places.end(); ++it)
    {
        box->addItem(QString((*it).first.c_str()), QVariant((*it).second));
    }
}


void MainWindow::editMode()
{
    editModeOn = !editModeOn;
    if (editModeOn)
    {
        ui->mapWidget->redrawMap(true);
        ui->editMapButton->setStyleSheet(" background-color: lightgreen; ");
    }
    else
    {
        ui->mapWidget->redrawMap(false);
        fillPlaces(ui->startList);
        fillPlaces(ui->finishList);
        placeDialog.close();
        routeDialog.close();
        deactivateButton(ui->removeButton);
        deactivateButton(ui->createPlaceButton);
        deactivateButton(ui->createRouteButton);

        routeCreatedModeOn = false;
        placeCreatedModeOn = false;
        removeModeOn = false;
        ui->editMapButton->setStyleSheet(" background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #f6f7fa, stop: 1 #dadbde); ");
    }
    ui->createPlaceButton->setEnabled(editModeOn);
    ui->createRouteButton->setEnabled(editModeOn);
    ui->removeButton->setEnabled(editModeOn);
}

void MainWindow::activateButton(QAbstractButton *button)
{
    button->setStyleSheet(" background-color: lightgreen; ");
}

void MainWindow::deactivateButton(QAbstractButton *button)
{
    button->setStyleSheet(" background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #f6f7fa, stop: 1 #dadbde); ");
}

void MainWindow::on_createPlaceButton_clicked()
{
    if (!placeCreatedModeOn)
    {
        routeDialog.close();
        placeDialog.show();
        deactivateButton(ui->createRouteButton);
        deactivateButton(ui->removeButton);
        activateButton(ui->createPlaceButton);
        placeCreatedModeOn = true;
        routeCreatedModeOn = false;
        removeModeOn = false;

    }
    else
    {
        deactivateButton(ui->createPlaceButton);
        placeCreatedModeOn = false;
        placeDialog.close();
        ui->mapWidget->resetMode();
    }
}

void MainWindow::cancelCreatingPlace()
{
    deactivateButton(ui->createPlaceButton);
    placeDialog.clear();
    placeCreatedModeOn = false;
    ui->mapWidget->resetMode();
}

void MainWindow::cancelCreatingRoute()
{
    deactivateButton(ui->createRouteButton);
    routeCreatedModeOn = false;
    ui->mapWidget->resetMode();
}

void MainWindow::onElementRemoved()
{
    deactivateButton(ui->removeButton);
    removeModeOn = false;
    ui->mapWidget->resetMode();
}

void MainWindow::onPlaceCreated(double x, double y)
{
    Place pPlace(x,y,placeDialog.getPlaceName().toStdString(),placeDialog.getInterest());
    cancelCreatingPlace();
    //CityMap::Instance().getSinglePlaces().push_back(pPlace);

    ui->mapWidget->addSinglePlace(pPlace);
    ui->mapWidget->drawMark(x,y,"icons/building.png",pPlace.getId(),pPlace.getName());
    statusLabel.setText("");
}

void MainWindow::onRouteCreated(int begin, int end)
{
    double x1 = 0.0, y1 = 0.0, x2 = 0.0, y2 = 0.0;

    const Place & p1 = ui->mapWidget->getPlaceById(begin);
    x1 = p1.getGeoCoordX();
    y1 = p1.getGeoCoordY();
    const Place & p2 = ui->mapWidget->getPlaceById(end);
    x2 = p2.getGeoCoordX();
    y2 = p2.getGeoCoordY();
    Interest inter = p2.getIntersestCategory();
    cancelCreatingRoute();
    std::set<Interest> interests;
    interests.insert(inter);

    std::set<Transport> transports;
    transports.insert(routeDialog.getTransport());
    RouteCost* cost = new RouteCost(routeDialog.getCost(), routeDialog.getTime(), interests, transports);
    int edgeIndex = CityMap::Instance().addRoute(p1,p2,cost);

    ui->mapWidget->drawLine(x1,y1,x2,y2, edgeIndex);

    if(ui->mapWidget->isSinglePlace(begin))
        ui->mapWidget->removeSinglePlace(begin);
    if(ui->mapWidget->isSinglePlace(end))
        ui->mapWidget->removeSinglePlace(end);
}

void MainWindow::on_createRouteButton_clicked()
{
    if (!routeCreatedModeOn)
    {
        routeDialog.show();
        placeDialog.close();
        placeDialog.clear();
        deactivateButton(ui->createPlaceButton);
        deactivateButton(ui->removeButton);
        activateButton(ui->createRouteButton);
        routeCreatedModeOn = true;
        placeCreatedModeOn = false;
        removeModeOn = false;

    }
    else
    {
        deactivateButton(ui->createRouteButton);
        routeCreatedModeOn = false;
        routeDialog.close();
        ui->mapWidget->resetMode();
    }
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
    if (!removeModeOn)
    {
        routeDialog.close();
        placeDialog.close();
        placeDialog.clear();
        ui->mapWidget->removeElement();
        deactivateButton(ui->createRouteButton);
        deactivateButton(ui->createPlaceButton);
        activateButton(ui->removeButton);
        placeCreatedModeOn = false;
        routeCreatedModeOn = false;
        removeModeOn = true;
    }
    else
    {
        deactivateButton(ui->removeButton);
        removeModeOn = false;
    }
}

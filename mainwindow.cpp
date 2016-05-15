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

    ui->sortTypeComboBox->addItem("По времени");
    ui->sortTypeComboBox->addItem("По стоимости");

    ui->createPlaceButton->setEnabled(false);
    ui->createRouteButton->setEnabled(false);
    ui->removeButton->setEnabled(false);

    ui->routesTableWidget->setColumnCount(5);

    QStringList horizontalLabels;
    horizontalLabels.append("Начало");
    horizontalLabels.append("Конец");
    horizontalLabels.append("Стоимость");
    horizontalLabels.append("Время");
    horizontalLabels.append("Действия");
    ui->routesTableWidget->setHorizontalHeaderLabels(horizontalLabels);

    fillPlaces(ui->startList);
    fillPlaces(ui->finishList);

    connect(&placeDialog,SIGNAL(accepted()),ui->mapWidget,SLOT(createPlace()));
    connect(&placeDialog,SIGNAL(rejected()), this, SLOT(cancelCreatingPlace()));
    connect(&placeDialog,SIGNAL(accepted()),this,SLOT(onPlaceDataEntered()));
    connect(&routeDialog,SIGNAL(accepted()),ui->mapWidget,SLOT(createRoute()));
    connect(&routeDialog,SIGNAL(rejected()), this, SLOT(cancelCreatingRoute()));
    connect(&routeDialog,SIGNAL(accepted()),this,SLOT(onRouteDataEntered()));
    connect(&saveDialog,SIGNAL(accepted()),this,SLOT(save()));
    connect(&saveDialog,SIGNAL(rejected()),this,SLOT(cancel()));
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
    fillRoutesList(routes);
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

void MainWindow::save()
{
    endEditing();
    // Todo serialize
    controller.save();
}

void MainWindow::cancel()
{
    //TODO read old file
    endEditing();
}

void MainWindow::endEditing()
{
    editModeOn = !editModeOn;
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
    ui->mapWidget->resetMode();
    ui->createPlaceButton->setEnabled(editModeOn);
    ui->createRouteButton->setEnabled(editModeOn);
    ui->removeButton->setEnabled(editModeOn);
    ui->searchRoutesButton->setEnabled(!editModeOn);

}

void MainWindow::editMode()
{
    if (!editModeOn)
    {
        ui->mapWidget->redrawMap(true);
        ui->editMapButton->setStyleSheet(" background-color: lightgreen; ");
        editModeOn = !editModeOn;
        ui->createPlaceButton->setEnabled(editModeOn);
        ui->createRouteButton->setEnabled(editModeOn);
        ui->removeButton->setEnabled(editModeOn);
        ui->searchRoutesButton->setEnabled(!editModeOn);
    }
    else
    {
        if (ui->mapWidget->hasSinglePlaces())
        {
            QMessageBox::warning(this,"Ошибка при редактировании", "На карте есть места, не соединенные с другими! Данные места сохранены не будут");
        }
        saveDialog.show();
    }
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

std::string getPlaceName(int index) {
    return CityMap::Instance().getPlaceById(index).getName();
}

std::vector<std::vector<SearchParameters>> getSortedByTime(std::vector<std::vector<SearchParameters>> tableList) {
    struct CostSortFunc {
        bool operator()(std::vector<SearchParameters> item1, std::vector<SearchParameters> item2) {
            return MainWindow::defineDuration(item1) < MainWindow::defineDuration(item2);
        }
        QTime defineTime(std::vector<SearchParameters> pathVector) {
            int minutes = 0;
            int hours = 0;
            for(int i = 0; i < pathVector.size();i++) {
                QTime time = pathVector.at(i).getTime();
                hours += time.hour();
                minutes += time.minute();
            }
            while(minutes >= 60) {
                hours++;
                minutes -= 60;
            }
            return QTime(hours, minutes);
        }
    } sortObject;

    std::sort(tableList.begin(), tableList.end(), sortObject);
    return tableList;
}

std::vector<RoutesTableItemModel> getSortedByTime(std::vector<RoutesTableItemModel> tableList) {
    struct CostSortFunc {
        bool operator()(RoutesTableItemModel item1, RoutesTableItemModel item2) {
            if(item1.time.hour() < item2.time.hour()) {
                return true;
            } else {
                if(item1.time.hour() == item2.time.hour()) {
                    return item1.time.minute() < item2.time.minute();
                } else {
                    return false;
                }
            }

        }
    } sortObject;

    std::sort(tableList.begin(), tableList.end(), sortObject);
    return tableList;
}

std::vector<std::vector<SearchParameters>> getSortedByMoney(std::vector<std::vector<SearchParameters>> tableList) {
    struct CostSortFunc {
        bool operator()(std::vector<SearchParameters> item1, std::vector<SearchParameters> item2) {
            return MainWindow::defineCost(item1) < MainWindow::defineCost(item2);
        }
    } sortObject;

    std::sort(tableList.begin(), tableList.end(), sortObject);
    qDebug() << "123";
    return tableList;
}

std::vector<RoutesTableItemModel> getSortedByMoney(std::vector<RoutesTableItemModel> tableList) {
    struct CostSortFunc {
        bool operator()(RoutesTableItemModel item1, RoutesTableItemModel item2) {
            return item1.cost < item2.cost;
        }
    } sortObject;

    std::sort(tableList.begin(), tableList.end(), sortObject);
    qDebug() << "123";
    return tableList;
}

int MainWindow::defineCost(std::vector<SearchParameters> pathVector) {
    int cost = 0;
    for(int i = 0; i < pathVector.size(); i++) {
        cost += pathVector.at(i).getMoney();
    }
    return cost;
}

QTime MainWindow::defineDuration(std::vector<SearchParameters> pathVector) {
    int minutes = 0;
    int hours = 0;
    for(int i = 0; i < pathVector.size();i++) {
        QTime time = pathVector.at(i).getTime();
        hours += time.hour();
        minutes += time.minute();
    }
    while(minutes >= 60) {
        hours++;
        minutes -= 60;
    }
    return QTime(hours, minutes);
}

void MainWindow::drawPath() {
    QPushButton* b = qobject_cast<QPushButton *>(sender());

    int index = b->property("index").toInt();

    qDebug() << "DRAW PATH!!!" << index;

    ui->mapWidget->drawPath(vvPaths.at(index));
}

void MainWindow::showFullInfo() {
    QPushButton* b = qobject_cast<QPushButton *>(sender());
    int index = b->property("index").toInt();

    std::vector<SearchParameters> path = vvPaths.at(index);

    QString startName = QString::fromStdString(CityMap::Instance().getPlaceById(path.at(0).getStart()).getName());
    QString finishName = QString::fromStdString(CityMap::Instance().getPlaceById(path.at(path.size() - 1).getFinish()).getName());

    QString cost = QString::number(MainWindow::defineCost(path));
    QString duration = MainWindow::defineDuration(path).toString();

    std::vector<QString> stopsList;
    for(int i = 0; i < path.size(); i++) {
        SearchParameters sp = path.at(i);
        QString stopName = QString::fromStdString(CityMap::Instance().getPlaceById(sp.getStart()).getName());
        stopsList.push_back(stopName);
    }
//    for(int i = 0; i < routesTableItem.pathVector.size(); i++) {
//        SearchParameters searchParams = routesTableItem.pathVector.at(i);
//        std::string str = CityMap::Instance().getPlaceById(searchParams.getStart()).getName();
//        stopsList.push_back(QString::fromStdString(str));
//    }
    stopsList.push_back(finishName);

    QString stopsStr;
    for(int i = 0; i < stopsList.size();i++) {
        stopsStr += QString::number(i+1);
        stopsStr += ") ";
        stopsStr += stopsList.at(i);
        stopsStr += "\n";
    }

    QMessageBox::information(this, "Информация о маршруте",
                             QString("\nИз: ") + startName +
                             QString("\nВ: ") + finishName +
                             QString("\nСтоимость: ") + cost +
                             QString("\nВремя: ") + duration +
                             QString("\nОстановки: \n") +
                             stopsStr);

}

QTime getTime(std::vector<SearchParameters> params) {
    int minutes = 0;
    int hours = 0;
    for(int i = 0; i < params.size(); i++) {
        QTime qTime = params.at(i).getTime();
        minutes += qTime.minute();
        hours += qTime.hour();
    }
    while(minutes >= 60) {
        minutes-=60;
        hours++;
    }
    return QTime(hours, minutes);
}

int getCost(std::vector<SearchParameters> params) {
    int money = 0;
    for(int i = 0; i < params.size(); i++) {
        money += params.at(i).getMoney();
    }
    return money;
}

void MainWindow::fillRoutesTableWidget(QTableWidget* routesTableWidget, int index) {
    qDebug() << "CALL 1";
    routesTableWidget->clearContents();
    routesTableWidget->setRowCount(0);

    if(index == 0) {
        // сортировка по времени
        vvPaths = getSortedByTime(vvPaths);
//        routesItemList = getSortedByTime(routesItemList);
    } else {
        // сортировка по стоимости
        vvPaths = getSortedByMoney(vvPaths);
//        routesItemList = getSortedByMoney(routesItemList);
    }

    routesTableWidget->setRowCount(vvPaths.size());

    qDebug() << "vvPaths.size: " << vvPaths.size();
    for(int i = 0; i < vvPaths.size(); i++) {
        std::vector<SearchParameters> path = vvPaths.at(i);

        int start = path.at(0).getStart();
        QString startStr = QString::fromStdString(CityMap::Instance().getPlaceById(start).getName());

        int finish = path.at(path.size() - 1).getFinish();
        QString finishStr = QString::fromStdString(CityMap::Instance().getPlaceById(finish).getName());

        int cost = getCost(path);
        QString costStr = QString::number(cost);

        QTime time = getTime(path);

        routesTableWidget->setItem(i, 0, new QTableWidgetItem(startStr));
        routesTableWidget->setItem(i, 1, new QTableWidgetItem(finishStr));
        routesTableWidget->setItem(i, 2, new QTableWidgetItem(costStr));
        routesTableWidget->setItem(i, 3, new QTableWidgetItem(time.toString()));

        QHBoxLayout* layout = new QHBoxLayout();
        layout->setMargin(0);

        QPushButton* btn1 = new QPushButton("На карте");
        QPushButton* btn2 = new QPushButton("Подробно");

        layout->setSizeConstraint(QLayout::SetMaximumSize);

        btn1->setProperty("index", QVariant(i));
        btn2->setProperty("index", QVariant(i));

        layout->setSpacing(0);

        layout->addWidget(btn1);
        layout->addWidget(btn2);

        connect(btn1, SIGNAL(clicked()), this, SLOT(drawPath()));
        connect(btn2, SIGNAL(clicked()), this, SLOT(showFullInfo()));

        QWidget* widget = new QWidget();
        widget->setLayout(layout);

        routesTableWidget->setCellWidget(i, 4, widget);
    }
}

void MainWindow::fillRoutesTableWidget(std::vector<RoutesTableItemModel> routesItemList, QTableWidget* routesTableWidget, int index) {
    routesTableWidget->clearContents();
    routesTableWidget->setRowCount(0);

    if(index == 0) {
        // сортировка по времени
        routesItemList = getSortedByTime(routesItemList);
    } else {
        // сортировка по стоимости
        routesItemList = getSortedByMoney(routesItemList);
    }
    qDebug() << "fillRoutesTableWidget, size=" << routesItemList.size();
    routesTableWidget->setRowCount(routesItemList.size());

    for(int i = 0; i < routesItemList.size(); i++ ) {
        RoutesTableItemModel item = routesItemList.at(i);
        routesTableWidget->setItem(i, 0, new QTableWidgetItem(item.start));
        routesTableWidget->setItem(i, 1, new QTableWidgetItem(item.end));
        routesTableWidget->setItem(i, 2, new QTableWidgetItem(QString::number(item.cost)));
        routesTableWidget->setItem(i, 3, new QTableWidgetItem(item.time.toString()));

        QHBoxLayout* layout = new QHBoxLayout();
        layout->setMargin(0);

        QPushButton* btn1 = new QPushButton("На карте");
        QPushButton* btn2 = new QPushButton("Подробно");

        layout->setSizeConstraint(QLayout::SetMaximumSize);

        btn1->setProperty("index", QVariant(i));
        btn2->setProperty("index", QVariant(i));

        layout->setSpacing(0);

        layout->addWidget(btn1);
        layout->addWidget(btn2);

        connect(btn1, SIGNAL(clicked()), this, SLOT(drawPath()));
        connect(btn2, SIGNAL(clicked()), this, SLOT(showFullInfo()));

        QWidget* widget = new QWidget();
        widget->setLayout(layout);
        routesTableWidget->setCellWidget(i, 4, widget);
    }
}

void MainWindow::fillRoutesList(std::vector<std::vector<SearchParameters>> foundedRoutes) {

    if(foundedRoutes.size() == 0) {
        // todo: show alert dialog that no one routes has been found
    }
    this->vvPaths = foundedRoutes;


//    for(int i = 0; i < foundedRoutes.size(); i++) {
//        std::vector<SearchParameters> pathVector = foundedRoutes.at(i);
//        if(pathVector.size() == 0) {
//            //todo: alert dialog
//        } else {
//            RoutesTableItemModel tableItem;

//            std::string start = getPlaceName(pathVector.at(0).getStart());
//            std::string end = getPlaceName(pathVector.at(pathVector.size() - 1).getFinish());
//            QString qStart = QString::fromStdString(start);
//            QString qEnd = QString::fromStdString(end);

//            tableItem.start = qStart;
//            tableItem.end = qEnd;
//            tableItem.cost = defineCost(pathVector);
//            tableItem.time = defineTime(pathVector);
//            tableItem.pathVector = pathVector;

//            qDebug() << "SEARCH PARAM #" << i+1 << ": " << tableItem.time.toString();

//            tableRoutesList.push_back(tableItem);
//        }
//    }

    fillRoutesTableWidget(ui->routesTableWidget, ui->sortTypeComboBox->currentIndex());
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

void MainWindow::on_sortTypeComboBox_currentIndexChanged(int index)
{
    fillRoutesTableWidget(ui->routesTableWidget, index);
}

void MainWindow::on_clearButton_clicked()
{
    ui->routesTableWidget->clearContents();
    ui->routesTableWidget->setRowCount(0);
    ui->moneyCount->setValue(0);
    ui->timeEdit->setTime(QTime(0, 0));
    ui->startList->setCurrentIndex(0);
    ui->finishList->setCurrentIndex(0);
}

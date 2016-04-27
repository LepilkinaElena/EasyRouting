#include "routedialog.h"
#include "ui_routedialog.h"

RouteDialog::RouteDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RouteDialog)
{
    ui->setupUi(this);
}

RouteDialog::~RouteDialog()
{
    delete ui;
}

Transport RouteDialog::getTransport()
{
    if(ui->carRadioButton->isChecked())
        return Transport::CAR;
    if(ui->undergroundRadioButton->isChecked())
        return Transport::UNDERGROUND;
    if(ui->busRadioButton->isChecked())
        return Transport::BUS;
    if(ui->trolleybusRadioButton->isChecked())
        return Transport::TROLLEYBUS;
    if(ui->tramRadioButton->isChecked())
        return Transport::TRAM;
    if(ui->taxiRadioButton->isChecked())
        return Transport::TAXI;
    if(ui->footRadioButton->isChecked())
        return Transport::FOOT;
    return Transport::FOOT;
}

int RouteDialog::getCost()
{
    return ui->costSpinBox->value();
}

QTime RouteDialog::getTime()
{
    return ui->timeEdit->time();
}

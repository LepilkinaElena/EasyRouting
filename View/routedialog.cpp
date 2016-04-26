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

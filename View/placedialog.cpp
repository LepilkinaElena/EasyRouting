#include "placedialog.h"
#include "ui_placedialog.h"

PlaceDialog::PlaceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PlaceDialog)
{
    ui->setupUi(this);
}

PlaceDialog::~PlaceDialog()
{
    delete ui;
}

QString PlaceDialog::getPlaceName()
{
    return ui->lineEdit->text();
}

Interest PlaceDialog::getInterest()
{
    if(ui->sightRadioButton->isChecked())
        return Interest::SIGHT;
    if(ui->cultureRadioButton->isChecked())
        return Interest::CULTURE;
    if(ui->parkRadioButton->isChecked())
        return Interest::PARK;
    if(ui->entertainmentRadioButton->isChecked())
        return Interest::ENTERTAINMENT;
    return Interest::SIGHT;
}

void PlaceDialog::accept()
{
    if (ui->lineEdit->text().isEmpty())
    {
        QMessageBox::warning(this,"Ошибка при вводе", "Не задано название места!");
    }
    else
    {
        QDialog::accept();
    }
}

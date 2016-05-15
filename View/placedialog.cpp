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

void PlaceDialog::clear()
{
    ui->lineEdit->clear();
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
    std::vector<std::pair<std::string, int> > places = controller.getAllPlacesOnMap();
    std::vector<std::string> names;
    std::string name = ui->lineEdit->text().toStdString();
    for (auto const& element: places)
    {
        names.emplace_back(element.first);
    }
    if (ui->lineEdit->text().isEmpty())
    {
        QMessageBox::warning(this,"Ошибка при вводе", "Не задано название места!");
    }
    else if (std::find(names.begin(), names.end(), name) != names.end())
    {
        QMessageBox::warning(this,"Ошибка при вводе", "Место с таким именем уже существует!");
    }
    else
    {
        QDialog::accept();
    }
}

#ifndef ROUTEDIALOG_H
#define ROUTEDIALOG_H

#include <QDialog>
#include "ERModel/routecost.h"

namespace Ui {
class RouteDialog;
}

/*!\class RouteDialog
*\brief Класс виджета формы ввода данных о дороге
*\ref RouteDialog
*/
class RouteDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RouteDialog(QWidget *parent = 0);
    ~RouteDialog();
    /*!\fn getTransport();
    *\brief Метод возвращающий тип транспорта из интерфейса
    *\return тип транспорта
    */
    Transport getTransport();
    /*!\fn getCost();
    *\brief Метод возвращающий стоимость из интерфейса
    *\return стоимость
    */
    int getCost();
    /*!\fn getTime();
    *\brief Метод возвращающий время из интерфейса
    *\return время
    */
    QTime getTime();
private:
    Ui::RouteDialog *ui;
};

#endif // ROUTEDIALOG_H

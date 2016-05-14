#ifndef PLACEDIALOG_H
#define PLACEDIALOG_H

#include <QDialog>
#include <QStandardItemModel>
#include "View/selectionitem.h"
#include "ERModel/place.h"
#include <QMessageBox>
#include <QCloseEvent>

namespace Ui {
class PlaceDialog;
}


/*!\class PlaceDialog
*\brief Класс виджета формы ввода данных о месте
*\ref PlaceDialog
*/
class PlaceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PlaceDialog(QWidget *parent = 0);
    ~PlaceDialog();

    /*!\fn getPlaceName();
    *\brief Метод возвращающий название места из интерфейса
    *\return название
    */
    QString getPlaceName();
    /*!\fn getInterest();
    *\brief Метод возвращающий категорию места из интерфейса
    *\return категория
    */
    Interest getInterest();

    void clear();

private:
    Ui::PlaceDialog *ui;
protected:
    void accept();
};

#endif // PLACEDIALOG_H

#ifndef PLACEDIALOG_H
#define PLACEDIALOG_H

#include <QDialog>
#include <QStandardItemModel>
#include "View/selectionitem.h"
#include "ERModel/place.h"

namespace Ui {
class PlaceDialog;
}

class PlaceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PlaceDialog(QWidget *parent = 0);
    ~PlaceDialog();

    QString getPlaceName();
    Interest getInterest();

private slots:
    void on_checkBox_clicked();

private:
    Ui::PlaceDialog *ui;
};

#endif // PLACEDIALOG_H

#ifndef ROUTEDIALOG_H
#define ROUTEDIALOG_H

#include <QDialog>
#include "ERModel/routecost.h"

namespace Ui {
class RouteDialog;
}

class RouteDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RouteDialog(QWidget *parent = 0);
    ~RouteDialog();
    Transport getTransport();
    int getCost();
private:
    Ui::RouteDialog *ui;
};

#endif // ROUTEDIALOG_H

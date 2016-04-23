#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "View/selectionitem.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void setupUI();

    QStandardItemModel interestsModel;
    QStandardItemModel transportModel;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

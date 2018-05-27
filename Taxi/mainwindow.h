#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "taxiselector.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void print(QString msg);

    void process(QVector<SelectResult *> *re, int secs);

private:
    Ui::MainWindow *ui;
    TaxiSelector* ts;
};

#endif // MAINWINDOW_H

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "iostream"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    NetReader netreader;
    QVector<int> path;
    std::cout << Dijkstra::complex_dijkstra(netreader.getEdges(), netreader.getSrc(0), netreader.getDst(0), path) << std::endl;
}

MainWindow::~MainWindow()
{
    delete ui;
}

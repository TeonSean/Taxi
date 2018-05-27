#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "input.h"
#include "iostream"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&NetReader::getInstance(), SIGNAL(message(QString)), this, SLOT(print(QString)));
    NetReader::getInstance().init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::process(QVector<SelectResult*> *re, int secs)
{
    QString display = QString::number(secs) + " seconds used.\n";
    char buf[128];
    if(re->size() > 0)
    {
        for(auto i: *re)
        {
            sprintf(buf, "Taxi id %d, position %d, d1 %d, d2 %d, d3 %d, d4 %d, onboard detour %d, pickup detour %d.\n",
                    i->taxi, i->src, i->d1, i->d2, i->d3, i->d4, i->d1 == 0 ? 0 : i->d2 + i->d3 - i->d1, i->d3 - i->d4);
            display += QString(buf);
            delete i;
        }
    }
    else
    {
        display += "No qualified taxi.\n";
    }
    ui->textBrowser->setText(ui->textBrowser->toPlainText() + display);
    ui->pushButton->setEnabled(true);
    delete re;
}

void MainWindow::print(QString msg)
{
    ui->textBrowser->setText(ui->textBrowser->toPlainText() + msg + "\n");
}

void MainWindow::on_pushButton_clicked()
{
    Input* input = new Input(this);
    if(input->exec() == QDialog::Accepted)
    {
        ui->pushButton->setEnabled(false);
        int src = input->getSrc();
        int dst = input->getDst();
        QString msg = "Taxi requested. From " + QString::number(src) + " to " + QString::number(dst) + ".";
        print(msg);
        ts = new TaxiSelector(src, dst, this);
        connect(ts, SIGNAL(finish(QVector<SelectResult*>*, int)), this, SLOT(process(QVector<SelectResult*>*, int)));
        connect(ts, SIGNAL(finished()), ts, SLOT(deleteLater()));
        connect(ts, SIGNAL(message(QString)), this, SLOT(print(QString)));
        ts->start(QThread::TimeCriticalPriority);
    }
    delete input;
}

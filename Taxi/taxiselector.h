#ifndef TAXISELECTOR_H
#define TAXISELECTOR_H

#include <QObject>
#include <QVector>
#include "netreader.h"
#include "dijkstra.h"
#include <QThread>

class SelectResult
{

public:
    int taxi;
    int src;
    int d1;
    int d2;
    int d3;
    int d4;

    SelectResult(int taxi, int src, int d1, int d2, int d3, int d4);
};

class TaxiSelector : public QThread
{
    Q_OBJECT

    NetReader& nr;
    const int limit;
    int src;
    int dst;

public:
    explicit TaxiSelector(int src, int dst, QObject *parent = nullptr);

    void run();

signals:
    void finish(QVector<SelectResult*>*, int);
    void message(QString msg);

public slots:
};

#endif // TAXISELECTOR_H

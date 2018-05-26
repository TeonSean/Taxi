#ifndef TAXISELECTOR_H
#define TAXISELECTOR_H

#include <QObject>
#include <QList>
#include "netreader.h"
#include "dijkstra.h"

class SelectResult
{
public:
    int taxi;
    int onboard_detour;
    int pickup_detour;

    SelectResult(int taxi, int onboard_detour, int pickup_detour);
};

class TaxiSelector : public QObject
{
    Q_OBJECT

    NetReader nr;
    const int limit;

public:
    explicit TaxiSelector(QObject *parent = nullptr);

    QList<SelectResult> select(int src, int dst);

signals:

public slots:
};

#endif // TAXISELECTOR_H

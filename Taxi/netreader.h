#ifndef NETREADER_H
#define NETREADER_H

#include <QObject>
#include <QVector>
#include <QMap>

class Node
{
public:
    int id;
    float longitude;
    float latitude;

    Node(int id, float longitude, float latitude);
};

class Taxi
{
public:
    int id;
    int pos;
    QVector<int> dst;
    int d1;

    Taxi(int id, int pos, int d1, QVector<int>& dst_);
};

class NetReader : public QObject
{
    Q_OBJECT

    static NetReader* instance;
    QVector<Node*> nodes;
    QMap<int, QMap<int, int> > edges;
    QVector<Taxi*> taxis;
    QVector<int> sortedTaxis;

    explicit NetReader(QObject *parent = nullptr);
    void print(QString msg);
    void readCarData();
    void readNodeData();
    void readEdgeData();
    void readD1();

public:

    static NetReader& getInstance();

    QMap<int, QMap<int, int> >& getEdges();

    QVector<int>& getDst(int taxi);

    int getNodeCnt();

    int getSrc(int taxi);

    int getTaxiCnt();

    int getPassengerCnt(int taxi);

    int getD1(int taxi);

    int getTaxiIdx(int rank);

    void init();

signals:

    void message(QString msg);

public slots:
};

#endif // NETREADER_H

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

    Taxi(int id, int pos, QVector<int>& dst_);
};

class NetReader : public QObject
{
    Q_OBJECT

    QVector<Node*> nodes;
    QMap<int, QMap<int, int> > edges;
    QVector<Taxi*> taxis;

    void print(QString msg);
    void readCarData();
    void readNodeData();
    void readEdgeData();

public:
    explicit NetReader(QObject *parent = nullptr);

signals:

public slots:
};

#endif // NETREADER_H

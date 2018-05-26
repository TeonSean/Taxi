#include "netreader.h"
#include "QFile"
#include "iostream"
#include "sstream"
#include "iomanip"

Node::Node(int id, float longitude, float latitude):
    id(id), longitude(longitude), latitude(latitude)
{

}

Taxi::Taxi(int id, int pos, int d1, QVector<int> &dst_):
    id(id), pos(pos), d1(d1)
{
    for(auto i: dst_)
    {
        dst.push_back(i);
    }
}

NetReader::NetReader(QObject *parent) : QObject(parent)
{
    readNodeData();
    readEdgeData();
    readCarData();
}

void NetReader::readNodeData()
{
    QFile nodef("..\\data\\road.cnode");
    if(nodef.open(QIODevice::ReadOnly))
    {
        char buf[128];
        print("Reading node data.");
        std::stringstream ss;
        while(nodef.readLine(buf, sizeof(buf)) >= 0)
        {
            ss.str(buf);
            int id;
            float longitude, latitude;
            ss >> id >> longitude >> latitude;
            nodes.push_back(new Node(id, longitude, latitude));
        }
        print("Finished.");
    }
    else
    {
        print("Error reading nodes.");
    }
}

void NetReader::readEdgeData()
{
    QFile edgef("..\\data\\road.nedge");
    if(edgef.open(QIODevice::ReadOnly))
    {
        char buf[128];
        print("Reading edge data.");
        edgef.readLine(buf, sizeof(buf));
        std::stringstream ss;
        while(edgef.readLine(buf, sizeof(buf)) >= 0)
        {
            ss.str(buf);
            int node1, node2, dis;
            ss >> node1 >> node2 >> dis;
            edges[node1][node2] = dis;
            edges[node2][node1] = dis;
        }
        print("Finished.");
    }
    else
    {
        print("Error reading edges.");
    }
}

void NetReader::readCarData()
{
    QFile carf("..\\data\\car.txt");
    QFile df("..\\data\\d1.txt");
    if(carf.open(QIODevice::ReadOnly) && df.open(QIODevice::ReadOnly))
    {
        char buf[256], buf2[16];
        print("Reading car data.");
        std::stringstream ss;
        while(carf.readLine(buf, sizeof(buf)) >= 0 && df.readLine(buf2, sizeof(buf2)) >= 0)
        {
            ss.str(buf);
            int id, cnt;
            ss >> id >> cnt;
            char comma;
            int pos, d1;
            float longitude, latitude;
            ss >> longitude >> comma >> latitude >> comma >> pos;
            QVector<int> dst;
            for(int i = 0; i < cnt; i++)
            {
                int node;
                ss >> longitude >> comma >> latitude >> comma >> node;
                dst.push_back(node);
            }
            if(cnt > 0)
            {
                ss.str(buf2);
                ss >> d1;
            }
            else
            {
                d1 = 0;
            }
            taxis.push_back(new Taxi(id, pos, d1, dst));
        }
        print("Finished.");
    }
    else
    {
        print("Error reading cars.");
    }
}

QMap<int, QMap<int, int> >& NetReader::getEdges()
{
    return edges;
}

int NetReader::getTaxiCnt()
{
    return taxis.size();
}

QVector<int>& NetReader::getDst(int taxi)
{
    return taxis[taxi]->dst;
}

int NetReader::getSrc(int taxi)
{
    return taxis[taxi]->pos;
}

int NetReader::getPassengerCnt(int taxi)
{
    return taxis[taxi]->dst.size();
}

int NetReader::getD1(int taxi)
{
    return taxis[taxi]->d1;
}

void NetReader::print(QString msg)
{
    std::cout << msg.toStdString() << std::endl;
}

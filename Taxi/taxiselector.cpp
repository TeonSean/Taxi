#include "taxiselector.h"
#include <QTime>
#include <QPair>
#include <iostream>

SelectResult::SelectResult(int taxi, int src, int d1, int d2, int d3, int d4):
    taxi(taxi), src(src), d1(d1), d2(d2), d3(d3), d4(d4)
{

}

TaxiSelector::TaxiSelector(int src, int dst, QObject *parent) : QThread(parent), src(src), dst(dst), limit(10000), nr(NetReader::getInstance())
{

}

void TaxiSelector::run()
{
    QVector<SelectResult*>* re = new QVector<SelectResult*>();
    QMap<int, int> dis;
    emit message("Starts flooding.");
    Dijkstra::flood_dijkstra(nr.getEdges(), src, dis);
    int d4 = dis[dst];
    emit message("Finished flooding. D4 is " + QString::number(d4));
    QTime cur = QTime::currentTime();
    QVector<QPair<int, int> > near;
    for(int j = 0; j < nr.getTaxiCnt(); j++)
    {
        int i = nr.getTaxiIdx(j);
        if(nr.getPassengerCnt(i) < 4)
        {
            int d2 = dis[nr.getSrc(i)];
            if(d2 <= limit)
            {
                near.push_back(QPair<int, int>(i, d2));
            }
        }
    }
    for(int i = 0; i < near.size(); i++)
    {
        int d1 = nr.getD1(near[i].first);
        int d2 = near[i].second;
        int d3_ub = 0;
        d3_ub = std::min(limit + d4, limit + d1 - d2);
        QVector<int>& dsts = nr.getDst(near[i].first);
        bool flag = false;
        for(auto i: dsts)
        {
            if(i == dst)
            {
                flag = true;
                break;
            }
        }
        int d3;
        if(flag)
        {
            d3 = Dijkstra::complex_dijkstra(nr.getEdges(), src, dsts, d3_ub);
        }
        else
        {
            dsts.push_back(dst);
            d3 = Dijkstra::complex_dijkstra(nr.getEdges(), src, dsts, d3_ub);
            dsts.pop_back();
        }
        if(d3 < 0)
        {
            continue;
        }
        re->push_back(new SelectResult(near[i].first, nr.getSrc(near[i].first), d1, d2, d3, d4));
        if(re->size() == 5)
        {
            break;
        }
    }
    emit finish(re, cur.secsTo(QTime::currentTime()));
}

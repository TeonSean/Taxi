#include "taxiselector.h"

SelectResult::SelectResult(int taxi, int onboard_detour, int pickup_detour):
    taxi(taxi), onboard_detour(onboard_detour), pickup_detour(pickup_detour)
{

}

TaxiSelector::TaxiSelector(QObject *parent) : QObject(parent), limit(10000)
{

}

QList<SelectResult> TaxiSelector::select(int src, int dst)
{
    QList<SelectResult> re;
    int d4 = Dijkstra::simple_dijkstra(nr.getEdges(), src, dst);
    for(int i = 0; i < nr.getTaxiCnt(); i++)
    {
        if(nr.getPassengerCnt(i) == 4)
        {
            continue;
        }
        int d2 = Dijkstra::simple_dijkstra(nr.getEdges(), nr.getSrc(i), src);
        if(d2 > limit)
        {
            continue;
        }
        QVector<int>& dsts = nr.getDst(i);
        dsts.push_back(dst);
        int d3 = Dijkstra::complex_dijkstra(nr.getEdges(), src, dsts);
        dsts.pop_back();
        int onboard_detour = d2 + d3 - nr.getD1(i);
        if(onboard_detour > limit)
        {
            continue;
        }
        int pickup_detour = d3 - d4;
        if(pickup_detour > limit)
        {
            continue;
        }
        re.push_back(SelectResult(i, onboard_detour, pickup_detour));
        if(re == 5)
        {
            break;
        }
    }
    return re;
}

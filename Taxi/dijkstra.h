#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <QObject>
#include <QMap>
#include <QVector>

class Dijkstra
{
public:
    Dijkstra();

    static int simple_dijkstra(QMap<int, QMap<int, int> >& edges, int src, int dst);

    static void flood_dijkstra(QMap<int, QMap<int, int> >& edges, int src, QMap<int, int>& min_dis);

    static int next_state(int cur, int next, int base, QVector<int>& dst);

    static bool check_state(int cur, int base);

    class pq_ele
    {
    public:
        int state;
        int value;

        pq_ele(int state, int value);
    };

    static int complex_dijkstra(QMap<int, QMap<int, int> >& edges, int src,
                                QVector<int>& dst, int ub = INT_MAX);
};

bool operator <(const Dijkstra::pq_ele& t1, const Dijkstra::pq_ele& t2);

#endif // DIJKSTRA_H

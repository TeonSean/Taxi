#include "dijkstra.h"
#include <QSet>
#include <iostream>
#include <queue>

Dijkstra::Dijkstra()
{

}

void Dijkstra::flood_dijkstra(QMap<int, QMap<int, int> > &edges, int src, QMap<int, int> &min_dis)
{
    // init
    QMap<int, int>& src_edge = edges[src];
    std::priority_queue<pq_ele> q;
    for(auto e = src_edge.begin(); e != src_edge.end(); e++)
    {
        min_dis[e.key()] = e.value();
        q.push(pq_ele(e.key(), e.value()));
    }
    // loop
    while(true)
    {
        int work, work_value;
        while(true)
        {
            if(q.empty())
            {
                return;
            }
            work = q.top().state;
            work_value = q.top().value;
            q.pop();
            if(work_value == min_dis[work])
            {
                break;
            }
        }
        QMap<int, int>& new_edge = edges[work];
        for(auto e = new_edge.begin(); e != new_edge.end(); e++)
        {
            if(min_dis.count(e.key()))
            {
                if(work_value + e.value() < min_dis[e.key()])
                {
                    min_dis[e.key()] = work_value + e.value();
                    q.push(pq_ele(e.key(), work_value + e.value()));
                }
            }
            else
            {
                min_dis[e.key()] = work_value + e.value();
                q.push(pq_ele(e.key(), work_value + e.value()));
            }
        }
    }
}

int Dijkstra::simple_dijkstra(QMap<int, QMap<int, int> > &edges, int src, int dst)
{
    QMap<int, int> min_dis;
    // init
    QMap<int, int>& src_edge = edges[src];
    std::priority_queue<pq_ele> q;
    for(auto e = src_edge.begin(); e != src_edge.end(); e++)
    {
        if(e.key() == dst)
        {
            return e.value();
        }
        min_dis[e.key()] = e.value();
        q.push(pq_ele(e.key(), e.value()));
    }
    // loop
    while(true)
    {
        int work, work_value;
        while(true)
        {
            if(q.empty())
            {
                work = -1;
                break;
            }
            work = q.top().state;
            work_value = q.top().value;
            q.pop();
            if(work_value == min_dis[work])
            {
                break;
            }
        }
        if(work == -1)
        {
            return -1;
        }
        QMap<int, int>& new_edge = edges[work];
        for(auto e = new_edge.begin(); e != new_edge.end(); e++)
        {
            if(dst == e.key())
            {
                return work_value + e.value();
            }
            if(min_dis.count(e.key()))
            {
                if(work_value + e.value() < min_dis[e.key()])
                {
                    min_dis[e.key()] = work_value + e.value();
                    q.push(pq_ele(e.key(), work_value + e.value()));
                }
            }
            else
            {
                min_dis[e.key()] = work_value + e.value();
                q.push(pq_ele(e.key(), work_value + e.value()));
            }
        }
    }
}

int Dijkstra::next_state(int cur, int next, int base, QVector<int> &dst)
{
    int visit_state = cur % base;
    int opt = 1;
    for(int i = dst.size() - 1; i >= 0; i--, opt <<= 1)
    {
        if(next == dst[i])
        {
            visit_state |= opt;
            break;
        }
    }
    return next * base + visit_state;
}

bool Dijkstra::check_state(int cur, int base)
{
    return (cur % base) == (base - 1);
}

Dijkstra::pq_ele::pq_ele(int state, int value):
    state(state), value(value)
{

}

bool operator <(const Dijkstra::pq_ele& t1, const Dijkstra::pq_ele& t2)
{
    return t1.value >= t2.value;
}

int Dijkstra::complex_dijkstra(QMap<int, QMap<int, int> > &edges, int src, QVector<int> &dst, int ub)
{
    QMap<int, int> min_dis;
    // init
    int base = 1;
    for(int i = 0; i < dst.size(); i++)
    {
        base *= 2;
    }
    QMap<int, int>& src_edge = edges[src];
    std::priority_queue<pq_ele> q;
    for(auto e = src_edge.begin(); e != src_edge.end(); e++)
    {
        int next = next_state(src * base, e.key(), base, dst);
        if(check_state(next, base))
        {
            return e.value() > ub ? -1 : e.value();
        }
        min_dis[next] = e.value();
        q.push(pq_ele(next, e.value()));
    }
    // loop
    while(true)
    {
        int work, work_value;
        while(true)
        {
            if(q.empty())
            {
                work = -1;
                break;
            }
            work = q.top().state;
            work_value = q.top().value;
            q.pop();
            if(work_value == min_dis[work])
            {
                break;
            }
        }
        if(work == -1)
        {
            return -1;
        }
        if(work_value > ub)
        {
            return -1;
        }
        QMap<int, int>& new_edge = edges[work / base];
        for(auto e = new_edge.begin(); e != new_edge.end(); e++)
        {
            int next = next_state(work, e.key(), base, dst);
            if(check_state(next, base))
            {
                int re = work_value + e.value();
                return re > ub ? -1 : re;
            }
            if(min_dis.count(next))
            {
                if(work_value + e.value() < min_dis[next])
                {
                    min_dis[next] = work_value + e.value();
                    q.push(pq_ele(next, work_value + e.value()));
                }
            }
            else
            {
                min_dis[next] = work_value + e.value();
                q.push(pq_ele(next, work_value + e.value()));
            }
        }
    }
}

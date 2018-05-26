#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <iostream>

void calc_d1()
{
    NetReader netreader;
    int cnt = netreader.getTaxiCnt();
    QFile fout("..\\data\\d1.txt");
    fout.open(QIODevice::WriteOnly);
    for(int i = 0; i < cnt; i++)
    {
        char buf[128];
        int d1 = Dijkstra::complex_dijkstra(netreader.getEdges(), netreader.getSrc(i), netreader.getDst(i));
        sprintf(buf, "%d\n", d1);
        fout.write(buf);
        std::cout << i << "/" << cnt << ": " << d1 << std::endl;
    }
    fout.close();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    calc_d1();
    MainWindow w;
    w.show();
    return a.exec();
}

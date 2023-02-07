#include <QCoreApplication>
#include <iostream>
#include <QObject>
#include <QDebug>
#include "MonitoringSystem.h"


int main(int argc, char *argv[])
{

    //uruchomienie przez domyslny konstruktor lub zdefiniowany przez uzytkownika

    QCoreApplication a(argc, argv);
    qDebug()<<"uruchomiono";
    QString plik = "C:/Users/Programista3/Desktop/SystemFileMonitoring/plik.txt";
    QFileSystemWatcher *t = new QFileSystemWatcher(&a);

    //FileSystemMonitoringAlghoritm default_( &a); // #1

    MonitoringSystem::FileSystemMonitoringAlghoritm instancja_monitoringu(&a,plik,t); // #2
    instancja_monitoringu.addPathToFile();
    instancja_monitoringu.displayFileName();
    instancja_monitoringu.connectSignal();
    delete t;
    return a.exec();
}

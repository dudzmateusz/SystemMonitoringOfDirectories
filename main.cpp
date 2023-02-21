#include <QCoreApplication>
#include <iostream>
#include <QObject>
#include <QDebug>
#include "SystemFilesMonitor.h"
#include "ReceiverSignals.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QFileSystemWatcher watcher = new QFileSystemWatcher(&a);
    SystemFilesMonitor sfm1(&a,"/var/run/mbog/",watcher);


    /* Przykład odbierania sygnałów od monitorowanych plików====================================================================================
    ReceiverSignals rs1; //jakaś klasa zawierająca metody odbierające emit w slots
    const auto &w = sfm1.getInstance_BatteryStateMonitoring(); //instancja odpowiedniej klasy monitorujacej z SystemFilesMonitor
    const auto &p = sfm1.getInstance_PrinterStateMonitoring(); // -=-
    const auto &t = sfm1.getInstance_DeviceWorkingTimeMonitoring();// -=-
    const auto &l = sfm1.getInstance_LogMonitoring(); // -=-
    if(l!=NULL)
        QObject::connect(l, &LogMonitoring::logNotification_current_LogInfoHasChanged, &rs1, &ReceiverSignals::logNotification_current_LogInfoHasChanged); //połączenie
    ============================================================================================================================================
    */


    return a.exec();
}



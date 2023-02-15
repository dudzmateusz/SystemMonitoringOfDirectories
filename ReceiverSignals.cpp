#include "ReceiverSignals.h"
#include "PrinterStateMonitoring.h"
#include <QDebug>

/*
ReceiverSignals::ReceiverSignals(QObject *parent, QFileSystemWatcher& w, QString& string)
    : printer_instance(parent,string,w)
{

}
*/

ReceiverSignals::ReceiverSignals()
{

}


void ReceiverSignals::printerNotification_PrinterOvertemp(bool message)
{
    qDebug() << "printerNotification_PrinterOvertemp" << message;
}
void ReceiverSignals::printerNotification_CoverClosed(bool message)
{
    qDebug() << "printerNotification_CoverClosed" <<  message;
}
void ReceiverSignals::printerNotification_PaperAvailable(bool message)
{
    qDebug() << "printerNotification_PaperAvailable" << message;
}
void ReceiverSignals::printerNotification_ErrorOfPrinterMotor(bool message)
{
    qDebug() << "printerNotification_ErrorOfPrinterMotor" << message;
}
void ReceiverSignals::printerNotification_PrintingInProgress(bool message)
{
    qDebug() << "printerNotification_PrintingInProgress" << message;
}

 void ReceiverSignals::batteryNotification_PowerConnected(bool message)
 {
     qDebug() << "batteryNotification_PowerConnected" << message;
 }
 void ReceiverSignals::batteryNotification_ErrorOfBattery(bool message)
 {
     qDebug() << "batteryNotification_ErrorOfBattery" << message;
 }
 void ReceiverSignals::batteryNotification_BatteryDischarging(bool message)
 {
qDebug() << "batteryNotification_BatteryDischarging" << message;
 }
 void ReceiverSignals::batteryNotification_BatteryFull(bool message)
 {
     qDebug() << "batteryNotification_BatteryFull" << message;
 }
 void ReceiverSignals::batteryNotification_BatteryDead(bool message)
 {
    qDebug() << "batteryNotification_BatteryDead" << message;
 }
 void ReceiverSignals::batteryNotification_BatteryCharging(bool message)
 {
    qDebug() << "batteryNotification_BatteryCharging" << message;
 }
void ReceiverSignals::batteryNotification_VoltageHasChanged(uint message)
{
    qDebug() << "batteryNotification_VoltageHasChanged" << message;
}

void ReceiverSignals::batteryNotification_PercentHasChanged(uint message)
{
    qDebug() << "batteryNotification_PercentHasChanged" << message;
}

ReceiverSignals::~ReceiverSignals()
{

}

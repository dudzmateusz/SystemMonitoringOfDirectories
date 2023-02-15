#include <QCoreApplication>
#include <iostream>
#include <QObject>
#include <QDebug>
#include "MonitoringSystem.h"
#include "PrinterStateMonitoring.h"
#include "BatteryStateMonitoring.h"
#include "ReceiverSignals.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString printer_file = "C:/Users/Programista3/Desktop/SystemFileMonitoring/printer.txt";
    QFileSystemWatcher watcherPrinter = new QFileSystemWatcher(&a);
    QFileSystemWatcher watcherBattery = new QFileSystemWatcher(&a);
    PrinterStateMonitoring psm1(&a,printer_file,watcherPrinter);
    BatteryStateMonitoring bsm1(&a,"C:/Users/Programista3/Desktop/SystemFileMonitoring/battery.txt","C:/Users/Programista3/Desktop/SystemFileMonitoring/battery_voltage.txt","C:/Users/Programista3/Desktop/SystemFileMonitoring/battery_percent.txt",watcherBattery);
    ReceiverSignals rs1;
    QObject::connect(&psm1, &PrinterStateMonitoring::printerNotification_CoverClosed, &rs1, &ReceiverSignals::printerNotification_CoverClosed);
    QObject::connect(&psm1, &PrinterStateMonitoring::printerNotification_ErrorOfPrinterMotor, &rs1, &ReceiverSignals::printerNotification_ErrorOfPrinterMotor);
    QObject::connect(&psm1, &PrinterStateMonitoring::printerNotification_PaperAvailable, &rs1, &ReceiverSignals::printerNotification_PaperAvailable);
    QObject::connect(&psm1, &PrinterStateMonitoring::printerNotification_PrinterOvertemp, &rs1, &ReceiverSignals::printerNotification_PrinterOvertemp);
    QObject::connect(&psm1, &PrinterStateMonitoring::printerNotification_PrintingInProgress, &rs1, &ReceiverSignals::printerNotification_PrintingInProgress);

    QObject::connect(&bsm1, &BatteryStateMonitoring::batteryNotification_PowerConnected, &rs1, &ReceiverSignals::batteryNotification_PowerConnected);
    QObject::connect(&bsm1, &BatteryStateMonitoring::batteryNotification_ErrorOfBattery, &rs1, &ReceiverSignals::batteryNotification_ErrorOfBattery);
    QObject::connect(&bsm1, &BatteryStateMonitoring::batteryNotification_BatteryFull, &rs1, &ReceiverSignals::batteryNotification_BatteryFull);
    QObject::connect(&bsm1, &BatteryStateMonitoring::batteryNotification_VoltageHasChanged, &rs1, &ReceiverSignals::batteryNotification_VoltageHasChanged);
    QObject::connect(&bsm1, &BatteryStateMonitoring::batteryNotification_PercentHasChanged, &rs1, &ReceiverSignals::batteryNotification_PercentHasChanged);

    return a.exec();
}

#include <QCoreApplication>
#include <iostream>
#include <QObject>
#include <QDebug>
#include "MonitoringSystem.h"
#include "PrinterStateMonitoring.h"
#include "BatteryStateMonitoring.h"
#include "DeviceWorkingTimeMonitoring.h"
#include "ReceiverSignals.h"
#include "LogMonitoring.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QFileSystemWatcher watcher = new QFileSystemWatcher(&a);
    //PRINTER
    PrinterStateMonitoring psm1(&a,
                                "C:/Users/Programista3/Desktop/SystemFileMonitoring/printer.txt",
                                "C:/Users/Programista3/Desktop/SystemFileMonitoring/printer_PaperSensorTransducerValue.txt",
                                "C:/Users/Programista3/Desktop/SystemFileMonitoring/printer_temperature.txt",watcher);
    //BATTERY
    BatteryStateMonitoring bsm1(&a,"C:/Users/Programista3/Desktop/SystemFileMonitoring/battery.txt",
                                "C:/Users/Programista3/Desktop/SystemFileMonitoring/battery_voltage.txt",
                                "C:/Users/Programista3/Desktop/SystemFileMonitoring/battery_percent.txt",watcher);
    //DEVICE INFO
    DeviceWorkingTimeMonitoring dwtm1(&a,"C:/Users/Programista3/Desktop/SystemFileMonitoring/device_workingtime.txt",watcher);
    //LOG INFO
    LogMonitoring lm(&a, "C:/Users/Programista3/Desktop/SystemFileMonitoring/log.txt",watcher);

    // RECEIVER SIGNALS SYSTEM ----------------------------------------------------------------------------------------------------
    ReceiverSignals rs1;
    //PRINTER RECEIVER SIGNAL
    QObject::connect(&psm1, &PrinterStateMonitoring::printerNotification_CoverClosed, &rs1, &ReceiverSignals::printerNotification_CoverClosed);
    QObject::connect(&psm1, &PrinterStateMonitoring::printerNotification_ErrorOfPrinterMotor, &rs1, &ReceiverSignals::printerNotification_ErrorOfPrinterMotor);
    QObject::connect(&psm1, &PrinterStateMonitoring::printerNotification_PaperAvailable, &rs1, &ReceiverSignals::printerNotification_PaperAvailable);
    QObject::connect(&psm1, &PrinterStateMonitoring::printerNotification_PrinterOvertemp, &rs1, &ReceiverSignals::printerNotification_PrinterOvertemp);
    QObject::connect(&psm1, &PrinterStateMonitoring::printerNotification_PrintingInProgress, &rs1, &ReceiverSignals::printerNotification_PrintingInProgress);
    QObject::connect(&psm1, &PrinterStateMonitoring::printerNotification_PrinterPaperSensorTransducerValueHasChanged, &rs1, &ReceiverSignals::printerNotification_PrinterPaperSensorTransducerValueHasChanged);
    QObject::connect(&psm1, &PrinterStateMonitoring::printerNotification_PrinterTemperatureHasChanged, &rs1, &ReceiverSignals::printerNotification_PrinterTemperatureHasChanged);
    //BATTERY RECEIVER SIGNAL
    QObject::connect(&bsm1, &BatteryStateMonitoring::batteryNotification_PowerConnected, &rs1, &ReceiverSignals::batteryNotification_PowerConnected);
    QObject::connect(&bsm1, &BatteryStateMonitoring::batteryNotification_ErrorOfBattery, &rs1, &ReceiverSignals::batteryNotification_ErrorOfBattery);
    QObject::connect(&bsm1, &BatteryStateMonitoring::batteryNotification_BatteryFull, &rs1, &ReceiverSignals::batteryNotification_BatteryFull);
    QObject::connect(&bsm1, &BatteryStateMonitoring::batteryNotification_VoltageHasChanged, &rs1, &ReceiverSignals::batteryNotification_VoltageHasChanged);
    QObject::connect(&bsm1, &BatteryStateMonitoring::batteryNotification_PercentHasChanged, &rs1, &ReceiverSignals::batteryNotification_PercentHasChanged);
    //DEVICE WORKING TIME RECEIVER SIGNAL
    QObject::connect(&dwtm1, &DeviceWorkingTimeMonitoring::deviceNotification_WorkingTimeHasChanged, &rs1 , &ReceiverSignals::deviceNotification_WorkingTimeHasChanged);
    //LOG RECEIVER SIGNAL
    QObject::connect(&lm, &LogMonitoring::logNotification_current_LogInfoHasChanged, &rs1 , &ReceiverSignals::logNotification_current_LogInfoHasChanged);

    return a.exec();
}

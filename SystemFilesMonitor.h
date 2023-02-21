#ifndef SYSTEMFILESMONITOR_H
#define SYSTEMFILESMONITOR_H

#include <QObject>
#include <BatteryStateMonitoring.h>
#include <DeviceWorkingTimeMonitoring.h>
#include <LogMonitoring.h>
#include <PrinterStateMonitoring.h>

class SystemFilesMonitor : public QObject
{
    Q_OBJECT
private:
    BatteryStateMonitoring Instance_BatteryStateMonitoring;
    DeviceWorkingTimeMonitoring Instance_DeviceWorkingTimeMonitoring;
    LogMonitoring Instance_LogMonitoring;
    PrinterStateMonitoring Instance_PrinterStateMonitoring;
public:
    SystemFilesMonitor(
                       QObject *parent,
                       const QString &prefix,
                       QFileSystemWatcher &instance
                      );
    ~SystemFilesMonitor();
    BatteryStateMonitoring* getInstance_BatteryStateMonitoring();
    DeviceWorkingTimeMonitoring* getInstance_DeviceWorkingTimeMonitoring();
    LogMonitoring* getInstance_LogMonitoring();
    PrinterStateMonitoring* getInstance_PrinterStateMonitoring();
};

#endif // SYSTEMFILESMONITOR_H

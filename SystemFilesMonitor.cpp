#include "SystemFilesMonitor.h"


SystemFilesMonitor::SystemFilesMonitor
        (
            QObject *parent,
            const QString &prefix,
            QFileSystemWatcher &instance
        ):    Instance_BatteryStateMonitoring(parent,prefix+"battery/status",prefix+"battery/voltage",prefix+"battery/capacity",instance),
              Instance_DeviceWorkingTimeMonitoring(parent,prefix+"info/deviceinfo",instance),
              Instance_LogMonitoring(parent,prefix+"hw_log",instance),
              Instance_PrinterStateMonitoring(parent,prefix+"status",prefix+"converter_mv",prefix+"temp",instance){}
SystemFilesMonitor::~SystemFilesMonitor() {}

BatteryStateMonitoring* SystemFilesMonitor::getInstance_BatteryStateMonitoring()
{
    return &Instance_BatteryStateMonitoring;
}
DeviceWorkingTimeMonitoring* SystemFilesMonitor::getInstance_DeviceWorkingTimeMonitoring()
{
    return &Instance_DeviceWorkingTimeMonitoring;
}
LogMonitoring* SystemFilesMonitor::getInstance_LogMonitoring()
{
    return &Instance_LogMonitoring;
}
PrinterStateMonitoring* SystemFilesMonitor::getInstance_PrinterStateMonitoring()
{
    return &Instance_PrinterStateMonitoring;
}


#ifndef DEVICEWORKINGTIMEMONITORING_H
#define DEVICEWORKINGTIMEMONITORING_H

#include <QObject>
#include <MonitoringSystem.h>

class DeviceWorkingTimeMonitoring : public MonitoringSystem::FileSystemMonitoringAlghoritm
{
    Q_OBJECT
private:
    QString DeviceWorkingTimeMonitoringFile;
    uint current_workingTime;
public:
    DeviceWorkingTimeMonitoring(QObject *parent, const QString deviceInformation_path, QFileSystemWatcher &instance);
    ~DeviceWorkingTimeMonitoring();
    void read_file(const QString &path) override;
    void DeviceWorkingTimeMonitoring_current_workingTime(const QString &path);
    uint getcurrent_workingTime();
    QString getDeviceWorkingTimeMonitoringFile();
signals:
    void deviceNotification_WorkingTimeHasChanged(uint message);

};

#endif // DEVICEWORKINGTIMEMONITORING_H

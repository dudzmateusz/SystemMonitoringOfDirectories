#ifndef LOGMONITORING_H
#define LOGMONITORING_H

#include <QObject>
#include <MonitoringSystem.h>

class LogMonitoring : public MonitoringSystem::FileSystemMonitoringAlghoritm
{
    Q_OBJECT
private:
    QString LogMonitoringFile;
    std::string current_LogInfo;
public:
    LogMonitoring(QObject *parent, const QString deviceInformation_path, QFileSystemWatcher &instance);
    ~LogMonitoring();
    void read_file(const QString &path) override;
    void LogMonitoring_current_LogInfo(const QString &path);
    std::string getcurrent_LogInfo();
    QString getLogMonitoringFile();
signals:
    void logNotification_current_LogInfoHasChanged(std::string message);
};

#endif // LOGMONITORING_H

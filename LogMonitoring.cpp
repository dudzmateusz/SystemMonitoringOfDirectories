#include "LogMonitoring.h"
#include <QFile>
#include <fstream>
#include <bitset>
#include <QDebug>

LogMonitoring::LogMonitoring(QObject *parent,
                             const QString &deviceInformation_path,
                             QFileSystemWatcher &instance):
MonitoringSystem::FileSystemMonitoringAlghoritm::FileSystemMonitoringAlghoritm(parent, deviceInformation_path, instance)
{
    LogMonitoring_current_LogInfo(deviceInformation_path);
}
LogMonitoring::~LogMonitoring(){}
void LogMonitoring::read_file(const QString &path)
{
    if(path == LogMonitoringFile)
    {
        std::ifstream file(path.toStdString());
        std::string readDataInStringFormat = "";
        while (std::getline(file, readDataInStringFormat)){}
        if(current_LogInfo != readDataInStringFormat)
        {
            emit logNotification_current_LogInfoHasChanged(readDataInStringFormat);
        }
        current_LogInfo = readDataInStringFormat;
    }
}
void LogMonitoring::LogMonitoring_current_LogInfo(const QString &path)
{
    this->addPathToFile(path);
    LogMonitoringFile = path;
    std::ifstream file(LogMonitoringFile.toStdString());
    std::string str;
    while (std::getline(file, str)){}
    current_LogInfo = str;
    connectSignal(path);
}
std::string LogMonitoring::getcurrent_LogInfo()
{
    return this->current_LogInfo;
}
QString LogMonitoring::getLogMonitoringFile()
{
    return this->LogMonitoringFile;
}

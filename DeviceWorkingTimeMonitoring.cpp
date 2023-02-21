#include "DeviceWorkingTimeMonitoring.h"
#include <QFile>
#include <fstream>
#include <bitset>
#include <QDebug>

DeviceWorkingTimeMonitoring::DeviceWorkingTimeMonitoring(QObject *parent,
                                               const QString &deviceInformation_path,
                                               QFileSystemWatcher &instance):
    MonitoringSystem::FileSystemMonitoringAlghoritm::FileSystemMonitoringAlghoritm(parent, deviceInformation_path, instance)
{
    DeviceWorkingTimeMonitoring_current_workingTime(deviceInformation_path);
}
DeviceWorkingTimeMonitoring::~DeviceWorkingTimeMonitoring(){}
void DeviceWorkingTimeMonitoring::read_file(const QString &path)
{
    if(path == DeviceWorkingTimeMonitoringFile)
    {
        std::ifstream file(path.toStdString());
        std::string readDataInStringFormat = "";
        uint getDataInIntFormat = 0; // zakres danych - 4294967295
        while (std::getline(file, readDataInStringFormat))
        {
            getDataInIntFormat = static_cast<uint>(std::stoul(readDataInStringFormat)); // konwersja do uint - zakres danych 4294967295
        }
        uint new_value_WorkingTime = getDataInIntFormat;
        if(current_workingTime != new_value_WorkingTime)
        {
            emit deviceNotification_WorkingTimeHasChanged(new_value_WorkingTime);
        }
        current_workingTime = new_value_WorkingTime;
    }
}
QString DeviceWorkingTimeMonitoring::getDeviceWorkingTimeMonitoringFile()
{
    return this->DeviceWorkingTimeMonitoringFile;
}
void DeviceWorkingTimeMonitoring::DeviceWorkingTimeMonitoring_current_workingTime(const QString &path)
{
    this->addPathToFile(path);
    DeviceWorkingTimeMonitoringFile = path;
    std::ifstream file(DeviceWorkingTimeMonitoringFile.toStdString());
    std::string str;
    uint getDataInIntFormat = 0;
    while (std::getline(file, str))
        {
            getDataInIntFormat = static_cast<uint>(std::stoul(str)); // konwersja do uint - zakres danych 4294967295
        }
    current_workingTime = getDataInIntFormat;
    connectSignal(path);
}
uint DeviceWorkingTimeMonitoring::getcurrent_workingTime()
{
    return this->current_workingTime;
}

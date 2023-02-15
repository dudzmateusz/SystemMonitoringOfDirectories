#include "BatteryStateMonitoring.h"
#include <QFile>
#include <fstream>
#include <bitset>
#include <QDebug>

BatteryStateMonitoring::BatteryStateMonitoring(QObject *parent,
                                               const QString batteryState_path,
                                               const QString batteryVoltage_path,
                                               const QString batteryPercent_path ,
                                               QFileSystemWatcher &instance):
    MonitoringSystem::FileSystemMonitoringAlghoritm::FileSystemMonitoringAlghoritm(parent, batteryState_path, instance),
    previous_state(0)
{
    BatteryStateMonitoring_BatteryState(batteryState_path);
    BatteryStateMonitoring_BatteryVoltage(batteryVoltage_path);
    BatteryStateMonitoring_BatteryPercent(batteryPercent_path);
}

BatteryStateMonitoring::~BatteryStateMonitoring(){}
void BatteryStateMonitoring::BatteryStateMonitoring_BatteryPercent(const QString &path)
{
    this->addPathToFile(path);
    BatteryPercentFile = path;
    std::ifstream file(BatteryPercentFile.toStdString());
    std::string str;
    uint getDataInIntFormat = 0;
    while (std::getline(file, str))
        {
            getDataInIntFormat = std::stoi(str.data());
        }
    current_percent_of_battery = getDataInIntFormat;
    connectSignal(path);
}
void BatteryStateMonitoring::BatteryStateMonitoring_BatteryVoltage(const QString &path)
{
    this->addPathToFile(path);
    BatteryVoltageFile = path;
    std::ifstream file(BatteryVoltageFile.toStdString());
    std::string str;
    uint getDataInIntFormat = 0;
    while (std::getline(file, str))
        {
            getDataInIntFormat = std::stoi(str.data());
        }
    current_voltage = getDataInIntFormat;
    connectSignal(path);
}
void BatteryStateMonitoring::BatteryStateMonitoring_BatteryState(const QString &path)
{
    this->addPathToFile(path);
    BatteryStateFile = path;
    std::ifstream file(BatteryStateFile.toStdString());
    std::string str;
    uint getDataInIntFormat = 0;
    while (std::getline(file, str))
        {
            getDataInIntFormat = std::stoi(str.data());
        }
    ulong getDataInDecimalFormat = std::bitset<8>(getDataInIntFormat).to_ulong();
    previous_state = getDataInDecimalFormat;
    connectSignal(path);
                //getdirOfPath().at(getPathIndexPosition(BatteryStateFile)
}
BatteryState BatteryStateMonitoring::GetPrinterState()
{
    return previous_state;
}
QString BatteryStateMonitoring::getBatteryStateFile()
{
    return this->BatteryStateFile;
}
QString BatteryStateMonitoring::getBatteryVoltageFile()
{
    return this->BatteryVoltageFile;
}
QString BatteryStateMonitoring::getBatteryPercentFile()
{
    return this->BatteryPercentFile;
}
void BatteryStateMonitoring::read_file(const QString &path)
{
  if(path == BatteryStateFile){
        std::ifstream file(path.toStdString());
        std::string readDataInStringFormat = "";
        uint getDataInIntFormat = 0;
        while (std::getline(file, readDataInStringFormat))
        {
            getDataInIntFormat = std::stoi(readDataInStringFormat.data());
        }
        ulong new_status_byte = getDataInIntFormat;
        BatteryState new_state = BatteryState(new_status_byte);
        if(previous_state.PowerConnected == false && new_state.PowerConnected == true)
        {
            emit batteryNotification_PowerConnected(new_state.PowerConnected);
        }
        if(previous_state.ErrorOfBattery == false && new_state.ErrorOfBattery == true)
        {
            emit batteryNotification_ErrorOfBattery(new_state.ErrorOfBattery);
        }
        if(previous_state.BatteryFull == false && new_state.BatteryFull == true)
        {
            emit batteryNotification_BatteryFull(new_state.BatteryFull);
        }
        previous_state.PowerConnected = new_state.PowerConnected;
        previous_state.ErrorOfBattery = new_state.ErrorOfBattery;
        previous_state.BatteryFull = new_state.BatteryFull;
}
if(path == BatteryVoltageFile)
{
    std::ifstream file(path.toStdString());
    std::string readDataInStringFormat = "";
    uint getDataInIntFormat = 0;
    while (std::getline(file, readDataInStringFormat))
    {
        getDataInIntFormat = std::stoi(readDataInStringFormat.data());
    }
    ulong new_value_voltage = getDataInIntFormat;
    if(current_voltage != new_value_voltage){
        emit batteryNotification_VoltageHasChanged(new_value_voltage);
    }
    current_voltage = new_value_voltage;
}
if(path ==BatteryPercentFile)
{
    std::ifstream file(path.toStdString());
    std::string readDataInStringFormat = "";
    uint getDataInIntFormat = 0;
    while (std::getline(file, readDataInStringFormat))
    {
        getDataInIntFormat = std::stoi(readDataInStringFormat.data());
    }
    ulong new_value_percent = getDataInIntFormat;
    if(current_percent_of_battery != new_value_percent){
        emit batteryNotification_PercentHasChanged(new_value_percent);
    }
    current_percent_of_battery = new_value_percent;
}
}

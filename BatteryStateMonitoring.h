#ifndef BATTERYSTATEMONITORING_H
#define BATTERYSTATEMONITORING_H

#include "MonitoringSystem.h"
#include <QObject>

struct BatteryState {
    BatteryState(uint8_t status_byte)
    {
        PowerConnected = status_byte & 0b00000001;
        ErrorOfBattery = status_byte & 0b00000010;
        BatteryDischarging = status_byte & 0b00000100;
        BatteryDead = status_byte & 0b00001000;
        BatteryFull = status_byte & 0b00010000;
        BatteryCharging = status_byte & 0b00100000;
    };
    bool PowerConnected;
    bool ErrorOfBattery;
    bool BatteryDischarging;
    bool BatteryFull;
    bool BatteryDead;
    bool BatteryCharging;
};

class BatteryStateMonitoring : public MonitoringSystem::FileSystemMonitoringAlghoritm
{
    Q_OBJECT

private:
    BatteryState previous_state;
    QString BatteryStateFile;
    QString BatteryVoltageFile;
    QString BatteryPercentFile;
    uint current_voltage;
    uint current_percent_of_battery;
public:
    BatteryStateMonitoring(QObject *parent, const QString &batteryState_path, const QString &batteryVoltage_path,const QString &batteryPercent_path, QFileSystemWatcher &instance);
    ~BatteryStateMonitoring();
    BatteryState GetPrinterState();
    void read_file(const QString &path) override;
    QString getBatteryStateFile();
    QString getBatteryVoltageFile();
    QString getBatteryPercentFile();
    void BatteryStateMonitoring_BatteryState(const QString &path);
    void BatteryStateMonitoring_BatteryVoltage(const QString &path);
    void BatteryStateMonitoring_BatteryPercent(const QString &path);
signals:
    void batteryNotification_PowerConnected(bool message);
    void batteryNotification_ErrorOfBattery(bool message);
    void batteryNotification_BatteryFull(bool message);
    void batteryNotification_BatteryDischarging(bool message);
    void batteryNotification_BatteryDead(bool message);
    void batteryNotification_BatteryCharging(bool message);
    void batteryNotification_VoltageHasChanged(uint message);
    void batteryNotification_PercentHasChanged(uint message);

};

#endif // BATTERYSTATEMONITORING_H

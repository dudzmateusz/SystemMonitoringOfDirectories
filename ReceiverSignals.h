#ifndef RECEIVERSIGNALS_H
#define RECEIVERSIGNALS_H

#include <QObject>

class ReceiverSignals : public QObject
{
    Q_OBJECT
private:
    uint8_t instance_printer = 0;
public:
    //ReceiverSignals(QObject *parent, QFileSystemWatcher& w, QString& string);
     ReceiverSignals();
    ~ReceiverSignals();
public slots:
//PRINTER SLOTS
     virtual void printerNotification_CoverClosed(bool message);
     virtual void printerNotification_PrinterOvertemp(bool message);
     virtual void printerNotification_PaperAvailable(bool message);
     virtual void printerNotification_ErrorOfPrinterMotor(bool message);
     virtual void printerNotification_PrintingInProgress(bool message);
     virtual void printerNotification_PrinterPaperSensorTransducerValueHasChanged(uint message);
     virtual void printerNotification_PrinterTemperatureHasChanged(uint message);
//BATTERY SLOTS
     virtual void batteryNotification_PowerConnected(bool message);
     virtual void batteryNotification_ErrorOfBattery(bool message);
     virtual void batteryNotification_BatteryDischarging(bool message);
     virtual void batteryNotification_BatteryFull(bool message);
     virtual void batteryNotification_BatteryDead(bool message);
     virtual void batteryNotification_BatteryCharging(bool message);
     virtual void batteryNotification_VoltageHasChanged(uint message);
     virtual void batteryNotification_PercentHasChanged(uint message);
//DEVICE SLOTS
    virtual void deviceNotification_WorkingTimeHasChanged(uint message);
//LOG SLOTS
     virtual void logNotification_current_LogInfoHasChanged(std::string message);
};

#endif // RECEIVERSIGNALS_H

#ifndef PRINTERSTATEMONITORING_H
#define PRINTERSTATEMONITORING_H

#include <QObject>
#include "MonitoringSystem.h"


struct PrinterState {
    PrinterState(uint8_t status_byte)
    {
        CoverClosed = status_byte & 0b00000100;
        PrinterOvertemp = status_byte & 0b00010000;
        PaperAvailable = status_byte & 0b00001000;
        ErrorOfPrinterEngine = status_byte & 0b00000010;
        PrintingInProgress = status_byte & 0b00000001;
    };
    bool CoverClosed;
    bool PrinterOvertemp;
    bool PaperAvailable;
    bool ErrorOfPrinterEngine;
    bool PrintingInProgress;
};
class PrinterStateMonitoring: public MonitoringSystem::FileSystemMonitoringAlghoritm
{
    Q_OBJECT
private:
    PrinterState previous_state;
    QString PrinterStateFile;
    QString PrinterPaperSensorTransducerValueFile;
    QString PrinterTemperatureFile;
    uint current_temperature;
    uint current_paperSensorTransducerValueFile;
public:
    PrinterStateMonitoring(QObject *parent, const QString printerState_path,const QString printerPaperSensorTransducerValue_path,const QString printerTemperature_path,QFileSystemWatcher &instance);
    ~PrinterStateMonitoring();
    PrinterState GetPrinterState();
    void read_file(const QString &path) override;
    void PrinterStateMonitoring_PrinterState(const QString &path);
    void PrinterStateMonitoring_PrinterPaperSensorTransducerValue(const QString &path);
    void PrinterStateMonitoring_PrinterTemperature(const QString &path);
signals:
    void printerNotification_CoverClosed(bool message);
    void printerNotification_PrinterOvertemp(bool message);
    void printerNotification_PaperAvailable(bool message);
    void printerNotification_ErrorOfPrinterMotor(bool message);
    void printerNotification_PrintingInProgress(bool message);
    void printerNotification_PrinterPaperSensorTransducerValueHasChanged(uint message);
    void printerNotification_PrinterTemperatureHasChanged(uint message);
};

#endif // PRINTERSTATEMONITORING_H

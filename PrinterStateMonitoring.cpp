#include "PrinterStateMonitoring.h"
#include <QFile>
#include <fstream>
#include <bitset>

PrinterStateMonitoring::PrinterStateMonitoring(QObject *parent,
                                               const QString &printerState_path,
                                               const QString &printerPaperSensorTransducerValue_path,
                                               const QString &printerTemperature_path,
                                               QFileSystemWatcher &instance) :
   MonitoringSystem::FileSystemMonitoringAlghoritm::FileSystemMonitoringAlghoritm(parent, printerState_path, instance),
   previous_state(0)
{
    PrinterStateMonitoring_PrinterState(printerState_path);
    PrinterStateMonitoring_PrinterPaperSensorTransducerValue(printerPaperSensorTransducerValue_path);
    PrinterStateMonitoring_PrinterTemperature(printerTemperature_path);
}
PrinterStateMonitoring::~PrinterStateMonitoring(){}
void PrinterStateMonitoring::PrinterStateMonitoring_PrinterState(const QString &path)
{
    this->addPathToFile(path);
    PrinterStateFile = path;
    std::ifstream file(PrinterStateFile.toStdString());
    std::string str;
    uint getDataInIntFormat = 0;
    while (std::getline(file, str))
        {
            getDataInIntFormat = static_cast<uint>(std::stoul(str));
        }
    ulong getDataInDecimalFormat = std::bitset<8>(getDataInIntFormat).to_ulong();
    previous_state = getDataInDecimalFormat;
    connectSignal(path);
}

void PrinterStateMonitoring::PrinterStateMonitoring_PrinterPaperSensorTransducerValue(const QString &path)
{
    this->addPathToFile(path);
    PrinterPaperSensorTransducerValueFile = path;
    std::ifstream file(PrinterPaperSensorTransducerValueFile.toStdString());
    std::string str;
    uint getDataInIntFormat = 0;
    while (std::getline(file, str))
        {
            getDataInIntFormat = static_cast<uint>(std::stoul(str));
        }
    current_paperSensorTransducerValueFile = getDataInIntFormat;
    connectSignal(path);
}
void PrinterStateMonitoring::PrinterStateMonitoring_PrinterTemperature(const QString &path)
{
    this->addPathToFile(path);
    PrinterTemperatureFile = path;
    std::ifstream file(PrinterTemperatureFile.toStdString());
    std::string str;
    uint getDataInIntFormat = 0;
    while (std::getline(file, str))
        {
            getDataInIntFormat = static_cast<uint>(std::stoul(str));
        }
    current_temperature = getDataInIntFormat;
    connectSignal(path);
}

PrinterState PrinterStateMonitoring::GetPrinterState()
{
    return previous_state;
}
void PrinterStateMonitoring::read_file(const QString &path)
{
    if(path == PrinterStateFile)
    {
        std::ifstream file(path.toStdString());
        std::string readDataInStringFormat = "";
        uint getDataInIntFormat = 0;
        while (std::getline(file, readDataInStringFormat))
        {
            getDataInIntFormat = static_cast<uint>(std::stoul(readDataInStringFormat));
        }
        ulong new_status_byte = getDataInIntFormat;
        PrinterState new_state = PrinterState(new_status_byte);
        if(previous_state.PrinterOvertemp == false && new_state.PrinterOvertemp == true)
        {
            emit printerNotification_PrinterOvertemp(new_state.PrinterOvertemp);
        } // if previous and new state is true do should we send information  to map and emit it? // QUESTION#1
        if(previous_state.CoverClosed == true && new_state.CoverClosed == false)
        {
            emit printerNotification_CoverClosed(new_state.CoverClosed);
        }
        if(previous_state.ErrorOfPrinterEngine == false && new_state.ErrorOfPrinterEngine == true)
        {
            emit printerNotification_ErrorOfPrinterMotor(new_state.ErrorOfPrinterEngine);
        }
        if(previous_state.PaperAvailable == true && new_state.PaperAvailable == false)
        {
            emit printerNotification_PaperAvailable(new_state.PaperAvailable);
        }
        if(previous_state.PrintingInProgress == false && new_state.PrintingInProgress == true)
        {
            emit printerNotification_PrintingInProgress(new_state.PrintingInProgress);
        }
        if (previous_state.PrintingInProgress == true && new_state.PrintingInProgress == false)
        {
            emit printerNotification_PrintingInProgress(new_state.PrintingInProgress);
        }
        previous_state.CoverClosed = new_state.CoverClosed;
        previous_state.PrinterOvertemp = new_state.PrinterOvertemp;
        previous_state.ErrorOfPrinterEngine = new_state.ErrorOfPrinterEngine;
        previous_state.PaperAvailable = new_state.PaperAvailable;
        previous_state.PrintingInProgress = new_state.PrintingInProgress;
   }
   if(path == PrinterPaperSensorTransducerValueFile)
   {
       std::ifstream file(path.toStdString());
       std::string readDataInStringFormat = "";
       uint getDataInIntFormat = 0;
       while (std::getline(file, readDataInStringFormat))
       {
           getDataInIntFormat = static_cast<uint>(std::stoul(readDataInStringFormat));
       }
       ulong new_value_paperSensorTransducerValueFile = getDataInIntFormat;
       if(current_paperSensorTransducerValueFile != new_value_paperSensorTransducerValueFile)
       {
           emit printerNotification_PrinterPaperSensorTransducerValueHasChanged(new_value_paperSensorTransducerValueFile);
       }
       current_paperSensorTransducerValueFile = new_value_paperSensorTransducerValueFile;
   }
   if(path == PrinterTemperatureFile)
   {
       std::ifstream file(path.toStdString());
       std::string readDataInStringFormat = "";
       uint getDataInIntFormat = 0;
       while (std::getline(file, readDataInStringFormat))
       {
           getDataInIntFormat = static_cast<uint>(std::stoul(readDataInStringFormat));
       }
       ulong new_value_temperature = getDataInIntFormat;
       if(current_temperature != new_value_temperature)
       {
           emit printerNotification_PrinterTemperatureHasChanged(new_value_temperature);
       }
       current_temperature = new_value_temperature;
   }
}




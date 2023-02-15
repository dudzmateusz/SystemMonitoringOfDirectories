#include "PrinterStateMonitoring.h"
#include <QFile>
#include <fstream>
#include <bitset>

PrinterStateMonitoring::PrinterStateMonitoring(QObject *parent, const QString path, QFileSystemWatcher &instance) :
   MonitoringSystem::FileSystemMonitoringAlghoritm::FileSystemMonitoringAlghoritm(parent, path, instance),
   previous_state(0)
{
    this->addPathToFile(path);
    std::ifstream file(getPath().toStdString());
    std::string str = "";
    uint getDataInIntFormat = 0;
    std::string getDataInStringFormat = "";
    while (std::getline(file, str))
    {
        getDataInIntFormat = std::stoi(str.data());
    }
    ulong getDataInDecimalFormat = std::bitset<8>(getDataInIntFormat).to_ulong();
    previous_state = getDataInDecimalFormat;
    connectSignal(getdirOfPath().at(0));
}

PrinterStateMonitoring::~PrinterStateMonitoring(){}

PrinterState PrinterStateMonitoring::GetPrinterState()
{
    return previous_state;
}

void PrinterStateMonitoring::read_file(const QString &path)
{
    std::ifstream file(path.toStdString());
    std::string readDataInStringFormat = "";
    uint getDataInIntFormat = 0;
    while (std::getline(file, readDataInStringFormat))
    {
        getDataInIntFormat = std::stoi(readDataInStringFormat.data());
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




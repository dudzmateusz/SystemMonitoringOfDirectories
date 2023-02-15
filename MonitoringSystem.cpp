#include "MonitoringSystem.h"
#include <QFile>
#include <QString>
#include <QObject>
#include <QDebug>
#include <QFileSystemWatcher>
#include <iostream>
#include <fstream>
#include <QDateTime>

MonitoringSystem::FileSystemMonitoringAlghoritm::FileSystemMonitoringAlghoritm(QObject *parent, const QString path, QFileSystemWatcher &instance) : QObject(parent)
{
    this->path = path;
    this->instance = &instance;
}
MonitoringSystem::FileSystemMonitoringAlghoritm::~FileSystemMonitoringAlghoritm()
{
}
bool MonitoringSystem::FileSystemMonitoringAlghoritm::compareValueFromFileWithVector(int ValueFromFile, std::vector<int> ValueFromVector)
{
    for(size_t i = 0; i < ValueFromVector.size(); i++)
    {
        if(ValueFromFile!=ValueFromVector.at(i))
        {
            ValueFromVector.clear();
            qDebug() << "Dane w pliku zmienione.";
            return true;
        }
        else
        {
            return false;
        }
    }
    return false;
}
QString MonitoringSystem::FileSystemMonitoringAlghoritm::getPath()
{
    return this->path;
}
bool MonitoringSystem::FileSystemMonitoringAlghoritm::compareTwoUintDatas(const uint8_t& first, const uint8_t& second)
{
    unsigned i = 1;
    uint8_t iteration = 0x80;
    while(i<=sizeof(uint8_t *))
    {
        if((!(first & iteration)) && (second & iteration))
        {
            qDebug() << "Dane sie roznia. Inna wartosc bitu na pozycji: " << i ;
        }
        else
        {
            qDebug() << "Dane nie zmienione.";
        }
     iteration = iteration>>1;
     ++i;
     }
    return true;
}
void MonitoringSystem::FileSystemMonitoringAlghoritm::read_file(const QString &path)
{
    std::ifstream file(path.toStdString());
    std::string str;
    int i;
    std::vector<int> dataFromFile {0};
    while (std::getline(file, str))
    {
        std::istringstream ss(str);
        ss >> i;
        this->compareValueFromFileWithVector(i,dataFromFile);
    }
}
void MonitoringSystem::FileSystemMonitoringAlghoritm::getSavedDataInVector(std::vector<int> ValueFromVector)
{
    for(size_t i =0; i < ValueFromVector.size(); i++)
    {
        qDebug() << ValueFromVector.at(i);
    }
}
const QString MonitoringSystem::FileSystemMonitoringAlghoritm::showFileName()
{
    return this->path;
}
void MonitoringSystem::FileSystemMonitoringAlghoritm::displayFileName()
{
    qDebug() << showFileName().data();
}
void MonitoringSystem::FileSystemMonitoringAlghoritm::fileHasChanged(const QString &path)
{
        this->read_file(path);
}
int MonitoringSystem::FileSystemMonitoringAlghoritm::getPathIndexPosition(const QString &path)
{
    if(this->instance->files().contains(path)==true)
    {
        int i =0;
        while (i < getdirOfPath().count())
        {
            if ( getdirOfPath().at(i) == path)
            {
                return i;
            }
            i++;
        }
    }
return 0;
}
QFileSystemWatcher MonitoringSystem::FileSystemMonitoringAlghoritm::getInstanceOfFileSystemWather()
{
    return this->instance;
}
QStringList MonitoringSystem::FileSystemMonitoringAlghoritm::getdirOfPath() const
{
    return this->instance->files();
}
void MonitoringSystem::FileSystemMonitoringAlghoritm::addPathToFile(const QString path)
{
    if(QFile::exists(path))
    {
        this->instance->addPath(path);
        if (this->instance->files().contains(path) == true)
        {
            qDebug() << "Lokalizacja istnieje, dodano sciezke: " << path;
        }
        else
        {
            qDebug() << "Błąd w dodawaniu ścieżki: "<< path;
        }
    }
    else
    {
        qDebug("Brak przekazywanej sciezki...");
        exit(0);
    }
}
void MonitoringSystem::FileSystemMonitoringAlghoritm::connectSignal(const QString &path)
{
    FileSystemMonitoringAlghoritm::connect
                (
                    this->instance, //instancja QFileSystemWatcher'a
                    &QFileSystemWatcher::fileChanged, //Metoda do monitorowania pliku z QFileSystemWatcher'a
                    this, //instancja MonitorSystem::FileSystemMonitoringAlghoritm
                    [this, &path] // lambda wywołująca metodę z MonitorSystem::FileSystemMonitorAlghoritm
                                  {
                                    fileHasChanged(path);
                                  }
                );
}


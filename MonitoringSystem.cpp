#include "MonitoringSystem.h"
#include <QFile>
#include <QString>
#include <QObject>
#include <QDebug>
#include <QFileSystemWatcher>
#include <iostream>


MonitoringSystem::FileSystemMonitoringAlghoritm::FileSystemMonitoringAlghoritm(QObject *parent, const QString dir, QFileSystemWatcher *instance) : QObject(parent)
{
    this->dir = dir;
    this->instance = instance;

}
MonitoringSystem::FileSystemMonitoringAlghoritm::FileSystemMonitoringAlghoritm(QObject *parent) : QObject(parent)
{
    QString file_to_monitoring = "C:\\Users\\Programista3\\Desktop\\SystemFileMonitoring\\plik.txt";
    this->instance = new QFileSystemWatcher(this);
    if(do_files_in_directory(file_to_monitoring)==true){
        this->instance->addPath(file_to_monitoring);
        FileSystemMonitoringAlghoritm::connect(this->instance, SIGNAL(fileChanged(const QString &)), this, SLOT(fileHasChanged(const QString &)));
      }
}

MonitoringSystem::FileSystemMonitoringAlghoritm::~FileSystemMonitoringAlghoritm()
{
}
const QString MonitoringSystem::FileSystemMonitoringAlghoritm::showFileName()
{
    return this->dir;
}
void MonitoringSystem::FileSystemMonitoringAlghoritm::displayFileName()
{
    std::cout<< showFileName().toStdString() << std::endl;
}
void MonitoringSystem::FileSystemMonitoringAlghoritm::fileHasChanged(const QString &path)
{
    qDebug() << "File changed" << path;
}
void MonitoringSystem::FileSystemMonitoringAlghoritm::directoryHasChanged(const QString & path)
{
    qDebug() << "Directory changed" << path;
}
void MonitoringSystem::FileSystemMonitoringAlghoritm::do_contains_files()
{
    std::cout<< this->instance->files().contains(dir);
}
QFileSystemWatcher MonitoringSystem::FileSystemMonitoringAlghoritm::getInstanceOfFileSystemWather()
{
    return this->instance;
}
QString MonitoringSystem::FileSystemMonitoringAlghoritm::getdirOfPath() const
{
 return this->dir;
}
bool MonitoringSystem::FileSystemMonitoringAlghoritm::do_files_in_directory(QString localisatioon_of_file)
{
    if(QFile::exists(localisatioon_of_file)){
        if (this->instance->files().contains(localisatioon_of_file) == true)
        {
            return true;
        }
        else
        {
            return false;
        }
}
    return true;
}
void MonitoringSystem::FileSystemMonitoringAlghoritm::addPathToFile()
{
    if(QFile::exists(dir)){
        this->instance->addPath(dir);
        if (this->instance->files().contains(dir) == true)
        {
            qDebug("Lokalizacja istnieje, dodano sciezke.");
        }
        else
        {
            qDebug("Blad w dodawaniu sciezki");
        }
    }
    else
    {
        qDebug("Brak przekazywanej sciezki...");
        exit(0);
    }
}
void MonitoringSystem::FileSystemMonitoringAlghoritm::connectSignal()
{
    this->instance = new QFileSystemWatcher(this);
    addPathToFile();
    FileSystemMonitoringAlghoritm::connect(this->instance, SIGNAL(fileChanged(const QString &)), this, SLOT(fileHasChanged(const QString &)));
}

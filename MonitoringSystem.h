#ifndef MONITORINGSYSTEM_H
#define MONITORINGSYSTEM_H

#include <QFileSystemWatcher>
#include <QObject>
#include <QThread>
#include <QCoreApplication>

namespace MonitoringSystem{
    class FileSystemMonitoringAlghoritm: public QObject
    {
        Q_OBJECT
    private:
        QString path = nullptr;
        QFileSystemWatcher *instance = nullptr;
    public:
        FileSystemMonitoringAlghoritm(QObject *parent, const QString path, QFileSystemWatcher &instance) ;
        ~FileSystemMonitoringAlghoritm();
        const QString showFileName();
        virtual void addPathToFile(const QString path);
        virtual void connectSignal(const QString &path);
        virtual void displayFileName();
        virtual int  getPathIndexPosition(const QString &path);
        virtual bool compareTwoUintDatas(const uint8_t& first, const uint8_t& second);
        virtual void read_file(const QString &path);
        virtual void getSavedDataInVector(std::vector<int> ValueFromVector);
        bool compareValueFromFileWithVector(int ValueFromFile, std::vector<int> ValueFromVector);
        QFileSystemWatcher getInstanceOfFileSystemWather();
        QStringList getdirOfPath() const;
        QString getPath();
    public slots:
        virtual void fileHasChanged(const QString &path);
    };

}
#endif // MONITORINGSYSTEM_H

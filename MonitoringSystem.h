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
        QString dir = nullptr;
        QFileSystemWatcher *instance = nullptr;
    public:
        FileSystemMonitoringAlghoritm(QObject *parent=0, const QString dir = 0, QFileSystemWatcher *instance = 0) ;
        FileSystemMonitoringAlghoritm(QObject *parent=0);
        ~FileSystemMonitoringAlghoritm();
        const QString showFileName();
        void addPathToFile();
        void connectSignal();
        void displayFileName();
        void do_contains_files();
        bool do_files_in_directory(QString localisatioon_of_file);
        QFileSystemWatcher getInstanceOfFileSystemWather();
        QString getdirOfPath() const;
    public slots:
        void fileHasChanged(const QString &path);
        void directoryHasChanged(const QString & path);

    };
}
#endif // MONITORINGSYSTEM_H

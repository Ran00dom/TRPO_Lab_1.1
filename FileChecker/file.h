#ifndef FILE_H
#define FILE_H

#include <QFileInfo>
#include <QDateTime>
#include <QObject>
#include <QVector>

class FileInfoRecorder:public QFileInfo
{

private:
    bool exist = true;
    QDateTime timeModified;
    qint64 sizeFile;

public:
    FileInfoRecorder(QString dir):QFileInfo(dir){};
    bool updateData();
};

class FileManager:public QObject
{
       Q_OBJECT

private:
    QVector<FileInfoRecorder> files;

private:
    FileManager():QObject(){files.clear();};
    FileManager(const FileManager&) = delete;
    FileManager& operator=(const FileManager&) = delete;
    int getFile(QString name) const;
public:
    static FileManager& Instance(); // возвращает адресс единственного экземпляра

    bool addFile(QString dir);
    bool removeFile(QString name);
    bool removeFile(int index);
    bool reset(QString nameResetFile, QString dirNewFile);

signals:
    void logUpdate(QString name, bool exist, qint64 size, QString date);
public slots:
    void update(bool);
};

#endif // FILE_H

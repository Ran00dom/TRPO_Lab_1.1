#ifndef FILE_H
#define FILE_H

#include <QFileInfo>
#include <QDateTime>
#include <QObject>

class FileInfoRecorder:public QFileInfo
{

private:
    bool exist = true;
    QDateTime timeModified;
    qint64 size;

public:
    FileInfoRecorder(QString dir):QFileInfo(dir){};
    bool updateData();
};

class FileManager:public QObject
{
       Q_OBJECT
private:

    int count{0};

private:
    int getFile(QString name);

public:
    FileManager(){};
    ~FileManager();

    bool addFile(QString dir);
    bool removeFile(QString dir);
    bool removeFile(int index);
    bool reset(QString nameResetFile, QString dirNewFile);
};

#endif // FILE_H

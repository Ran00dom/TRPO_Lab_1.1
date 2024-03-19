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
    QVector<FileInfoRecorder> files;
    int getFile(QString name);

public:
    FileManager():QObject(){files.clear();};

    bool addFile(QString dir);
    bool removeFile(QString name);
    bool removeFile(int index);
    bool reset(QString nameResetFile, QString dirNewFile);
};

#endif // FILE_H

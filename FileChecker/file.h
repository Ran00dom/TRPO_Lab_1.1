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

    int count{0};

private:
    QVector<FileInfoRecorder> files;
    int getFile(QString name) const;

public:
    FileManager():QObject(){files.clear();};

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

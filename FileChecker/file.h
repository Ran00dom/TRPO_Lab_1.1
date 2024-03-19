#ifndef FILE_H
#define FILE_H

#include <QFileInfo>
#include <QDateTime>
#include <QObject>
#include <QDebug>

class FileInfoRecorder:public QFileInfo
{
    Q_OBJECT // макрос для компиляции слотов и сигналов
private:
    bool exist = true;
    QDateTime timeModified;
    qint64 size;

public:
    FileInfoRecorder(QString dir):QFileInfo(dir){};
    bool updateData();
};

class FileManager
{
private:

    int count{0};

public:
    FileManager(){};
    ~FileManager();
    FileInfoRecorder* addFile(const char* dir);
    FileInfoRecorder* removeFile(const char* name);
    FileInfoRecorder* removeFile(int index);
    FileInfoRecorder* removeFile(FileInfoRecorder*);
    FileInfoRecorder* getFile(int);
    FileInfoRecorder* getFile(const char* name);
    FileInfoRecorder* reset(FileInfoRecorder* , const char* dir);
};

#endif // FILE_H

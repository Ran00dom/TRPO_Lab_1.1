#ifndef FILE_H
#define FILE_H

#include <QFileInfo>
#include <QDateTime>
#include <QObject>
#include <QDebug>

class FileInfoRecorder:public QObject
{
    Q_OBJECT // макрос для компиляции слотов и сигналов
private:
    bool exist = true;
    QDateTime timeModified;
    qint64 size;
    QFileInfo* file;

    FileInfoRecorder* next;

public:
    FileInfoRecorder(const char* parth, FileInfoRecorder* next);
    virtual ~FileInfoRecorder(){delete file;};
    bool addNext(FileInfoRecorder*);
    bool isFileName(const char* name);
    FileInfoRecorder* getNext();

signals:
    void logedStatus(QFileInfo*);

public slots:
    void updateData();

};

class FileManager
{
private:
    FileInfoRecorder* headList= nullptr;
    FileInfoRecorder* tail = nullptr;
    int count{0};

public:
    FileManager(){};
    FileInfoRecorder* addFile(const char* dir);
    FileInfoRecorder* removeFile(const char* name);
    FileInfoRecorder* removeFile(int index);
    FileInfoRecorder* removeFile(FileInfoRecorder*);
    FileInfoRecorder* getFile(int);
    FileInfoRecorder* getFile(const char* name);
};

#endif // FILE_H

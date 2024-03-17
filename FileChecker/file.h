#ifndef FILE_H
#define FILE_H

#include <QFileInfo>
#include <QDateTime>
#include <QObject>

class FileInfoRecorder:public QFileInfo
{
    Q_OBJECT // макрос для компиляции слотов и сигналов
private:
    bool exist = false;
    QDateTime timeModified;
    qint64 size;

    FileInfoRecorder* next;

public:
    FileInfoRecorder(const char* parth, FileInfoRecorder* next);
    virtual ~FileInfoRecorder(){};
    bool addNext(FileInfoRecorder*);
    FileInfoRecorder* getNext();
signals:
    int logedStatus(QFileInfo* file);
public slots:
    bool updateData();

};

class FileManager
{
private:
    FileInfoRecorder* headList= nullptr;
    FileInfoRecorder* tail = nullptr;
    int count{0};

public:
    FileManager(){};
    virtual ~FileManager(){};
    FileInfoRecorder* addFile(const char* dir);
    FileInfoRecorder* removeFile(const char* dir);
    FileInfoRecorder* removeFile(int index);
};

#endif // FILE_H

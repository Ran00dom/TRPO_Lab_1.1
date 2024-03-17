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
signals:
    int logedStatus(QFileInfo* file);
public slots:
    bool updateData();

};

#endif // FILE_H

#ifndef FILE_H
#define FILE_H

#include <QFileInfo>


class FileInfoRecorder:public QFileInfo
{

private:
    bool exist = false;
    QDateTime lastModifire();
    FileInfoRecorder* next;

public:
    FileInfoRecorder(const char* parth);

};

#endif // FILE_H

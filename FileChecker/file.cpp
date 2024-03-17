#include "file.h"

FileInfoRecorder::FileInfoRecorder(const char* parth, FileInfoRecorder* next):QFileInfo(parth)
{
    exist = exists();
    timeModified = lastModified();
    this->next = next;
    this->size = QFileInfo::size();
}

bool FileInfoRecorder::updateData()
{
    bool updateExist = exists();
    QDateTime lastTimeModified = lastModified();

    if (updateExist != exist || lastTimeModified != timeModified)
        logedStatus(this);
}

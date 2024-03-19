#include "file.h"
#include <iostream>


bool FileInfoRecorder::updateData()
{
    refresh();
    bool updateExist = exists();
    QDateTime lastTimeModified = lastModified();

    if (updateExist != exist || lastTimeModified != timeModified) {
        exist = updateExist;
        timeModified = lastTimeModified;
        return true;
    }
    return false;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool FileManager::addFile(QString dir)
{
    return false;
}


bool FileManager::removeFile(QString dir)
{
    return false;
}

bool FileManager::removeFile(int index)
{
    return false;
}

int  FileManager::getFile(QString name) // получить элемент списка
{
    return -1;
}

bool FileManager::reset(QString nameResetFile, QString dirNewFile)
{

}

FileManager::~FileManager()
{

}

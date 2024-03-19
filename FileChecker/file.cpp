#include "file.h"

bool FileInfoRecorder::updateData()
{
    refresh();
    bool updateExist = exists();
    QDateTime lastTimeModified = lastModified();

    if (updateExist != exist || lastTimeModified != timeModified) {
        exist = updateExist;
        timeModified = lastTimeModified;
        sizeFile = this->size();
        return true;
    }
    return false;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////


FileManager& FileManager::Instance()
{
    static FileManager singleInstance;
    return singleInstance;
}

int  FileManager::getFile(QString name) const  // получить элемент списка
{
    for (int var = 0; var < files.length(); var++) {
        if (files.at(var).fileName() == name || files.at(var).fileName() + "." + files.at(var).suffix() == name)
            return var;
    }
    return -1;
}

//---------------------------------------------------------------------------------//

bool FileManager::addFile(QString dir)
{
    int length = files.length();
    FileInfoRecorder* file = new FileInfoRecorder(dir);
    files.append(*file);
    if (length != files.length())
        return true;
    else {
        delete file;
        return false;
    }
}

bool FileManager::removeFile(QString name)
{
    if (!files.empty()){
        int state = getFile(name);
        if (state > -1) {
            int length = files.length();
            files.remove(state);

            if (length != files.length())
                return true;
        }
    }
    return false;
}

bool FileManager::removeFile(int index)
{
    if (!files.empty())
        if (index > -1 && index < files.length()){
            int length = files.length();
            files.remove(index);

            if (length != files.length())
                return true;
        }
    return false;
}

bool FileManager::reset(QString nameResetFile, QString dirNewFile)
{
    if (removeFile(nameResetFile))
        if (addFile(dirNewFile))
            return true;
    return false;
}

void FileManager::update(bool forcibly = false)
{
    for (int var = 0; var < files.length(); var++) {
        if (files[var].updateData() || forcibly){
            const FileInfoRecorder& file = files.at(var);
            emit logUpdate(file.fileName(), file.exists(), file.size(), file.lastModified().date().toString() + ":" + file.lastModified().time().toString());
        }
    }
}

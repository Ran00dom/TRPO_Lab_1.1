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

FileInfoRecorder* FileManager::addFile(const char* dir)
{
    if (headList == nullptr) {
        headList = new FileInfoRecorder(dir, nullptr);
        tail = headList;
        count++;
    }
    else {
        FileInfoRecorder* element = new FileInfoRecorder(dir, nullptr);
        tail->addNext(element);
        tail = element;
    }
    return tail;
}


FileInfoRecorder* FileManager::removeFile(const char* name)
{
    int i = 0;
    FileInfoRecorder* back = nullptr;
    count--;
    for (FileInfoRecorder* ptr = headList ; ptr != nullptr ;  back = ptr, ptr = ptr->getNext(), i++)
        if (ptr->isFileName(name))
            if (ptr == headList){
                ptr = ptr->getNext();
                delete headList;
                headList = ptr;
                return ptr;
            }
            else {
                if (ptr == tail){
                    tail = back;
                    back->addNext(nullptr);
                    delete ptr;
                    return tail;
                }
                else {
                    ptr = ptr->getNext();
                    delete back->getNext();
                    back->addNext(ptr);
                    return back->getNext();
                }
            }
    return nullptr;
}

FileInfoRecorder* FileManager::removeFile(int index)
{
    int i = 0;
    FileInfoRecorder* back = nullptr;
    count--;
    for (FileInfoRecorder* ptr = headList ; ptr != nullptr ;  back = ptr, ptr = ptr->getNext(), i++)
        if (i == index)
            if (ptr == headList){
                ptr = ptr->getNext();
                delete headList;
                headList = ptr;
                return ptr;
            }
            else {
                if (ptr == tail){
                    tail = back;
                    back->addNext(nullptr);
                    delete ptr;
                    return tail;
                }
                else {
                    ptr = ptr->getNext();
                    delete back->getNext();
                    back->addNext(ptr);
                    return back->getNext();
                }
            }
    return nullptr;
}

FileInfoRecorder* FileManager::removeFile(FileInfoRecorder* file)
{
    FileInfoRecorder* back = nullptr;
    count--;
    for (FileInfoRecorder* ptr = headList ; ptr != nullptr ;  back = ptr, ptr = ptr->getNext())
        if (file == ptr)
            if (ptr == headList){
                ptr = ptr->getNext();
                delete headList;
                headList = ptr;
                return ptr;
            }
            else {
                if (ptr == tail){
                    tail = back;
                    back->addNext(nullptr);
                    delete ptr;
                    return tail;
                }
                else {
                    ptr = ptr->getNext();
                    delete back->getNext();
                    back->addNext(ptr);
                    return back->getNext();
                }
            }
    return nullptr;
}


FileInfoRecorder*  FileManager::getFile(int index) // получить элемент списка
{
     int i = 0;
    for (FileInfoRecorder* ptr = headList ; ptr != nullptr ; ptr = ptr->getNext(), i++)
        if (index == i)
            return ptr;
    return nullptr;
}

FileInfoRecorder*  FileManager::getFile(const char* name) // получить элемент списка
{
    for (FileInfoRecorder* ptr = headList ; ptr != nullptr ; ptr = ptr->getNext())
        if (ptr->isFileName(name))
            return ptr;
    return nullptr;
}

FileInfoRecorder* FileManager::reset(FileInfoRecorder* file, const char* dir)
{
    if (file != nullptr){
        file->reset(dir);
        return file;
    }
    return nullptr;
}

FileManager::~FileManager()
{
    FileInfoRecorder* back = nullptr;
    for (FileInfoRecorder* ptr = headList ; ptr != nullptr ;  back = ptr, ptr = ptr->getNext()){
        if (back != nullptr){
            delete back;
        }
    }
    if (back != nullptr)
        delete back;
}

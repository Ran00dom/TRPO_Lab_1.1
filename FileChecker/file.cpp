#include "file.h"
#include <iostream>

FileInfoRecorder::FileInfoRecorder(const char* parth, FileInfoRecorder* next):QObject()
{
    file = new QFileInfo(parth);
    if (file != nullptr) {
        this->next = next;
        this->size = file->size();
    }
}

bool FileInfoRecorder::addNext(FileInfoRecorder* next)
{
    this->next = next;
    if (next != nullptr) {
        return true;
    }
    else
        return false;
}

void FileInfoRecorder::updateData()
{
    std::cout << "update" << std::endl;
    file->refresh();
    bool updateExist = file->exists();
    QDateTime lastTimeModified = file->lastModified();

    if (updateExist != exist || lastTimeModified != timeModified) {
        exist = updateExist;
        timeModified = lastTimeModified;
        emit logedStatus(this->file);
    }
}

FileInfoRecorder* FileInfoRecorder::getNext()
{
    return next;
}

bool FileInfoRecorder::isFileName(const char* name)
{
    if (file->fileName() == name)
        return true;
    return false;
}


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



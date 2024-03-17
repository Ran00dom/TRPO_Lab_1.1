#include "loger.h"
#include <QDebug>

void Loger::logFileUpdate(QFileInfo* file)
{
    if (file->exists())
        qDebug() << file->baseName() << "STATUS / exist? " << file->exists() << " / size?  " << file->size();
}

void Loger::logList(string name, int sizeX , int sizeY , string* columName, string** table)
{
    if (sizeX == 0 || sizeY == 0){
        qDebug() << &name;
    }
    else{
        qDebug() << "<< " << &name << ">>";
    }

    for (int i = 0; i < sizeX; i++)
    {
        cout << columName[i] << " | ";
    }
    cout << endl;

    for (int i = 0; i < sizeX; i++) {
        for (int j = 0; j < sizeY; j++){
            cout << table[i][j] << " | ";
        }
        cout << endl;
    }
}

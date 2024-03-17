#include "loger.h"
#include <QDebug>


void Loger::logFileUpdate(QFileInfo* file)
{
    if (file != nullptr) {
            qDebug() << file->baseName() << "STATUS / exist? " << file->exists() << " / size?  " << file->size();
    }
}

void Loger::logList(string name, TypeMessage type , int sizeX , int sizeY , string* columName, string** table)
{
    setColor(type);
    switch (type) {
    case ERRORS: {
        cout << "ERROR: ";
        break;
    }
    case WARNING:{
        cout << "WARNING: ";
        break;
    }
    case ACCEPT:{
        cout << "ACCEPT: ";
        break;
    }
    case MESSAGE:{
        cout << "MESSAGE: ";
        break;
    }
    case INFO: {break;};
        break;
    }

    if (sizeX == 0 || sizeY == 0){
        cout << name << endl;
    }
    else{
        cout << "<< " << &name << ">>" << endl;


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
    setColor();
}

void Loger::setColor(TypeMessage type)
{
    HANDLE consol = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(consol, type);
}

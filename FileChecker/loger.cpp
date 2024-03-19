#include "loger.h"
#include <QDateTime>
#include <QDebug>


void Loger::logFileUpdate(QString name, bool exist, qint64 size, QString date)
{

    qDebug() << name << "STATUS / exist? " << exist << " / size?  " << size << " / last Time Modified " << date;

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
        case INFO: break;

        break;
        }
            setColor();

    if (sizeX == 0 || sizeY == 0){
        cout << name << endl;
    }
    else{
        cout << "<< " << name << ">>" << endl;

        cout << "index" << endl;
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
}

void Loger::setColor(TypeMessage type)
{
    HANDLE consol = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(consol, type);
}

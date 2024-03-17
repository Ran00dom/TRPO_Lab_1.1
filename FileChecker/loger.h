#ifndef LOGER_H
#define LOGER_H

#include <QFileInfo>
#include <iostream>
#include <Windows.h>

using namespace std;

enum TypeMessage
{
    ERRORS = 4,
    WARNING = 6,
    ACCEPT = 2,
    INFO = 7,
    MESSAGE = 1
};


class Loger:public QObject
{
    Q_OBJECT

private:
    void setColor(TypeMessage = INFO);

public:
    Loger():QObject(){};
    virtual ~Loger(){};
    void logList(string name,  TypeMessage type = INFO ,int sizeX = 0, int sizeY = 0, string* columName = nullptr, string** table = nullptr);

public slots:
    void logFileUpdate(QFileInfo*);
};

#endif // LOGER_H

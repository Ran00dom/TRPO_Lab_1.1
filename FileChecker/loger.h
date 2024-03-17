#ifndef LOGER_H
#define LOGER_H

#include <QFileInfo>
#include <iostream>

using namespace std;

class Loger
{
    Q_OBJECT
public:
    Loger(){};
    void logList(string name, int sizeX = 0, int sizeY = 0, string* columName = nullptr, string** table = nullptr);

public slots:
    void logFileUpdate(QFileInfo*);
};

#endif // LOGER_H

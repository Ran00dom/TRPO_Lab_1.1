#ifndef MYAPPLICATION_H
#define MYAPPLICATION_H

#include "file.h"
#include "loger.h"
#include <QCoreApplication>
#include <QThread>
#include <QString>

enum Command
{
    COMMAND_FILE = 0,
    COMMAND_HELP,
    COMMAND_ADD,
    COMMAND_DROP,
    COMMAND_LISTEN,
    COMMAND_MUTE,
    COMMAND_RESET,
    COMMAND_LIST,
    COMMAND_EXIT,
};


class Console: public QObject
{
    Q_OBJECT

public:
    Console():QObject(){};

signals:
    void commandInput(QString);
public slots:
   bool listenCommand()
   {
       while (true)
       {
           std::string s;
           std::getline(std::cin,s);
           QString df(s.c_str());
           emit commandInput(df);
       }

    };
};



class MyApplication : public QCoreApplication
{
    Q_OBJECT

private:
    int consolTimer;
    int listenTimer;
    bool listenFile = false;

    FileManager& manager = FileManager::Instance();
    Loger& log = Loger::Instance();
    Console consol;

    QThread thread;

    const int numCommand = 10;
    const QString commands[10] =
        {
            "/file",
            "help",
            "add",
            "drop",
            "listen",
            "mute",
            "reset",
            "list",
            "exit",
            "empty"
        };

public:
    MyApplication(int argc, char*argv[]);

private:
    int commandCheck(QString);
   QString* spliter(QString, int*);
    void timerEvent(QTimerEvent*); // переопределение для таймера

signals:
    void update(bool forcibly = false);
public slots:
    bool listenCommand(QString);
};

#endif // MYAPPLICATION_H

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
    COMMAND_LIST,
    COMMAND_EXIT,
};



class Console: public QObject
{
    Q_OBJECT

private:
    Console():QObject(){};
    Console(Console&) = delete;
    Console& operator=(Console&) = delete;
public:
    static Console& Instance();

signals:
    void commandInput(QString);
public slots:
    void listenCommand();
};



class MyApplication : public QCoreApplication
{
    Q_OBJECT

private:
    int listenTimer;
    bool listenFile = false;

    FileManager& manager = FileManager::Instance();
    Loger& log = Loger::Instance();
    Console& consol = Console::Instance();

    QThread consoleThread;

    const int numCommand = 10;
    const QString commands[10] =
        {
            "/file",
            "help",
            "add",
            "drop",
            "listen",
            "mute",
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
    void consoleListen();
public slots:
    bool listenCommand(QString);
};

#endif // MYAPPLICATION_H

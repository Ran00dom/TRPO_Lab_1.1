#ifndef MYAPPLICATION_H
#define MYAPPLICATION_H

#include "file.h"
#include "loger.h"
#include <QCoreApplication>
#include <iostream>


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


class MyApplication : public QCoreApplication
{
    Q_OBJECT

private:
    int consolTimer;
    int listenTimer;
    bool listenFile = false;

    FileManager manager;
    Loger log;

    const int numCommand = 10;
    const std::string commands[10] =
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
    bool listen();
    FileInfoRecorder* connectFileLog(FileInfoRecorder*);
    FileInfoRecorder* disconnectFileLog(FileInfoRecorder*);

    bool listenCommand(std::string);
     int commandCheck(std::string);

    std::string* spliter(std::string, int*);


    void timerEvent(QTimerEvent*); // переопределение для таймера
signals:
    void update();
};

#endif // MYAPPLICATION_H

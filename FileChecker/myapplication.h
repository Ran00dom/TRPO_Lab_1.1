#ifndef MYAPPLICATION_H
#define MYAPPLICATION_H

#include <QCoreApplication>
#include <iostream>


enum Command
{
    COMMAND_FILE,
    COMMAND_HELP,
    COMMAND_ADD,
    COMMAND_DROP,
    COMMAND_LISTEN,
    COMMAND_MUTE
};


class MyApplication : public QCoreApplication
{
private:
    int timerID;
    bool listenFile = false;
    const std::string commands[7] =
        {
            "/file",
            "help",
            "add",
            "drop",
            "listen",
            "mute",
            "empty"
        };

public:
    MyApplication(int argc, char*argv[]);

private:
    bool listen();
    void connectFileLog(int*, int*);
    void disconnectFileLog(int*, int*);

    bool listenCommand(std::string);
     int commandCheck(std::string);

    std::string* spliter(std::string, int*);


    void timerEvent(QTimerEvent*); // переопределение для таймера
};

#endif // MYAPPLICATION_H

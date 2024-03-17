#include "myapplication.h"
#include <QDebug>
#include <cstring>
#include <conio.h>

MyApplication::MyApplication(int argc, char*argv[]):QCoreApplication(argc,argv)
{
    consolTimer = startTimer(50); // запуск таймера консоли
}

void MyApplication::timerEvent(QTimerEvent* event)
{
    if (event->timerId() == consolTimer){ // проверка id таймера
        if (_kbhit()) {
            std::string str;
            std::getline(std::cin,str); // чтение из консоли
            listenCommand(str); // проверка ввода
        }
    }
    else
        if (event->timerId() == listenTimer){
            emit update();
        }
        else
            QCoreApplication::timerEvent(event);
}

bool MyApplication::listenCommand(std::string str) // определяет и выполняет команды
{
    if (!str.empty()) //  строка не пустая
    {
        int countWord; // количество строк
        std::string *command = spliter(str, &countWord); // разделяем троку на слова

        if (command[0] == "/file" && countWord > 0) // проверяем ключивое слово и параметры за ним
            switch (commandCheck(command[1])) {  // поиск параметра по индексу


            case COMMAND_ADD:
                if (countWord > 2 && countWord < 4) {
                    if (connectFileLog(manager.addFile(command[2].c_str())) == nullptr)
                        log.logList("File dont add!", ERRORS);
                    else
                        log.logList("File add!", ACCEPT);
                    break;
                }
                else {
                    log.logList("Command not difined!", WARNING);
                    break;
                }


            case COMMAND_DROP:
                if (countWord > 2 && countWord < 4) {
                    if (manager.getFile(std::stoi(command[2])))
                    {
                        manager.removeFile(disconnectFileLog(manager.getFile(std::stoi(command[2]))));
                    }
                }
                else
                {
                    // not correct parth
                }


            case COMMAND_LISTEN: // запуск прослушивания
                if (countWord > 1 && countWord < 3) {
                    if (!listenFile) {
                        listenFile = true;
                        log.logList("Listen start!", ACCEPT);
                        listenTimer = startTimer(1000);
                    }
                    else
                        log.logList("Already listen!", WARNING);
                    break;
                }
                else
                    log.logList("Command not difined!", WARNING);


            case COMMAND_MUTE: // выключить прослушку
                if (countWord > 1 && countWord < 3) {
                    if (listenFile) {
                        listenFile = false;
                        log.logList("Mute listen!", ACCEPT);
                        killTimer(listenTimer);
                    }
                    else
                        log.logList("Already mute!", WARNING);
                }
                else
                    log.logList("Command not difined!", WARNING);


            case COMMAND_HELP:{
                // help info
            }


            break;
            default: // исключение
                log.logList("Command not difined!", WARNING);
                return false;

            }
        return false;
    }
    return true;
}

int MyApplication::commandCheck(std::string str) // проверка индекса ключевого слова
{
    for (int i = 0; i < 7 ; i++) {
        if (str == commands[i])
            return i;
    }
    return -1;
}

std::string* MyApplication::spliter(std::string str, int* countWord = nullptr) // деление строки по пробелам
{
    if (!str.empty())
    {
        int num = std::count(str.begin(),str.end(), ' ') + 1;
        std::string *newStr = new std::string[num];

        int j = -1;
        bool begin = false;

        std::string bufer = "";
        for (size_t i = 0 ; i < str.length(); i++)
        {
            if (str[i] != ' ')
            {
                if (!begin)
                {
                    j++;
                    begin = true;
                }
                bufer.append(1,str[i]);
            }
            else
                if (begin)
                {
                    newStr[j] = bufer;
                    bufer.clear();
                    begin = false;
                }
        }

        if (begin)
            newStr[j] = bufer;
        if (countWord != nullptr)
            *countWord = num;

        return newStr;
    }
    return nullptr;
}

FileInfoRecorder* MyApplication::connectFileLog(FileInfoRecorder* file)
{
    if (file != nullptr) {
        log.logList("connect", ACCEPT);
        this->connect(this, &MyApplication::update, file, &FileInfoRecorder::updateData);
        this->connect(file, &FileInfoRecorder::logedStatus, &log, &Loger::logFileUpdate);
    }
    return file;
}

FileInfoRecorder* MyApplication::disconnectFileLog(FileInfoRecorder* file)
{
    if (file != nullptr) {
        log.logList("disconnect", ACCEPT);
        this->disconnect(this, &MyApplication::update, file, &FileInfoRecorder::updateData);
        this->disconnect(file, &FileInfoRecorder::logedStatus, &log, &Loger::logFileUpdate);
    }
    return file;
}



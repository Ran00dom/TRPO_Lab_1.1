#include "myapplication.h"
#include <QDebug>
#include <cstring>

MyApplication::MyApplication(int argc, char*argv[]):QCoreApplication(argc,argv)
{
    timerID = startTimer(50); // запуск таймера консоли
}

void MyApplication::timerEvent(QTimerEvent* event)
{
    if (event->timerId() == timerID) // проверка id таймера
    {
        std::string str;
        std::getline(std::cin,str); // чтение из консоли
        listenCommand(str); // проверка ввода
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
                    if (manager.addFile(command[2].c_str()) == nullptr)
                        log.logList("File dont add!", ERRORS);
                    else
                        log.logList("File dont add!", ACCEPT);
                }
                else
                {
                    // not correct parth
                }

            case COMMAND_DROP:
                if (countWord > 1) {
                    // drop file
                }
                else
                {
                    // not correct parth
                }
            case COMMAND_LISTEN:
                if (countWord > 1) {
                    // listen file
                }
                else
                {
                    // not correct parth
                }
            case COMMAND_MUTE:
                if (countWord > 1) {
                    // mute file
                }
                else
                {
                    // not correct parth
                }
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

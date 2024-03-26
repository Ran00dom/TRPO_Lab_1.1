#include "myapplication.h"

Console& Console::Instance()
{
    static Console singleInstance;
    return singleInstance;
}

void Console::listenCommand()
{
    std::string s;
    std::getline(std::cin,s);
    QString df(s.c_str());
    emit commandInput(df);
};

//===============================================================================================//

MyApplication::MyApplication(int argc, char*argv[]):QCoreApplication(argc,argv)
{
    connect(&consoleThread, &QThread::started, &consol, &Console::listenCommand);
    connect(&consoleThread, &QThread::finished, &consol, &Console::deleteLater);

    connect(&consol, &Console::commandInput, this,&MyApplication::listenCommand);
    connect(this, &MyApplication::consoleListen, &consol, &Console::listenCommand);

    connect(this, &MyApplication::update, &manager, &FileManager::update);
    connect(&manager, &FileManager::logUpdate, &log, &Loger::logFileUpdate);

   //consolTimer = startTimer(50); // запуск таймера консоли
    log.logList("<< The program was created by Kiryushkin Yaroslav from the group 932122 >>");
    log.logList("Call list of commands /file help | to enable file update enter /file listen",WARNING);

    consol.moveToThread(&consoleThread);
    consoleThread.start();
}

void MyApplication::timerEvent(QTimerEvent* event)
{
        if (event->timerId() == listenTimer){
            emit update();
        }
        else
            QCoreApplication::timerEvent(event);
}

bool MyApplication::listenCommand(QString str) // определяет и выполняет команды
{
    if (!str.isEmpty()) //  строка не пустая
    {
        int countWord; // количество строк
        QString *command = spliter(str, &countWord); // разделяем троку на слова
        if (command[0] == "/file" && countWord > 1) { // проверяем ключивое слово и параметры за ним
            switch (commandCheck(command[1])) {  // поиск параметра по индексу

            case COMMAND_ADD: {
                if (countWord == 3) {
                    QString str(command[2]);
                    if (manager.addFile(str))
                        log.logList("file ADD successfully!", ACCEPT);
                    else
                        log.logList("file already ADD!", WARNING);
                    break;
                }
                log.logList("command not difined!", WARNING);
                break;
            }

            case COMMAND_DROP:{
                if (countWord == 3) {
                    QString str(command[2]);
                    bool isNumber;
                    int index = str.toInt(&isNumber);
                    if (isNumber)
                        if (manager.removeFile(index))
                            log.logList("file DROPPED successfully!", ACCEPT);
                        else
                            log.logList("file not FOUND!", WARNING);
                    else
                        if (manager.removeFile(str))
                            log.logList("file DROPPED successfully!", ACCEPT);
                        else
                            log.logList("file not FOUND!", WARNING);
                    break;
                }
                log.logList("command not difined!", WARNING);
                break;
            }

            case COMMAND_LISTEN:{ // запуск прослушивания
                if (countWord == 2) {
                    if (!listenFile) {
                        listenFile = true;
                        log.logList("Listen start!", ACCEPT);
                        listenTimer = startTimer(1000);
                    }
                    else
                        log.logList("Already listen!", WARNING);

                    break;
                }
                log.logList("command not difined!", WARNING);
                break;
            }

            case COMMAND_MUTE:{ // выключить прослушку
                if (countWord == 2) {
                    if (listenFile) {
                        listenFile = false;
                        log.logList("Mute listen!", ACCEPT);
                        killTimer(listenTimer);
                    }
                    else
                        log.logList("Already mute!", WARNING);
                    break;
                }
                log.logList("command not difined!", WARNING);
                break;
            }

            case COMMAND_HELP:{
                if (countWord == 2) {
                    log.logList("< COMMAND LIST >", MESSAGE);
                    log.logList("< every command starts with /file :>");
                    log.logList("| add [dir]          | adds a file along dir the path in the listening list");
                    log.logList("| drop [file name]   | deleting a file from the wiretap with the name [name]");
                    log.logList("| listen             | starts wiretapping if it is stopped");
                    log.logList("| mute               | stop wiretapping if it exists");
                    log.logList("| list               | force the states of all files to be displayed");
                    log.logList("| exit               | exit the application");
                    break;
                } 
                log.logList("command not difined!", WARNING);
                break;
            }

            case COMMAND_LIST:{
                if (countWord == 2) {
                    log.logList("<< FILE LIST >>", MESSAGE);
                    emit update(true);
                    break;
                }
                log.logList("command not difined!", WARNING);
                break;
            }

            case COMMAND_EXIT:{
                if (countWord == 2) {
                    consoleThread.quit();
                    this->exit();
                    log.logList("Program completed!", WARNING);
                    log.logList("< press any button >", INFO);
                    return true;
                }
                log.logList("command not difined!", WARNING);
                break;
            }

            break;
            default: // исключение
                log.logList("command not difined!", WARNING);
            }

        }
        else
            log.logList("command not difined!", WARNING);

        emit consoleListen();
        delete[] command;
        return false;
    }
    emit consoleListen();
    log.logList("command not difined!", WARNING);
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

int MyApplication::commandCheck(QString str) // проверка индекса ключевого слова
{
    for (int i = 0; i < numCommand; i++) {
        if (str == commands[i])
            return i;
    }
    return -1;
}

QString* MyApplication::spliter(QString str, int* countWord = nullptr) // деление строки по пробелам
{
    if (!str.isEmpty())
    {
        int num = std::count(str.begin(),str.end(), ' ')+1;

        QString *newStr = new QString[num];
        int j = -1;
        bool begin = false;

        QString bufer = "";
        for (int i = 0 ; i < str.length(); i++){
            if (str.at(i) != ' '){
                if (!begin){
                    j++;
                    begin = true;
                }
                bufer.append(str.at(i));
            }
            else
                if (begin){
                    newStr[j] = bufer;
                    bufer.clear();
                    begin = false;
                }
        }

        if (begin)
            newStr[j] = bufer;

        int newString = j + 1;
        QString* command = new QString[newString]; // новый массив
        for (int var = 0; var < newString; var++) {
            command[var] =  newStr[var];
        }

        delete[] newStr;
        if (countWord != nullptr)
            *countWord = newString;

        return command;
    }
    return nullptr;
}





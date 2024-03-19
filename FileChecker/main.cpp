#include "myapplication.h"
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "Russian");
    MyApplication a(argc, argv);

    return a.exec();
}

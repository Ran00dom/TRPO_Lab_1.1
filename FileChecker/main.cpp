#include "myapplication.h"
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    MyApplication a(argc, argv);

    return a.exec();
}

#include "loger.h"
#include <QDebug>

void Loger::logFileUpdate(QFileInfo* file)
{
    if (file->exists())
        qDebug() << file->baseName() << "STATUS / exist? " << file->exists() << " / size?  " << file->size() << ;

}

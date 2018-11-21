#include <QSqlDatabase>
#include <QMutexLocker>

#include "qtdbxml.h"

QMutex QtDbXml::constMutex;
QtDbXml *QtDbXml::myInstance = nullptr;

QtDbXml::QtDbXml(QString driver,QString host,QString dbname,QString uname,QString passwd)
{
}

QtDbXml *QtDbXml::instance()
{
    if (myInstance)
        return myInstance;
    QMutexLocker l(&constMutex);
    if (myInstance)
        return myInstance;
    if (!init())
        return nullptr;
    return myInstance;
}

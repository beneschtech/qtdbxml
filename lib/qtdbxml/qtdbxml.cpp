#include <QSqlDatabase>
#include <QMutexLocker>
#include <QSqlError>
#include <QJsonDocument>
#include <QJsonObject>

#include "qtdbxml.h"

QMutex QtDbXml::constMutex;
QtDbXml *QtDbXml::myInstance = nullptr;

QtDbXml::QtDbXml(QString driver,QString host,QString dbname,QString uname,QString passwd):
    dbDriver(driver),
    dbHost(host),
    dbName(dbname),
    dbUname(uname),
    dbPasswd(passwd)
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

bool QtDbXml::init(QString driver, QString host, QString dbname, QString uname, QString passwd)
{
    if (myInstance)
        return false;
    QMutexLocker l(&constMutex);
    if (myInstance)
        return false;
    myInstance = new QtDbXml(driver,host,dbname,uname,passwd);
    return true;
}

bool QtDbXml::init()
{
    if (myInstance)
        return false;
    QMutexLocker l(&constMutex);
    if (myInstance)
        return false;
    if (!getenv("XMLCONFIG")) return false;
    QByteArray ba = QByteArray::fromBase64(getenv("XMLCONFIG"));
    QJsonObject obj = QJsonDocument::fromJson(ba).object();

}

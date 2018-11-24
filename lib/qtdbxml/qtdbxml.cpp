#include <iostream>
#include <QSqlDatabase>
#include <QMutexLocker>
#include <QSqlError>
#include <QJsonDocument>
#include <QJsonObject>

#include "qtdbxml.h"

QMutex QtDbXml::constMutex;
QtDbXml *QtDbXml::myInstance = nullptr;

QtDbXml::QtDbXml(QString driver,QString host,QString dbname,QString uname,QString passwd):
    myIsConnected(false),
    dbDriver(driver),
    dbHost(host),
    dbName(dbname),
    dbUname(uname),
    dbPasswd(passwd)
{
    myIsConnected = connect();
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
    return myInstance->isConnected();
}

bool QtDbXml::init()
{
    if (myInstance)
        return false;
    QMutexLocker l(&constMutex);
    if (myInstance)
        return false;
    if (!getenv("XMLCONFIG")) return false;
    QJsonParseError pe;
    QJsonDocument doc(QJsonDocument::fromJson(QByteArray::fromBase64(getenv("XMLCONFIG")),&pe));
    if (doc.isNull())
    {
        std::cerr << pe.errorString().toStdString() << std::endl;
        return false;
    }
    QJsonObject obj = doc.object();
    myInstance = new QtDbXml(obj["driver"].toString(),obj["host"].toString(),
            obj["name"].toString(),obj["user"].toString(),obj["pass"].toString());
    return myInstance->isConnected();
}

bool QtDbXml::connect()
{
    myDBHandle = QSqlDatabase::addDatabase(dbDriver,QTDBXMLDBNAME);
    myDBHandle.setDatabaseName(dbName);
    myDBHandle.setUserName(dbUname);
    if (!dbHost.isEmpty())
        myDBHandle.setHostName(dbHost);
    if (!dbPasswd.isEmpty())
        myDBHandle.setPassword(dbPasswd);
    if (!myDBHandle.open())
    {
        std::cerr << myDBHandle.lastError().text().toStdString() << std::endl;
        return false;
    }
    origThread = QThread::currentThread();
    return true;
}

void QtDbXml::threadEnded()
{

}

QSqlDatabase QtDbXml::connection()
{
    return myDBHandle;
}

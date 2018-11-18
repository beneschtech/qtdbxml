#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QFile>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonDocument>

#include <version.h>

#include "qtxmlconfig.h"

QTXmlConfig::QTXmlConfig(int &argc, char **argv)
    :QCoreApplication(argc,argv)
{
    QTimer::singleShot(0,this,SLOT(startup()));
    dbDriver = "QPSQL";
}

void QTXmlConfig::startup()
{
    if (!parseArgs())
    {
        exit(1);
        return;
    }
    if (!validateDBSettings())
    {
        exit(1);
        return;
    }
    QJsonObject o;
    o["driver"] = QJsonValue(dbDriver);
    o["user"] = QJsonValue(dbUser);
    o["name"] = QJsonValue(dbName);
    if (dbHost.length())
        o["host"] = QJsonValue(dbHost);
    if (dbPasswd.length())
        o["passwd"] = QJsonValue(dbPasswd);
    QJsonDocument doc(o);
    std::cout << "XMLCONFIG=\"" << doc.toJson(QJsonDocument::Compact).toBase64().data() << "\"" << std::endl;
    quit();
}

bool QTXmlConfig::parseArgs()
{
    QCommandLineParser p;
    setApplicationName("qtxmlconfig");
    setApplicationVersion(VERSIONSTR);
    p.addVersionOption();
    p.addOptions({
        {{"H","host"},"H","host"},
        {{"d","dbname"},"d","dbname"},
        {{"u","user"},"u","user"},
        {{"p","pass"},"p","pass"},
        {{"D","driver"},"D","driver"},
        {{"h","help"},"" }
                 });
    const QStringList args = arguments();
    p.process(args);
    if (p.isSet("h"))
    {
        usage();
        quick_exit(0);
    }
    if (p.isSet("H"))
    {
        dbHost = p.value("H");
    }
    if (p.isSet("d"))
    {
        dbName = p.value("d");
    }
    if (p.isSet("u"))
    {
        dbUser = p.value("u");
    }
    if (p.isSet("p"))
    {
        dbPasswd = p.value("p");
    }
    if (p.isSet("D"))
    {
        dbDriver = validateDriver(p.value("D"));
    }
    if (!dbDriver.length() || !dbUser.length() || !dbName.length())
    {
        usage();
        return false;
    }
    return true;
}

QString QTXmlConfig::validateDriver(QString d)
{
    QStringList drvs = QSqlDatabase::drivers();
    if (drvs.contains(d))
        return d;

    std::cout << "Driver " << d.toStdString() << " not found" << std::endl;
    std::cout << "\nAvailable drivers:" << std::endl;
    foreach (QString drv,drvs)
    {
        std::cout << drv.toStdString() << std::endl;
    }
    return QString();
}

void QTXmlConfig::usage()
{
    QFile f(":/help.txt");
    f.open(QIODevice::ReadOnly);
    std::cout << f.readAll().data() << std::endl;
    f.close();
}

bool QTXmlConfig::validateDBSettings()
{
    QSqlDatabase db = QSqlDatabase::addDatabase(dbDriver);
    db.setDatabaseName(dbName);
    db.setUserName(dbUser);
    if (dbHost.length())
        db.setHostName(dbHost);
    if (dbPasswd.length())
        db.setPassword(dbPasswd);

    if (!db.open())
    {
        std::cerr << db.lastError().text().toStdString() << std::endl;
        return false;
    }
    QSqlQuery q(db);
    if (!q.prepare("SELECT * FROM xmlconfig_data WHERE parent = ?"))
    {
        std::cerr << q.lastError().text().toStdString() << std::endl;
        return false;
    }
    return true;
}

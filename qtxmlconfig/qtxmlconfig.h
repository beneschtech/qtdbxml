#ifndef QTXMLCONFIG_H
#define QTXMLCONFIG_H

#include <iostream>
#include <QObject>
#include <QTimer>
#include <QCoreApplication>

class QTXmlConfig : public QCoreApplication
{
    Q_OBJECT

public:
    QTXmlConfig(int &argc,char **argv);

public slots:
    void startup();

private:
    bool parseArgs();
    QString validateDriver(QString);
    void usage();
    bool validateDBSettings();

    QString dbDriver;
    QString dbUser;
    QString dbPasswd;
    QString dbHost;
    QString dbName;
};

#endif // QTXMLCONFIG_H

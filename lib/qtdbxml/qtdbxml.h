#ifndef QTDBXML_H
#define QTDBXML_H
#include <QMutex>

class QtDbXml
{
public:
    static bool init();
    static bool init(QString driver,QString host,QString dbname,QString uname,QString passwd=QString());
    static QtDbXml *instance();

private:
    Q_DISABLE_COPY
    QtDbXml(QString driver,QString host,QString dbname,QString uname,QString passwd);
    QString dbHost;
    QString dbDriver;
    QString dbUname;
    QString dbName;
    QString dbPasswd;

    static QMutex constMutex;
    static QtDbXml *myInstance;
};

#endif // QTDBXML_H

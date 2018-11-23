#ifndef QTDBXML_H
#define QTDBXML_H
#include <QMutex>
#include <QString>
#include <QSqlDatabase>

class QtDbXml
{
public:
    static bool init();
    static bool init(QString driver,QString host,QString dbname,QString uname,QString passwd=QString());
    static QtDbXml *instance();

private:
    Q_DISABLE_COPY(QtDbXml)
    QtDbXml(QString driver,QString host,QString dbname,QString uname,QString passwd);
    QString dbDriver;
    QString dbHost;
    QString dbName;
    QString dbUname;
    QString dbPasswd;

    static QMutex constMutex;
    static QtDbXml *myInstance;
};

#endif // QTDBXML_H

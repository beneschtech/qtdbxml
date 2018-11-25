#ifndef QTDBXML_H
#define QTDBXML_H
#include <QMutex>
#include <QString>
#include <QSqlDatabase>
#include <QThread>
#include <QMap>
#include <QObject>
#include <QDomDocument>

#include "dbdomdocument.h"

#define QTDBXMLDBNAME "QTDBXML"

class QtDbXml: public QObject
{
    Q_OBJECT

public:
    static bool init();
    static bool init(QString driver,QString host,QString dbname,QString uname,QString passwd=QString());
    static QtDbXml *instance();

    bool isConnected() { return myIsConnected; }
    DBDomDocument documentFromName(QString,unsigned revId = 0);

    enum DataType {
        NONE = -1,
        NODE = 0,
        ELEMENT = 1,
        ATTRIBUTE = 2,
        TEXT = 3
    };
private slots:
    void threadEnded();

private:
    Q_DISABLE_COPY(QtDbXml)
    QtDbXml(QString driver,QString host,QString dbname,QString uname,QString passwd);
    bool connect();
    QSqlDatabase connection();
    void documentRecursive(QDomDocument *,QDomElement *,QSqlQuery *parentCur,QSqlQuery *idCur,QSqlQuery *bigCur,long long id,unsigned revision,unsigned *maxRev);

    bool myIsConnected;
    QSqlDatabase myDBHandle;
    QThread *origThread;
    QString dbDriver;
    QString dbHost;
    QString dbName;
    QString dbUname;
    QString dbPasswd;
    QMap<QThread *,QSqlDatabase> threadMap;
    static QMutex constMutex;
    static QtDbXml *myInstance;
};

#endif // QTDBXML_H

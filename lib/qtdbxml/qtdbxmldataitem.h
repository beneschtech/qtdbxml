#ifndef QTDBXMLDATAITEM_H
#define QTDBXMLDATAITEM_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

class QtDBXmlDataItem
{
public:
    QtDBXmlDataItem(QSqlQuery *idCur,QSqlQuery *bigData,long long dbid,unsigned dbrevision);
    long long id;
    int type;
    long long parent;
    int order;
    QString name;
    QByteArray data;
    unsigned revision;
    long long last_rev_id;
};

#endif // QTDBXMLDATAITEM_H

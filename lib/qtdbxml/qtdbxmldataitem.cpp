#include <QVariant>
#include "qtdbxmldataitem.h"

QtDBXmlDataItem::QtDBXmlDataItem(QSqlQuery *idCur, QSqlQuery *bigCur, long long dbid, unsigned dbrevision)
{
    id = -1;
    type = -1;
    parent = -1;
    order = -1;
    name.clear();
    data.clear();
    revision = 0;
    last_rev_id = -1;

    bool revfound = false;
    while (!revfound)
    {
        idCur->addBindValue(QVariant(dbid));
        idCur->exec();
        if (!idCur->next())
            return;
        revision = idCur->value("revision").toUInt();
        last_rev_id = idCur->value("lastrev_id").toLongLong();
        if (revision <= dbrevision || dbrevision == 0)
        {
            revfound = true;
        } else {
            idCur->finish();
            dbid = last_rev_id;
        }
    }
    id = idCur->value("id").toLongLong();
    type = idCur->value("type").toInt();
    parent = idCur->value("parent").toLongLong();
    order = idCur->value("order").toInt();
    name = idCur->value("name").toString();
    if (name == "@BIGDATA")
    {
        bigCur->addBindValue(QVariant(id));
        bigCur->exec();
        bigCur->next();
        data = bigCur->value("data").toByteArray();
        bigCur->finish();
    } else {
        data = idCur->value("data").toByteArray();
    }

    idCur->finish();
}

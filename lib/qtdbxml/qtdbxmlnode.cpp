#include <iostream>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QVariant>
#include <QVector>
#include <QDomElement>

#include "qtdbxml.h"
#include "qtdbxmldataitem.h"

DBDomDocument QtDbXml::documentFromName(QString nm, unsigned revision)
{
    QDomDocument rv;

    if (!isConnected())
        return DBDomDocument();
    QSqlQuery findDocument(connection());
    QString sql = QString("SELECT * FROM xmlconfig_data WHERE type = 0 AND parent = 0 AND \"order\" = 0 AND name = ?");
    if (!findDocument.prepare(sql))
    {
        std::cerr << findDocument.lastError().text().toStdString() << std::endl;
        return DBDomDocument();
    }
    findDocument.addBindValue(QVariant(nm));
    if (!findDocument.exec())
    {
        std::cerr << findDocument.lastError().text().toStdString() << std::endl;
        return DBDomDocument();
    }
    if (!findDocument.next())
        return DBDomDocument();

    QSqlQuery parentCur(connection());
    QSqlQuery idCur(connection());
    QSqlQuery bigCur(connection());
    sql = "SELECT id FROM xmlconfig_data WHERE parent = ? ORDER BY \"order\"";
    if (!parentCur.prepare(sql))
    {
        std::cerr << parentCur.lastError().text().toStdString() << std::endl;
        return DBDomDocument();
    }
    sql = "SELECT * FROM xmlconfig_data WHERE id = ?";
    if (!idCur.prepare(sql))
    {
        std::cerr << idCur.lastError().text().toStdString() << std::endl;
        return DBDomDocument();
    }
    sql = "SELECT xmldata_id AS id,data FROM xmlconfig_bigdata WHERE xmldata_id = ?";
    if (!bigCur.prepare(sql))
    {
        std::cerr << bigCur.lastError().text().toStdString() << std::endl;
        return DBDomDocument();
    }
    unsigned maxRev = 0;
    documentRecursive(&rv,nullptr,&parentCur,&idCur,&bigCur,findDocument.value("id").toLongLong(),revision,&maxRev);
    findDocument.finish();
    return DBDomDocument(rv,maxRev);
}

void QtDbXml::documentRecursive(QDomDocument *doc, QDomElement *el, QSqlQuery *parentCur, QSqlQuery *idCur, QSqlQuery *bigCur, long long id, unsigned revision, unsigned *maxRev)
{
    parentCur->addBindValue(QVariant(id));
    parentCur->exec();
    QVector<long long> ids;
    while (parentCur->next())
    {
        ids.append(parentCur->value(0).toLongLong());
    }
    parentCur->finish();
    foreach (long long elid,ids)
    {        
        QtDBXmlDataItem itm(idCur,bigCur,elid,revision);
        if (itm.revision > *maxRev)
            *maxRev = itm.revision;
        switch (itm.type)
        {
        case NONE:
            continue;

        case ELEMENT:
        {
            QDomElement e = doc->createElement(itm.name);
            if (el)
            {
                el->appendChild(e);
            } else {
                doc->appendChild(e);
            }
            idCur->finish();
            documentRecursive(doc,&e,parentCur,idCur,bigCur,itm.id,revision,maxRev);
            break;
        }

        case ATTRIBUTE:
        {
            el->setAttribute(itm.name,QString(itm.data));
            idCur->finish();
            break;
        }

        case TEXT:
        {
            el->appendChild(doc->createTextNode(itm.data));
            idCur->finish();
            break;
        }

        default:
            std::cerr << "Type: " << idCur->value("type").toInt() << " not handled" << std::endl;
        }
    }
}

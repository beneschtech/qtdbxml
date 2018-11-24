#include <iostream>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QVariant>
#include <QVector>
#include <QDomElement>

#include "qtdbxml.h"
#include "qtdbxmldataitem.h"

QDomDocument QtDbXml::documentFromName(QString nm, unsigned revision)
{
    QDomDocument rv;

    if (!isConnected())
        return rv;
    QSqlQuery findDocument(connection());
    QString sql = QString("SELECT * FROM xmlconfig_data WHERE type = 0 AND parent = 0 AND \"order\" = 0 AND name = ?");
    if (!findDocument.prepare(sql))
    {
        std::cerr << findDocument.lastError().text().toStdString() << std::endl;
        return rv;
    }
    findDocument.addBindValue(QVariant(nm));
    if (!findDocument.exec())
    {
        std::cerr << findDocument.lastError().text().toStdString() << std::endl;
        return rv;
    }
    if (!findDocument.next())
        return rv;

    QSqlQuery parentCur(connection());
    QSqlQuery idCur(connection());
    QSqlQuery bigCur(connection());
    sql = "SELECT id FROM xmlconfig_data WHERE parent = ? ORDER BY \"order\"";
    if (!parentCur.prepare(sql))
    {
        std::cerr << parentCur.lastError().text().toStdString() << std::endl;
        return rv;
    }
    sql = "SELECT * FROM xmlconfig_data WHERE id = ?";
    if (!idCur.prepare(sql))
    {
        std::cerr << idCur.lastError().text().toStdString() << std::endl;
        return rv;
    }
    sql = "SELECT xmldata_id AS id,data FROM xmlconfig_bigdata WHERE xmldata_id = ?";
    if (!bigCur.prepare(sql))
    {
        std::cerr << bigCur.lastError().text().toStdString() << std::endl;
        return rv;
    }
    documentRecursive(&rv,nullptr,&parentCur,&idCur,&bigCur,findDocument.value("id").toLongLong(),revision);
    findDocument.finish();
    savedDocs[nm] = rv.documentElement().cloneNode().toElement();
    return rv;
}

void QtDbXml::documentRecursive(QDomDocument *doc, QDomElement *el, QSqlQuery *parentCur, QSqlQuery *idCur, QSqlQuery *bigCur, long id, unsigned revision)
{
    parentCur->addBindValue(QVariant((long long)id));
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
        switch (itm.type)
        {
        case NONE:
            continue;
            break;

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
            documentRecursive(doc,&e,parentCur,idCur,bigCur,itm.id,revision);
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

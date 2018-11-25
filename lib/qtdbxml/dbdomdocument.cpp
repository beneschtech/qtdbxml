#include <QTextStream>
#include "dbdomdocument.h"

DBDomDocument::DBDomDocument(QDomDocument doc,unsigned rev)
{
    workingDoc = doc.documentElement();
    backupDoc = workingDoc.cloneNode().toElement();
    myRevision = rev;
    myNull = !workingDoc.isElement();
}

bool DBDomDocument::saveDocument(QString)
{
    return false;
}

QString DBDomDocument::toString()
{
    QString rs;
    QTextStream str(&rs);
    workingDoc.save(str,1);
    return rs;
}

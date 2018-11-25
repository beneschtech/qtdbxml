#ifndef DBDOMDOCUMENT_H
#define DBDOMDOCUMENT_H

#include <QDomDocument>
#include <QDomElement>
#include <QString>

class DBDomDocument
{
public:
    DBDomDocument(): myRevision(0),myNull(true) {}
    DBDomDocument(QDomDocument, unsigned rev);
    QDomElement element() { return workingDoc; }
    bool saveDocument(QString);
    unsigned int revision() const { return myRevision; }
    bool isNull() const { return myNull; }
    QString toString();

private:
    QDomElement workingDoc;
    QDomElement backupDoc;
    unsigned int myRevision;
    bool myNull;
};

#endif // DBDOMDOCUMENT_H

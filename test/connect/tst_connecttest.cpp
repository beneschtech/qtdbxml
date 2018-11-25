#include <QString>
#include <QtTest>
#include <qtdbxml.h>
#include <iostream>

class ConnectTest : public QObject
{
    Q_OBJECT

public:
    ConnectTest();

private Q_SLOTS:
    void testConnection();
    void testDOM();
    void testRevision();
};

ConnectTest::ConnectTest()
{
}

void ConnectTest::testConnection()
{
    QVERIFY(QtDbXml::init());
    QVERIFY(QtDbXml::instance() != nullptr);
    QVERIFY(QtDbXml::instance()->isConnected());
}

void ConnectTest::testDOM()
{
    DBDomDocument d = QtDbXml::instance()->documentFromName("_test_xml",0);
    QVERIFY(!d.isNull());
    std::cout << "\nDocument string:\n" << d.toString().toStdString() << std::endl;
    std::cout << "Document revision: " << d.revision() << std::endl;
}

void ConnectTest::testRevision()
{
    QString curRev = QtDbXml::instance()->documentFromName("_test_xml",0).toString();
    QString fRev = QtDbXml::instance()->documentFromName("_test_xml",1).toString();

    QVERIFY(curRev != fRev);
}
QTEST_APPLESS_MAIN(ConnectTest)

#include "tst_connecttest.moc"

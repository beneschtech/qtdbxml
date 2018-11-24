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
    void environConnect();
    void isConnected();
    void getTestDOM();
};

ConnectTest::ConnectTest()
{
}

void ConnectTest::environConnect()
{
    QVERIFY(QtDbXml::init());
}

void ConnectTest::isConnected()
{
    QVERIFY(QtDbXml::instance() != nullptr);
    QVERIFY(QtDbXml::instance()->isConnected());
}

void ConnectTest::getTestDOM()
{
    QDomDocument d = QtDbXml::instance()->documentFromName("_test_xml",1);
    QVERIFY(d.documentElement().isElement());
    std::cout << "\n\nDocument string:\n" << d.toString().toStdString() << "\n\n" << std::endl;
}
QTEST_APPLESS_MAIN(ConnectTest)

#include "tst_connecttest.moc"

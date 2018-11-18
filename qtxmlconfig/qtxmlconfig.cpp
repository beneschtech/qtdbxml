#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QSqlDatabase>
#include <QFile>
#include <version.h>

#include "qtxmlconfig.h"

QTXmlConfig::QTXmlConfig(int &argc, char **argv)
    :QCoreApplication(argc,argv)
{
    myTimer = new QTimer();
    myTimer->setSingleShot(true);
    myTimer->setInterval(0);
    connect(myTimer,SIGNAL(timeout()),this,SLOT(startup()));
    myTimer->start();
}

void QTXmlConfig::startup()
{
    QCommandLineParser p;
    setApplicationName("qtxmlconfig");
    setApplicationVersion(VERSIONSTR);
    p.addVersionOption();
    p.addOptions({
        {{"h","help"},"" }
                 });
    const QStringList args = arguments();
    p.process(args);
    if (p.isSet("h"))
    {
        QFile f(":/help.txt");
        f.open(QIODevice::ReadOnly);
        std::cout << f.readAll().data() << std::endl;
        f.close();
        quick_exit(0);
    }
}

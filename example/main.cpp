#include <QApplication>
#include <QQmlApplicationEngine>

#include <QMLThreadProxy.h>
#include "CopyClass.h"


#include <QtQml>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("Proxy", new QMLThreadProxy<CopyClass>);
    engine.rootContext()->setContextProperty("CopyClass", new CopyClass);
    engine.load(QUrl(QStringLiteral("qrc:///main.qml")));

    return app.exec();
}

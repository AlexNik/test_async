#include <QApplication>
#include <QQmlApplicationEngine>

#include "ScreenShot.h"
#include "QMLThreadProxy.h"

#include <QtQml>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("SCProxy", new QMLThreadProxy<Screenshot>);
    engine.load(QUrl(QStringLiteral("qrc:///main.qml")));



    return app.exec();
}

#include <QApplication>
#include <QQmlApplicationEngine>

#include "ScreenShotProxy.h"

#include <QtQml>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("SCProxy", new ScreenShotProxy<Screenshot>);
    engine.load(QUrl(QStringLiteral("qrc:///main.qml")));



    return app.exec();
}

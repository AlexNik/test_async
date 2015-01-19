#include <QApplication>
#include <QQmlApplicationEngine>

#include "ScreenShotProxy.h"
#include "QMLThread.h"

#include <QtQml>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qmlRegisterType<ScreenShotProxy>("ScreenShotLib", 1, 0, "ScreenShotProxy");

    qmlRegisterType<QMLThread>("ScreenShotLib", 1, 0, "QMLThread");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:///main.qml")));

    return app.exec();
}

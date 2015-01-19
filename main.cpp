#include <QApplication>
#include <QQmlApplicationEngine>

#include "ScreenShotProxy.h"

#include <QtQml>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);


    qmlRegisterType<Screenshot>("ScreenshotLib", 1, 1, "Screenshot");
    qmlRegisterType<ScreenShotProxy>("ScreenshotLib", 1, 1, "ScreenShotProxy");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:///main.qml")));

    return app.exec();
}

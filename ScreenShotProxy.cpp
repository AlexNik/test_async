#include "ScreenShotProxy.h"

#include <QStringList>
#include <QDebug>

//#include <Qti

ScreenShotProxy::ScreenShotProxy(QObject *parent):
    Screenshot(parent)
{
    m_screenShot = new Screenshot;
    m_thread = new QThread;

    QStringList parentSignals, qobjectsignals, qobjectslots, parentslots;

    qobjectsignals = getMetha(QObject(), QMetaMethod::Signal);
    parentSignals = getMetha(Screenshot(), QMetaMethod::Signal);
    qobjectslots = getMetha(QObject(), QMetaMethod::Slot);
    parentslots = getMetha(Screenshot(), QMetaMethod::Slot);
    qDebug() << qobjectsignals;
    qDebug() << parentSignals;
    qDebug() << parentslots;


    foreach (const QString &str, parentSignals) {
        if (qobjectsignals.contains(str))
            continue;

        qDebug() << QObject::connect(m_screenShot, QString("2" + str).toLocal8Bit().data(), qFlagLocation(QString("2" + str).toLocal8Bit().data()))
                 << QString("2" + str).toLocal8Bit().data();

    }

    foreach (QString str, parentslots) {
        if (qobjectslots.contains(str))
            continue;

        if (!str.contains(QRegExp("^on"))) {
            continue;
        }

        QString slot = str;
        QString signal = str.replace(0, 3, str.at(2).toLower());

        if (!parentSignals.contains(signal)) {
            qDebug() << "???";
            continue;
        }

        QObject::connect(this, qFlagLocation(QString("2" + signal).toLocal8Bit().data()),
                         m_screenShot, qFlagLocation(QString("1" + slot).toLocal8Bit().data()));
    }


    m_screenShot->moveToThread(m_thread);
    m_thread->start();
}

ScreenShotProxy::~ScreenShotProxy()
{
    m_thread->quit();
    m_thread->wait();

    delete m_thread;
    delete m_screenShot;
}

//void ScreenShotProxy::takeScreenshot()
//{
//    QMetaObject::invokeMethod(m_screenShot, QString(__FUNCTION__).split("::").at(1).toLocal8Bit().data());
//}

QStringList ScreenShotProxy::getMetha(const QObject &obj, QMetaMethod::MethodType type)
{
    QStringList signalsList;
    const QMetaObject *metaObj = obj.metaObject();

    for (int i = 0; i < metaObj->methodCount(); i++) {
        if (metaObj->method(i).methodType() == type) {
            signalsList.append(metaObj->method(i).methodSignature());
        }

        //        if (metaObj->method(i).methodType() == QMetaMethod::Slot) {
        //            qDebug() << metaObj->method(i).tag();
        //        }
    }

    return signalsList;
}

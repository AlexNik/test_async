#include "ScreenShotProxy.h"

#include <QStringList>
#include <QDebug>

//#include <Qti

void ScreenShotProxy::stop()
{
    m_screenShot->setContinue(false);
}

ScreenShotProxy::ScreenShotProxy(QObject *parent):
    ScreenshotInterface(parent)
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

        qDebug() << "signals" << QObject::connect(m_screenShot, QString("2" + str).toLocal8Bit().data(), qFlagLocation(QString("2" + str).toLocal8Bit().data()))
                 << QString("2" + str);

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
            //qDebug() << "???";
            continue;
        }

        qDebug() << "slots" << QObject::connect(this, qFlagLocation(QString("2" + signal).toLocal8Bit().data()),
                         m_screenShot, qFlagLocation(QString("1" + slot).toLocal8Bit().data())) <<
                    QString("2" + signal) << "to" << QString("1" + slot);
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

void ScreenShotProxy::setName(const QString name)
{
    QMetaObject::invokeMethod(m_screenShot, QString(__FUNCTION__).split("::").at(1).toLocal8Bit().data(), Q_ARG(QString, name));
}

void ScreenShotProxy::setRect(QRect rect)
{
    // TODO: sync
    m_screenShot->setRect(rect);

    //QMetaObject::invokeMethod(m_screenShot, QString(__FUNCTION__).split("::").at(1).toLocal8Bit().data(), Q_ARG(QRect, rect));
}

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

#include "ScreenShotProxy.h"

#include <QStringList>
#include <QDebug>

#include <QMetaObject>

#if (QT_VERSION < QT_VERSION_CHECK(5, 0, 0))
    #define METASTRING(x) x->d.stringdata
#else
    #define METASTRING(x) ((char*)x->d.stringdata->data())
#endif

void ScreenShotProxy::stop()
{
    m_screenShot->setContinue(false);
}

ScreenShotProxy::ScreenShotProxy(QObject *parent):
    QObject(parent)
{
    m_screenShot = new Screenshot;
    m_thread = new QThread;

    QStringList parentSignals, qobjectsignals, qobjectslots, parentslots;

    qobjectsignals = getMetha(QObject(), QMetaMethod::Signal);
    parentSignals = getMetha(Screenshot(), QMetaMethod::Signal);
    qobjectslots = getMetha(QObject(), QMetaMethod::Slot);
    parentslots = getMetha(Screenshot(), QMetaMethod::Slot);

//    qDebug() << qobjectsignals;
//    qDebug() << parentSignals;
//    qDebug() << parentslots;


    foreach (const QString &str, parentSignals) {
        if (qobjectsignals.contains(str))
            continue;

        QObject::connect(m_screenShot, QString("2" + str).toLocal8Bit().data(), qFlagLocation(QString("2" + str).toLocal8Bit().data()));

        //qDebug() << "signals" << QString("2" + str);

    }

//    foreach (QString str, parentslots) {
//        if (qobjectslots.contains(str))
//            continue;

//        if (!str.contains(QRegExp("^on"))) {
//            continue;
//        }

//        QString slot = str;
//        QString signal = str.replace(0, 3, str.at(2).toLower());

//        if (!parentSignals.contains(signal)) {
//            //qDebug() << "???";
//            continue;
//        }

//        qDebug() << "slots" << QObject::connect(this, qFlagLocation(QString("2" + signal).toLocal8Bit().data()),
//                         m_screenShot, qFlagLocation(QString("1" + slot).toLocal8Bit().data())) <<
//                    QString("2" + signal) << "to" << QString("1" + slot);
//    }


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

void ScreenShotProxy::takeScreenshot()
{
    QMetaObject::invokeMethod(m_screenShot, QString(__FUNCTION__).split("::").at(1).toLocal8Bit().data());
}

QStringList ScreenShotProxy::getMetha(const QObject &obj, QMetaMethod::MethodType type)
{
    QStringList signalsList;
    const QMetaObject *metaObj = obj.metaObject();

    for (int i = 0; i < metaObj->methodCount(); i++) {
        if (metaObj->method(i).methodType() == type) {
            signalsList.append(metaObj->method(i).methodSignature());
        }
    }

    return signalsList;
}


const QMetaObject *ScreenShotProxy::metaObject() const
{
    qDebug() << m_screenShot->metaObject();
    return m_screenShot->metaObject();
}

void *ScreenShotProxy::qt_metacast(const char *clname)
{
    return m_screenShot->qt_metacast(clname);
}

int ScreenShotProxy::qt_metacall(QMetaObject::Call call, int id, void **arg)
{
    const QMetaObject *mobj = m_screenShot->metaObject();
    QMetaMethod method = mobj->method(id);

    QByteArrayList args = method.parameterTypes();
    QGenericArgument genArgs[10];


    for (int i = 0; i < args.count(); i++) {
        QGenericArgument ga(args.at(i), arg[i]);
        genArgs[i] = ga;
    }

    bool ok = method.invoke(m_screenShot, genArgs[0], genArgs[1], genArgs[2], genArgs[3], genArgs[4], genArgs[5], genArgs[6],
             genArgs[7], genArgs[8], genArgs[9]);

    return 1;
}

#include "ScreenShotProxy.h"

#include <QStringList>
#include <QDebug>

#include <QMetaObject>
#include <QList>
#include <QByteArray>

ScreenShotProxy::ScreenShotProxy(QObject *parent):
    QObject(parent)
{
    m_screenShot = new Screenshot;
    m_thread = new QThread;

    const QMetaObject* metaObject = m_screenShot->metaObject();

    for (int i = 0; i < metaObject->methodCount(); i++) {
        if (metaObject->method(i).methodType() == QMetaMethod::Signal) {
            QString x =  metaObject->method(i).methodSignature();
            QObject::connect(m_screenShot, qFlagLocation(QString("2" + x).toLocal8Bit().data()), this, qFlagLocation(QString("2" + x).toLocal8Bit().data()));
        }
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

const QMetaObject *ScreenShotProxy::metaObject() const
{
    return m_screenShot->metaObject();
}

void *ScreenShotProxy::qt_metacast(const char *clname)
{
    return m_screenShot->qt_metacast(clname);
}

int ScreenShotProxy::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    if (_c != QMetaObject::InvokeMetaMethod) {
        int id = m_screenShot->qt_metacall(_c, _id, _a);
        if (id < 0)
            return id;
    }

    QMetaMethod method = m_screenShot->metaObject()->method(_id);
    QList<QByteArray> args = method.parameterTypes();
    QGenericArgument genArgs[10];
    for (int i = 0; i < args.count(); i++) {
        QGenericArgument ga(args.at(i), _a[i + 1]);
        genArgs[i] = ga;
    }

    method.invoke(m_screenShot, genArgs[0], genArgs[1], genArgs[2], genArgs[3], genArgs[4], genArgs[5], genArgs[6],
            genArgs[7], genArgs[8], genArgs[9]);

    return _id;
}

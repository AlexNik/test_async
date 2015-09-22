#ifndef QMLTHREADPROXY_H
#define QMLTHREADPROXY_H

#include <QThread>
#include <QMetaMethod>


template <class  T>
class QMLThreadProxy: public QObject
{
    Q_OBJECT_CHECK
    QT_TR_FUNCTIONS

public:
    QMLThreadProxy(QObject *parent = 0):
        QObject(parent)
    {
        m_screenShot = new T;
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

    ~QMLThreadProxy()
    {
        m_thread->quit();
        m_thread->wait();

        delete m_thread;
        delete m_screenShot;
    }

    const QMetaObject *metaObject() const
    {
        return m_screenShot->metaObject();
    }

    void *qt_metacast(const char *clname)
    {
        return m_screenShot->qt_metacast(clname);
    }

    int qt_metacall(QMetaObject::Call call, int id, void **args)
    {
        if (call != QMetaObject::InvokeMetaMethod) {
            int tmpId = m_screenShot->qt_metacall(call, id, args);
            if (tmpId < 0)
                return tmpId;
        }

        QMetaMethod method = m_screenShot->metaObject()->method(id);
        QList<QByteArray> argsList = method.parameterTypes();
        QGenericArgument genArgs[10];
        for (int i = 0; i < argsList.count(); i++) {
            QGenericArgument ga(argsList.at(i), args[i + 1]);
            genArgs[i] = ga;
        }

        method.invoke(m_screenShot, genArgs[0], genArgs[1], genArgs[2], genArgs[3], genArgs[4], genArgs[5], genArgs[6],
                genArgs[7], genArgs[8], genArgs[9]);

        return id;
    }

private:
    QThread *m_thread;
    T *m_screenShot;
};

#endif // QMLTHREADPROXY_H

#ifndef SCREENSHOTPROXY_H
#define SCREENSHOTPROXY_H

#include "ScreenShot.h"

#include <QThread>
#include <QMetaMethod>


/// Использование
///
/// 1) Нужно сделать интерфейс для класса, который мы хотим распаралелить
///     а) Для удобства сдеать сигналы begin/end/progress
///
/// 2) От него отнаследовать прокси и реализацию
///     а) По возможности "соединять" слоты прокси со слотами реализации через invokeMethod
///         - Если вызывать напрямую, то может появиться дедлок (см. 2в)
///     б) Прокси автоматически соединит сигналы от реализации с сигналами прокси
///     в) Задуматься о мьютексах в реализации
///         - может возникнуть дедлок, если установлен мьютекс на запись и на чтение
///             и это свойство используется в QML (см. rect). Возможно, надо разлочить мьютекс
///             перед эмитом сигнала об измении свойства
///     г) Добавить метод stop, чтобы корректно завершалась работа потока при удалении объекта
///         -можно добавить в интерфейс как слот и работать с ним как с обычным слотом
/// 3) Зарегестрировать прокси в метасистеме, использовать в QML
/// 4) Радоваться)))

template <class  T>
class ScreenShotProxy: public QObject
{
    Q_OBJECT_CHECK
    QT_TR_FUNCTIONS

public:
    ScreenShotProxy(QObject *parent = 0):
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

    ~ScreenShotProxy()
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

#endif // SCREENSHOTPROXY_H

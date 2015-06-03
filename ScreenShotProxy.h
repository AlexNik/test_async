#ifndef SCREENSHOTPROXY_H
#define SCREENSHOTPROXY_H

#include "ScreenShot.h"
#include "ScreenshotInterface.h"

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


class ScreenShotProxy: public QObject
{
//    Q_OBJECT_CHECK
//    QT_TR_FUNCTIONS

public:
    ScreenShotProxy(QObject *parent = 0);
    ~ScreenShotProxy();

    Q_INVOKABLE void stop();

    QString name() { return m_screenShot->name(); }
    int progress() { return m_screenShot->progress(); }
    QRect rect() { return m_screenShot->rect(); }

    Q_INVOKABLE virtual void takeScreenshot();

    virtual const QMetaObject *metaObject() const;
    virtual void *qt_metacast(const char *clname);
    virtual int qt_metacall(QMetaObject::Call call, int id, void **args);

public slots:
    void setName(const QString name);
    void setRect(QRect rect);

private:
    QStringList getMetha(const QObject &obj, QMetaMethod::MethodType type);

private:
    QThread *m_thread;
    Screenshot *m_screenShot;
};

#endif // SCREENSHOTPROXY_H

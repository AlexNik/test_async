#ifndef SCREENSHOTPROXY_H
#define SCREENSHOTPROXY_H

#include "ScreenShot.h"

#include <QThread>
#include <QMetaMethod>

class ScreenShotProxy: public Screenshot
{
    Q_OBJECT


    /// 1. region задается в proxy, а используется в Screenshot
    ///     как прокидывать?
    ///     где приватная переменная?
    /// 2. Тоже самое с output
    /// 3. Где хранить значение bytes?
    /// 4. Доступ из С++ к worker'у
    /// 5. Как вызвать у статистики асинхронно ее метод из QML?
    ///
    /// -------
    /// 4*. Получение свойств после обязательной анимации
    ///     (св-во получилось раньше, чем прошла анимация)

public:
    ScreenShotProxy(QObject *parent = 0);
    ~ScreenShotProxy();

private:
    QStringList getMetha(const QObject &obj, QMetaMethod::MethodType type);

private:
    QThread *m_thread;
    Screenshot *m_screenShot;
};

#endif // SCREENSHOTPROXY_H

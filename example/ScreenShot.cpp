#include "ScreenShot.h"

#include <QGuiApplication>
#include <QScreen>
#include <QPixmap>

#include <QDebug>
#include <QThread>
#include <QMetaMethod>

Screenshot::Screenshot(QObject *parent) :
    QObject(parent),
    m_screenRect(0, 0, 1920, 1080),
    m_progress(0),
    m_work(false)
{
}

QString Screenshot::name()
{
    QMutexLocker locker(&m_mutex);
    return m_name;
}

int Screenshot::progress()
{
    QMutexLocker locker(&m_mutex);
    return m_progress;
}

QRect Screenshot::rect()
{
    QMutexLocker locker(&m_mutex);
    return m_screenRect;
}

void Screenshot::setName(const QString name)
{
    QMutexLocker lock(&m_mutex);

    if (m_name != name) {
        m_name = name;
        emit nameChanged(m_name);
    }
}

void Screenshot::takeScreenshot()
{
    emit saveBegin();

    setWork(true);

    QGuiApplication::processEvents();

    QPixmap pix;
    QScreen *screen = QGuiApplication::primaryScreen();

    for (int i = 0; i < 10; i++) {
        if (work()) {
            if (screen) {
                QRect rect1 = rect();
                pix = screen->grabWindow(0, rect1.x(), rect1.y(), rect1.width(), rect1.height());
            }

            QString saveStr = QString("xz_%1.png").arg(i);
            pix.save(saveStr);
            setName(saveStr);

            setProgress(10 * (i + 1));
        }
    }

    emit saveEnd();
}

bool Screenshot::work()
{
    QMutexLocker lock(&m_mutex);
    return m_work;
}

void Screenshot::setRect(QRect rect)
{
    QMutexLocker locker(&m_mutex);
    m_screenRect = rect;
    // TODO: Вызов напрямую?
    locker.unlock();

    emit rectChanged(m_screenRect);
}

void Screenshot::setWork(bool arg)
{
    QMutexLocker lock(&m_mutex);

    if (m_work == arg)
        return;

    m_work = arg;
    emit workChanged(arg);
}

void Screenshot::setProgress(int i)
{
    QMutexLocker locker(&m_mutex);
    m_progress = i;
    emit progressChanged(m_progress);
}

#include "ScreenShot.h"

#include <QGuiApplication>
#include <QScreen>
#include <QPixmap>

#include <QDebug>
#include <QThread>

Screenshot::Screenshot(QObject *parent) :
    QObject(parent)
{
}

void Screenshot::onTakeScreenshot()
{
    qDebug() << "Screenshot::onTakeScreenshot()";

    emit saveBegin();

    QGuiApplication::processEvents();

    QPixmap pix;
    QScreen *screen = QGuiApplication::primaryScreen();

    for (int i = 0; i < 10; i++) {
        QMutexLocker lock(&m_mutex);
        if (screen)
            pix = screen->grabWindow(0, m_screenRect.x(), m_screenRect.y(), m_screenRect.width(), m_screenRect.height());

        pix.save(QString("xz_%1.png").arg(i));

        emit progress(10 * (i + 1));
    }

    emit saveEnd();
}

void Screenshot::onSetRect(int x, int y, int w, int h)
{
    qDebug() << "onSetRect" << QThread::currentThreadId();
    QMutexLocker lock(&m_mutex);

    m_screenRect.setX(x);
    m_screenRect.setY(y);
    m_screenRect.setWidth(w);
    m_screenRect.setHeight(h);
}

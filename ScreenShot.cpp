#include "ScreenShot.h"

#include <QGuiApplication>
#include <QScreen>
#include <QPixmap>

#include <QDebug>
#include <QThread>

Screenshot::Screenshot(QObject *parent) :
    ScreenshotInterface(parent),
    m_screenRect(0, 0, 1920, 1080),
    m_progress(0)
{
}

void Screenshot::setName(const QString name)
{
    //QMutexLocker lock(&m_mutex);

    if (m_name != name) {
        m_name = name;
        emit nameChanged(m_name);
    }
}

void Screenshot::onTakeScreenshot()
{
    qDebug() << "Screenshot::onTakeScreenshot()";

    emit saveBegin();

    QGuiApplication::processEvents();

    QPixmap pix;
    QScreen *screen = QGuiApplication::primaryScreen();

    for (int i = 0; i < 10; i++) {
        if (m_continue) {
            if (screen)
                pix = screen->grabWindow(0, m_screenRect.x(), m_screenRect.y(), m_screenRect.width(), m_screenRect.height());

            QString saveStr = QString("xz_%1.png").arg(i);
            pix.save(saveStr);
            setName(saveStr);

            setProgress(10 * (i + 1));
            qDebug() << progress();
        } else {
            m_continue = true;
            break;
        }
    }

    emit saveEnd();
}

void Screenshot::setRect(QRect rect)
{
    m_screenRect = rect;
    emit rectChanged(m_screenRect);
}

void Screenshot::setProgress(int i)
{
    m_progress = i;
    emit progressChanged(m_progress);
}

#ifndef SCREENSHOT_H
#define SCREENSHOT_H

#include <QObject>
#include <QRect>

#include "ScreenshotInterface.h"

class Screenshot: public ScreenshotInterface
{
    Q_OBJECT
public:
    Screenshot(QObject *parent = 0);

    QString name();
    int progress();
    QRect rect();

    bool isContinue() { QMutexLocker lock(&m_mutex); return m_continue; }
    void setContinue(bool c) { QMutexLocker lock(&m_mutex); m_continue = c; }

    Q_INVOKABLE virtual void takeScreenshot();

public slots:
    // TODO:
    // Возможно будут проблемы, т.к. в метасистеме 2 слота: один от интерфейса, второй отсюда
    void setName(const QString name);
    void setRect(QRect rect);


    void xz(){}

    void onSDF() {}

private:
    void setProgress(int i);

private:
    QString m_name;
    int m_progress;

    QRect m_screenRect;

    QMutex m_mutex;
    bool m_continue;
};

#endif // SCREENSHOT_H

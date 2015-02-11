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

// TODO:
// Если их перенести в public slots, то будет 2 слота setName ???????
    virtual void setName(const QString name);
    virtual void setRect(QRect rect);

    Q_INVOKABLE virtual void takeScreenshot();

public slots:

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

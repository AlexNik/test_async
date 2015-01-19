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

    QString name() const { return m_name; }
    int progress() const { return m_progress; }
    QRect rect() const { return m_screenRect; }

    void setContinue(bool c) { m_continue = c; }

// TODO:
// Если их перенести в public slots, то будет 2 слота setName ???????
    virtual void setName(const QString name);
    virtual void onTakeScreenshot();
    virtual void setRect(QRect rect);
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

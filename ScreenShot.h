#ifndef SCREENSHOT_H
#define SCREENSHOT_H

#include <QObject>
#include <QRect>

class Screenshot : public QObject
{
    Q_OBJECT

    //Q_PROPERTY(bool name READ name WRITE setName NOTIFY nameChanged)
public:
    Screenshot(QObject *parent = 0);

signals:
    void saveBegin();
    void saveEnd();
    void progress(int i);

    void takeScreenshot();
    void setRect(int x, int y, int w, int h);

public slots:
    void onTakeScreenshot();

    void onSetRect(int x, int y, int w, int h);

    void xz(){}

    void onSDF() {}

private:
    QRect m_screenRect;

    QMutex m_mutex;
};

#endif // SCREENSHOT_H

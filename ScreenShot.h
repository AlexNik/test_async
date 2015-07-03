#ifndef SCREENSHOT_H
#define SCREENSHOT_H

#include <QObject>
#include <QRect>

class Screenshot: public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(int progress READ progress NOTIFY progressChanged)
    Q_PROPERTY(QRect rect READ rect WRITE setRect NOTIFY rectChanged)

public:
    Screenshot(QObject *parent = 0);

    QString name();
    int progress();
    QRect rect();

    bool isContinue() { QMutexLocker lock(&m_mutex); return m_continue; }
    void setContinue(bool c) { QMutexLocker lock(&m_mutex); m_continue = c; }

    Q_INVOKABLE void takeScreenshot();
    Q_INVOKABLE void stop();

    int getOne() { return 1; }

signals:
    void progressChanged(int progress);
    void nameChanged(QString name);
    void rectChanged(QRect rect);

    void saveBegin();
    void saveEnd();

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

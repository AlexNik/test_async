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

    Q_PROPERTY(bool work READ work WRITE setWork NOTIFY workChanged)
public:
    Screenshot(QObject *parent = 0);

    QString name();
    int progress();
    QRect rect();
    bool work();


    Q_INVOKABLE void takeScreenshot();

signals:
    void progressChanged(int progress);
    void nameChanged(QString name);
    void rectChanged(QRect rect);

    void saveBegin();
    void saveEnd();
    
    void workChanged(bool arg);

public slots:
    // TODO:
    // Возможно будут проблемы, т.к. в метасистеме 2 слота: один от интерфейса, второй отсюда
    void setName(const QString name);
    void setRect(QRect rect);

    void setWork(bool arg);

private:
    void setProgress(int i);

private:
    QString m_name;
    int m_progress;

    QRect m_screenRect;

    QMutex m_mutex;
    bool m_continue;
    bool m_work;
};

#endif // SCREENSHOT_H

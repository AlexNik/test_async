#ifndef SCREENSHOTINTERFACE_H
#define SCREENSHOTINTERFACE_H

#include <QObject>
#include <QRect>

class ScreenshotInterface : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(int progress READ progress NOTIFY progressChanged)
    Q_PROPERTY(QRect rect READ rect WRITE setRect NOTIFY rectChanged)
public:
    ScreenshotInterface(QObject *parent = 0): QObject(parent) {}

    virtual QString name() const = 0;
    virtual int progress() const = 0;
    virtual QRect rect() const = 0;

signals:
    void progressChanged(int progress);
    void nameChanged(QString name);
    void rectChanged(QRect rect);

    void saveBegin();
    void saveEnd();

    void takeScreenshot();


public slots:
    virtual void setName(const QString name) = 0;
    virtual void setRect(QRect rect) = 0;

    virtual void onTakeScreenshot() = 0;
};

#endif // SCREENSHOTINTERFACE_H

#ifndef COPYCLASS_H
#define COPYCLASS_H

#include <QObject>

class CopyClass : public QObject
{
    Q_OBJECT

    Q_PROPERTY(double progress READ progress WRITE setProgress NOTIFY progressChanged)
    Q_PROPERTY(bool stop READ stop WRITE setStop NOTIFY stopChanged)

public:
    CopyClass(QObject *parent = 0);

    double progress() const { return m_progress; }

    bool stop() const { return m_stop; }

signals:
    void begin();
    void end();
    void progressChanged(int progress);

    void stopChanged(bool stop);

public slots:
    bool copy(QString sourceFile, QString destFolder);
    void setStop(bool stop);

private:
    void setProgress(double progress);

private:
    double m_progress;
    bool m_stop;
};

#endif // COPYCLASS_H

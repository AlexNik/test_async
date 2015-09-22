#ifndef COPYCLASS_H
#define COPYCLASS_H

#include <QObject>

class CopyClass : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int progress READ progress WRITE setProgress NOTIFY progressChanged)
    Q_PROPERTY(bool stop READ stop WRITE setStop NOTIFY stopChanged)

public:
    CopyClass(QObject *parent = 0);

    int progress() const { return m_progress; }

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
    void setProgress(int progress);

private:
    int m_progress;
    bool m_stop;
};

#endif // COPYCLASS_H

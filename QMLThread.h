#ifndef QMLTHREAD_H
#define QMLTHREAD_H

#include <QObject>
#include <QThread>

class QMLThread : public QThread
{
    Q_OBJECT
public:
    QMLThread(QObject *parent = 0);

    Q_INVOKABLE void myId();

    void run();

signals:

public slots:

};

#endif // QMLTHREAD_H

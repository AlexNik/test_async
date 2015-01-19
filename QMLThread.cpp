#include "QMLThread.h"

#include <QDebug>
#include "Windows.h"

QMLThread::QMLThread(QObject *parent) :
    QThread(parent)
{
}

void QMLThread::myId()
{
    qDebug() << "myId" << QThread::currentThreadId();
}

void QMLThread::run()
{
    qDebug() << "run 1 " << QThread::currentThreadId();
    Sleep(3000);
    qDebug() << "run 2 " << QThread::currentThreadId();
}

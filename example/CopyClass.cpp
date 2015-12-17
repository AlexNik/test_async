#include "CopyClass.h"
#include <QFile>
#include <QFileInfo>
#include <QDebug>
#include <Windows.h>

CopyClass::CopyClass(QObject *parent) : QObject(parent),
    m_progress(0),
    m_stop(false)
{
}

bool CopyClass::copy(QString sourceFile, QString destFolder)
{
    emit begin();

    setProgress(0);
    setStop(false);

    sourceFile = sourceFile.remove("file:///");
    destFolder = destFolder.remove("file:///");

    qint64 allBytes = QFileInfo(sourceFile).size();

    QFile source(sourceFile);
    source.open(QIODevice::ReadOnly);

    QFile dest(destFolder + "/" + source.fileName().split("/").last());
    dest.open(QIODevice::WriteOnly);

    char buf;

    double i = 0;
    bool ok;

    while(source.getChar(&buf) && !m_stop) {
        i++;
        ok = dest.putChar(buf);
        setProgress(100 * i / allBytes);
        Sleep(1);

        if (!ok) {
            source.close();
            dest.close();

            emit end();

            return false;
        }
    }

    source.close();
    dest.close();

    emit end();

    return true;
}

void CopyClass::setStop(bool stop)
{
    if (m_stop == stop)
        return;

    m_stop = stop;
    emit stopChanged(stop);
}

void CopyClass::setProgress(double progress)
{
    if (m_progress == progress)
        return;

    m_progress = progress;
    emit progressChanged(progress);
}


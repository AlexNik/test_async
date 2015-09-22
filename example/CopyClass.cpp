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

    char buf[1024];

    int i = 0;
    int lastItaration = allBytes / 1024 + 1;
    while(source.read(buf, 1024) && !m_stop) {
        i++;
        dest.write(buf);
        setProgress(100 * i / lastItaration);
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

void CopyClass::setProgress(int progress)
{
    if (m_progress == progress)
        return;

    m_progress = progress;
    emit progressChanged(progress);
}


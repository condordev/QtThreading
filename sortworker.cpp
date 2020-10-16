#include "sortworker.h"
#include <QDebug>
#include <QThread>

SortWorker::SortWorker(int counter) : mCounter(counter){
    qDebug() << "SortWorker::SortWorker() get called from: " << QThread::currentThreadId();
}

SortWorker::~SortWorker()
{
    qDebug() << "SortWorker::~SortWorker get called from: " << QThread::currentThreadId();
    if(workerTimer != Q_NULLPTR){
        // https://forum.qt.io/topic/91180/delete-vs-deletelater/2
        workerTimer->deleteLater();
    }
}

void SortWorker::onTimeout()
{
    //qDebug() << "SortWorker::onTimeout get called from: " << QThread::currentThreadId();
    emit progress(mCounter--);
    if (mCounter == 0) {
        qDebug() << "SortWorker::onTimeout counter reached 0: " << QThread::currentThreadId();
        workerTimer->stop();
        emit finished();
    }
}

void SortWorker::onWorkerStarted()
{
    workerTimer = new QTimer(this);
    QObject::connect(workerTimer, &QTimer::timeout, this, &SortWorker::onTimeout);
    workerTimer->moveToThread(this->thread());
    workerTimer->start(1000);
    qDebug() << "SortWorker::onThreadStarted get called from: " << QThread::currentThreadId() << " mCounter is: " << mCounter;
}

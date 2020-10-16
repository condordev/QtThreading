#ifndef SORTWORKER_H
#define SORTWORKER_H

#include <QObject>
#include <QTimer>

class SortWorker : public QObject
{
    Q_OBJECT
public:
    explicit SortWorker(int counter = 5);
    ~SortWorker();
signals:
    void finished();
    void progress(int);

public slots:
    void onTimeout();
    void onWorkerStarted();

private:
    int mCounter;
    QTimer *workerTimer = Q_NULLPTR;
};

#endif // SORTWORKER_H

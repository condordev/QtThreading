#include "sortdialog.h"

#include <QHBoxLayout>
#include <QPushButton>
#include <QThread>
#include <QTimer>
#include <QDebug>
#include <QMessageBox>

SortDialog::SortDialog(QWidget *parent) : QDialog(parent)
{

    qDebug() << "SortDialog::SortDialog() get called from: " << QThread::currentThreadId();
   // setGeometry(0, 0, 100, 100);
    btnStart = new QPushButton(tr("&Start"));
    btnStart->setDefault(true);
    btnStart->setEnabled(true);

    btnCancel = new QPushButton(tr("&Cancel"));
    btnCancel->setEnabled(true);

    spinBox = new QSpinBox();
    progressBar = new QProgressBar();
    progressBar->setMinimum(0);
    progressBar->setMaximum(4);

    connect(btnStart, &QPushButton::clicked, this, &SortDialog::on_startButton_clicked);
    connect(btnCancel, &QPushButton::clicked, this, &SortDialog::on_cancelButton_clicked);

    QHBoxLayout *topLeftLayout = new QHBoxLayout;
    topLeftLayout->addWidget(btnStart);
    topLeftLayout->addWidget(btnCancel);
    topLeftLayout->addWidget(spinBox);
    //topLeftLayout->addWidget(progressBar);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(progressBar);
    mainLayout->addLayout(topLeftLayout);
    mainLayout->setSizeConstraint(QLayout::SetMinimumSize);
    setLayout(mainLayout);

    setWindowTitle(tr("Sorter"));
    setFixedHeight(sizeHint().height());
}

SortDialog::~SortDialog()
{
    qDebug() << "SortDialog::~SortDialog() get called from: " << QThread::currentThreadId();
}

void SortDialog::on_startButton_clicked()
{
    qDebug() << "SortDialog::on_startButton_clicked get called from: " << QThread::currentThreadId();

    mpSortWorker = new SortWorker();
    mpThread = new QThread(this);
    mpSortWorker->moveToThread(mpThread);

    QObject::connect(mpThread, &QThread::started, mpSortWorker, &SortWorker::onWorkerStarted);
    QObject::connect(mpThread, &QThread::finished, mpSortWorker, &QThread::deleteLater);
    QObject::connect(mpThread, &QThread::finished, mpSortWorker, &SortWorker::deleteLater);
    QObject::connect(mpSortWorker, &SortWorker::finished, this, &SortDialog::onWorkerFinished);
    QObject::connect(mpSortWorker, &SortWorker::progress, this, &SortDialog::updateProgress);

    progressBar->setValue(0);
    mpThread->start();
}

void SortDialog::on_cancelButton_clicked()
{
    qDebug() << "SortDialog::on_cancelButton_clicked get called from: " << QThread::currentThreadId();
    if(mpThread->isRunning())
        mpThread->quit();
}

void SortDialog::onWorkerFinished()
{
    qDebug() << "SortDialog::onWorkerFinished get called from: " << QThread::currentThreadId();
    if(mpThread->isRunning())
        mpThread->quit();

}

void SortDialog::closeEvent(QCloseEvent *event)
{
    qDebug() << "SortDialog::closeEvent get called from: " << QThread::currentThreadId();
    // do what you need here then call parent's procedure
    if(mpThread->isRunning())
        mpThread->quit();
    QWidget::closeEvent(event);
}

void SortDialog::updateProgress()
{
    progressBar->setValue(progressBar->value()+1);
}



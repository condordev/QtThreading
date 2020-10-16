#ifndef SORTDIALOG_H
#define SORTDIALOG_H
//#pragma once

#include <QDialog>
#include <QObject>
#include <QProgressBar>
#include <QSpinBox>
#include "sortworker.h"
#include <QScopedPointer>

class SortDialog : public QDialog
{
    Q_OBJECT
public:
    SortDialog(QWidget *parent = Q_NULLPTR);
    ~SortDialog();
    void closeEvent(QCloseEvent *event) override;

private:
    QPushButton *btnStart;
    QPushButton *btnCancel;
    QSpinBox *spinBox;
    QProgressBar *progressBar;
    QThread *mpThread = Q_NULLPTR;
    SortWorker *mpSortWorker = Q_NULLPTR;
   // QTimer *mpTimer;

private slots:
    void on_startButton_clicked();
    void on_cancelButton_clicked();
    void onWorkerFinished();
    void updateProgress();
};

#endif // SORTDIALOG_H

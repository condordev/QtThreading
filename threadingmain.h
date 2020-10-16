#ifndef THREADINGMAIN_H
#define THREADINGMAIN_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class ThreadingMain; }
QT_END_NAMESPACE

class ThreadingMain : public QMainWindow
{
    Q_OBJECT

public:
    ThreadingMain(QWidget *parent = nullptr);
    ~ThreadingMain();

private:
    Ui::ThreadingMain *ui;
    QVector<QWidget *> mDialogs;

private slots:
    void on_btnCreate_clicked();
};
#endif // THREADINGMAIN_H

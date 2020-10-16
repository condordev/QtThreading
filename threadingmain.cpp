#include "threadingmain.h"
#include "ui_threadingmain.h"
#include "sortdialog.h"

ThreadingMain::ThreadingMain(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ThreadingMain)
{
    ui->setupUi(this);
   // connect(ui->btnCreate,SIGNAL(clicked()),this,SLOT(on_btnCreate_clicked()));
}

ThreadingMain::~ThreadingMain()
{
    delete ui;
}

void ThreadingMain::on_btnCreate_clicked()
{
    SortDialog *dialog = new SortDialog(this);
    dialog->setAttribute (Qt::WA_DeleteOnClose);
    //dialog->setModal(true);
    dialog->show();
    //mDialogs.append(dialog);
}

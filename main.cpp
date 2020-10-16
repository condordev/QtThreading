#include "threadingmain.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ThreadingMain w;
    w.show();

    return a.exec();
}

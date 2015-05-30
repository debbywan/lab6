#include "dialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog *mainwindow = new Dialog;
    mainwindow->exec();

    return a.exec();
}

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

   GLWidget glw;
   glw.showMaximized();
    return a.exec();
}

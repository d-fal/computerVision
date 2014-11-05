#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.show();
    imageAnalysis analysis;
    analysis.startIt();


    return a.exec();


}

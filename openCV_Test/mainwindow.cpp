#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "opencv/cv.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"

using namespace cv;
using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Mat mat;
    mat=imread("C:\\example\\Lenna.png");
    imshow("",mat);
}

MainWindow::~MainWindow()
{
    delete ui;
}

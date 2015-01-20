#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv/cv.h>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/core/core.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/ml/ml.hpp>
#include <opencv2/contrib/contrib.hpp>

#include<vector>
#include<cstring>
#include<fstream>
#include <cmath>
#include "characterrecognition.h"
#include "imageanalysis.h"
#include "readcharacterdata.h"
#include "comparenumber.h"
using namespace cv;
using namespace std;


//#define TRAINING_SAMPLES 3050       //Number of samples in training dataset
#define ATTRIBUTES 256  //Number of pixels per sample.16X16
//#define TEST_SAMPLES 1170       //Number of samples in test dataset
#define CLASSES 10                  //Number of distinct labels.
#define TRAINING_SAMPLES 4600       //Number of samples in training dataset
#define TEST_SAMPLES 500




namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

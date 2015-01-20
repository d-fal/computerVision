#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#define PI  3.141592
#include <QMainWindow>
#include <QPixmap>
#include <QPicture>
#include <opencv/cv.h>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/core/core.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/ml/ml.hpp>
#include <opencv2/contrib/contrib.hpp>
#include "colordetect.h"
#include "histogram1d.h"
#include "watershedsegmenter.h"
#include "preprocessing.h"
#include "characterrecognition.h"
#include "humomments.h"
#include "readcharacterdata.h"
#include <fstream>
#include <windows.h>

//#define TRAINING_SAMPLES 3050       //Number of samples in training dataset
#define ATTRIBUTES 256  //Number of pixels per sample.16X16
//#define TEST_SAMPLES 1170       //Number of samples in test dataset
#define CLASSES 10                  //Number of distinct labels.
#define TRAINING_SAMPLES 4600       //Number of samples in training dataset
#define TEST_SAMPLES 500       //Number of samples in test dataset


using namespace cv;
using namespace std;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

void read_dataset(char *filename, cv::Mat &data, cv::Mat &classes,  int total_samples);
    cv::Mat image;
    cv::Mat logo;
    cv::Mat imageRGB;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

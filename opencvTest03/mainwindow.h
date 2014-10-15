#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#define PI  3.141592
#include <QMainWindow>
#include <QPixmap>
#include <QPicture>
#include "opencv/cv.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "colordetect.h"
#include "histogram1d.h"
#include "watershedsegmenter.h"
#include "preprocessing.h"
#include "characterrecognition.h"
using namespace cv;
using namespace std;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
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

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

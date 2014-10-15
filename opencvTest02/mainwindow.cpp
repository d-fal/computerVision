#include "mainwindow.h"
#include "assets.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Mat imageRGB;
    Mat image;
    imageRGB=imread("C:\\example\\Lenna.png");
image=imageRGB.clone();
    Mat logo = imread("C:\\example\\logo.png");
    Mat imageROI;

    imageROI=imageRGB(cv::Rect(imageRGB.cols-logo.cols-1,imageRGB.rows-logo.rows-1,logo.cols,logo.rows));
    cout<<"logo : "<<logo.cols<<" x "<<logo.rows<<"\nImage: "<<imageRGB.cols<<" x "<<imageRGB.rows<<
        "\nimageROI: " << imageROI.cols<<" x "<<imageROI.rows<<"\n";
    cv::addWeighted(imageROI,1,logo,0.3,0.,imageROI);
    //imshow("",imageROI);
    //cvtColor(imageRGB,image,CV_RGB2GRAY);
  // cv::flip(imageRGB,image,1); // process the image
//cvtColor(imageRGB,image_gray,CV_BGR2GRAY);

    colorReduce(imageRGB,image,8);
    Mat kernel=Mat(3,3,CV_32F,cv::Scalar(0));
    kernel.at<float>(1,1)=5;
    kernel.at<float>(0,1)=-1;
    kernel.at<float>(1,0)=-1;
    kernel.at<float>(2,1)=-1;
    kernel.at<float>(1,2)=-1;

  //  equalizeHist(image,image_gray);

    filter2D(image,image,image.depth(),kernel);
    colorDetector cd;
    cd.instantiateValues(150,50,100,90);
    //imshow("",image_gray);
    // change color channel ordering
   image=cd.process(image);


    // Qt image
    imshow("",image);
    cv::cvtColor(image,image,CV_BGR2RGB);
    waitKey(37);
    /*
    QImage img= QImage((const unsigned char*)(image.data),
    image.cols,image.rows,QImage::Format_RGB888);
    // display on label
    ui->label->setPixmap(QPixmap::fromImage(img).scaled(500,500));
    // resize the label to fit the image
    */

}

MainWindow::~MainWindow()
{
    delete ui;
}


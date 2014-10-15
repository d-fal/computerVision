#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

        characterRecognition ocr;
        Mat img=imread("C:\\example\\samples\\img_8.png");
        cout<<ocr.charRecognition(img)<<endl;
        imageRGB=imread("C:\\example\\test01.jpg");
        image=imageRGB.clone();
        medianBlur(image,image,3);
        logo = imread("C:\\example\\logo.png");
        Mat imageROI;

        imageROI=imageRGB(cv::Rect(imageRGB.cols-logo.cols-1,imageRGB.rows-logo.rows-1,logo.cols,logo.rows));
        //cout<<"logo : "<<logo.cols<<" x "<<logo.rows<<"\nImage: "<<imageRGB.cols<<" x "<<imageRGB.rows<<
           // "\nimageROI: " << imageROI.cols<<" x "<<imageROI.rows<<"\n";
        cv::addWeighted(imageROI,1,logo,0.3,0.,imageROI);
        //imshow("",imageROI);
        //cvtColor(imageRGB,image,CV_RGB2GRAY);
      // cv::flip(imageRGB,image,1); // process the image
    //cvtColor(imageRGB,image_gray,CV_BGR2GRAY);

        //colorReduce(imageRGB,image,8);
        /*
        Mat kernel=Mat(3,3,CV_32F,cv::Scalar(0));
        kernel.at<float>(1,1)=5;
        kernel.at<float>(0,1)=-1;
        kernel.at<float>(1,0)=-1;
        kernel.at<float>(2,1)=-1;
        kernel.at<float>(1,2)=-1;
*/
      //  equalizeHist(image,image_gray);

        //filter2D(imageRGB,image,image.depth(),kernel);

        colorDetect cd;
        cd.instantiateValues(150,50,100,900);
        //imshow("",image_gray);
        // change color channel ordering
        //image=cd.process(image);

        //Histogram1D h;
        //cv::MatND histo= h.getHistogram(image);

        //cv::namedWindow("Histogram");
        //cv::imshow("Histogram",
        //h.getHistogramImage(image));
        // Qt image
        //imshow("",image);
        //cv::cvtColor(image,image,CV_BGR2RGB);
        //waitKey(37);
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

void MainWindow::on_pushButton_clicked()
{
    VideoCapture cap(0);
    colorDetect cd;
    cd.instantiateValues(150,50,100,90);

    for(;;){

    Mat frame,edges;

    cap >> frame; // get a new frame from camera
if(!frame.empty()){


    //imshow("",image_gray);
    // change color channel ordering
    //edges=cd.process(frame);
    edges=cd.followContours(frame);
    //cvtColor(frame, edges, CV_BGR2GRAY);
    //GaussianBlur(edges, edges, Size(7,7), 1.5, 1.5);
    //Canny(edges, edges, 0, 30, 3);


    imshow("webcam",edges);

    if(waitKey(30) >= 0) break;

    // the camera will be deinitialized automatically in VideoCapture destructor
}
   }
}

void MainWindow::on_pushButton_2_clicked()
{

Mat imageBW,image_gray;
cvtColor(image,image_gray,CV_RGB2GRAY);
threshold(image_gray,imageBW,0,255,THRESH_OTSU);
imshow("",imageBW);
Mat grad;
morphologyEx(imageBW,grad,MORPH_GRADIENT,Mat());
//imshow("Gradient",grad);
Mat open;
morphologyEx(grad,open,MORPH_OPEN,Mat());
//imshow("openned",open);

cv::Mat fg;
cv::erode(imageBW,fg,cv::Mat(),cv::Point(-1,-1),6);
//imshow("Foreground",fg);
cv::Mat bg;
cv::dilate(imageBW,bg,cv::Mat(),cv::Point(-1,-1),6);
cv::threshold(bg,bg,1,128,cv::THRESH_BINARY_INV);
//imshow("Background",bg);
cv::Mat markers(imageBW.size(),CV_8U,cv::Scalar(0));
markers= fg+bg;
imshow("Markers",markers);
// Create watershed segmentation object
WatershedSegmenter segmenter;
// Set markers and process
segmenter.setMarkers(markers);
Mat res=segmenter.process(image);

}

void MainWindow::on_pushButton_3_clicked()
{
   preProcessing pre;
   cv::Mat result=pre.detectCharacters(image);
   imshow("Detected Chars",result+.8*image);
}

void MainWindow::on_pushButton_4_clicked()
{
    colorDetect cd;
    vector<int> res=cd.verticalLines(image);
    for(unsigned int i=0;i<res.size();++i){
        cout<<res[i]<<endl;
    }

}

void MainWindow::on_pushButton_5_clicked()
{
    vector<vector<cv::Point> > contours;
    vector<Vec4i> hierarchy;
    Mat image_canny,image_gray;
    cvtColor(image,image_gray,CV_RGB2GRAY);

    Canny( image_gray, image_canny, 100, 200, 3 );
    cv::findContours(image_canny,
    contours, hierarchy, // a vector of contours
    CV_RETR_TREE, // retrieve the external contours
    CV_CHAIN_APPROX_SIMPLE,Point(0,0)); // all pixels of each contours
    // Draw black contours on a white image
    cv::Mat result(image.size(),CV_8U,cv::Scalar(0));
    RNG rng(12345);
    cvtColor(result,result,CV_GRAY2BGR);
    for(unsigned int i = 0; i< contours.size(); i++ )
         {
           //Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
           Scalar color=Scalar(150,0,255);
           //cv::Rect r0= cv::boundingRect(cv::Mat(contours[i]));
           //cv::rectangle(result,r0,cv::Scalar(0),2);
           //drawContours( result, contours, i, color, 2, 8, hierarchy, 0, Point() );
           float radius;
           cv::Point2f center;

           cv::minEnclosingCircle(cv::Mat(contours[i]),center,radius);
           float wid=radius;
           Point2f start=center-Point2f(wid,wid);
           Point2f end=center+Point2f(wid,wid);
           if(radius<20){
           //cv::circle(result,center,static_cast<int>(radius),color,2);
           rectangle(result,start,end,color,.6,1);
           }
         }

    imshow("",result+0.8*image);
    //imshow("",image);
}

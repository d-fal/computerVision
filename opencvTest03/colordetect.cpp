#include "colordetect.h"

cv::Mat colorDetect::process(const Mat &image){

        cv::Mat result=image.clone();

        cv::Mat_<cv::Vec3b>::const_iterator it=image.begin<cv::Vec3b>();
        cv::Mat_<cv::Vec3b>::const_iterator itend=image.end<cv::Vec3b>();
        cv::Mat_<cv::Vec3b>::iterator itout=result.begin<cv::Vec3b>();
        // for each pixel
        for ( ; it!= itend; ++it, ++itout) {
        // process each pixel ---------------------
        // compute distance from target color


    *itout=getDistance(*it);
        // end of pixel processing ----------------
        }


    return result;
    }

cv::Vec3b colorDetect::getDistance(Vec3b bkr){
    Vec3b out;
    out[0]=100;
    out[1]=0;
    out[2]=0;
int distance = sqrt(pow(bkr[0]-blue,2)+pow(bkr[1]-green,2)+pow(bkr[2]-red,2));
//cout<<distance<<" , "<<(int)bkr[0]<<" , "<<blue<<endl;
if(distance<dst){
out=bkr;
}

return out;
}



void colorDetect::instantiateValues(int r , int g , int b, int d){
blue=b;
red=r;
green=g;
dst=d;
}

cv::Mat colorDetect::followContours(const Mat &image){

    vector<vector<cv::Point> > contours;

    Mat image_canny,image_gray;
    cvtColor(image,image_gray,CV_RGB2GRAY);

    Canny( image_gray, image_canny, 100, 200, 3 );
    cv::findContours(image_canny,
    contours, // a vector of contours
    CV_RETR_EXTERNAL, // retrieve the external contours
    CV_CHAIN_APPROX_NONE); // all pixels of each contours
    // Draw black contours on a white image
    cv::Mat result(image.size(),CV_8U,cv::Scalar(255));
    cv::drawContours(result,contours,
    -1, // draw all contours
    cv::Scalar(0), // in black
    2); // with a thickness of 2

    cvtColor(result,result,CV_GRAY2BGR);
return (255-result)+.6*image;
}


std::vector<int> colorDetect::verticalLines(cv::Mat const &image){

    cv::Mat contours,image2;
    image2=image.clone();
    vector<int> result;
    cv::Canny(image2,contours,125,350);
    // Hough tranform for line detection
    std::vector<cv::Vec4i> lines;
    cv::HoughLinesP(contours,lines,1,PI/180,80,80,10);
    std::vector<cv::Vec4i>::const_iterator it= lines.begin();
    Vec3b color;
    color[0]=100;
    color[1]=200;
    color[2]=100;
    //bool flag=false;
    while(it!=lines.end()){
        Vec4i val=*it;

        //Point Start=Point(val[0],val[1]);
        //Point End  =Point(val[2],val[3]);
        float angle=atan2(val[3]-val[1],val[2]-val[0])*180/PI;
        float length=sqrt(pow(val[2]-val[0],2)+pow(val[3]-val[1],2));
        if((angle<=-80 || angle>=85) && length>image.cols/4){
        //line(image2,Point(val[0],0),Point(val[0],image2.rows),(0,255,255),1,8);
        result.push_back(val[0]);
        }

        ++it;

    }
//imshow("Lines",image2);
return result;

}

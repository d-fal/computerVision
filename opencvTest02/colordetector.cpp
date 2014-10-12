#include "colordetector.h"


cv::Mat colorDetector::process(const Mat &image){

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

cv::Vec3b colorDetector::getDistance(Vec3b bkr){
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



void colorDetector::instantiateValues(int r , int g , int b, int d){
blue=b;
red=r;
green=g;
dst=d;
}




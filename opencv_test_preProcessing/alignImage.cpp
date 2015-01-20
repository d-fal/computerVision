#include "preProcessing.h"

void alignImage::findDistance(Vec4i &l, int &dist,int &maxDist,float &deviationAngle){
    float Theta;

    if((l[0]-l[2])*(l[0]-l[2])+(l[1]-l[3])*(l[1]-l[3])>maxDist*maxDist){
        Theta=(180/CV_PI)*abs(atan2(l[3]-l[1],l[2]-l[0]));
        if (Theta<20){
            deviationAngle=Theta;
        } else{
            deviationAngle=90-Theta;
        }
       // cout<<deviationAngle<<endl;
        dist=1;

    } else dist=0;

}


void alignImage::alignHorizontal(const Mat &src, float &averageDistortion){
    int dist,maxDistance,n;
    float distortion;
    averageDistortion=0;
    Mat dst,cdst;
    Canny(src, dst, 50, 200, 3);
    //cvtColor(src, cdst, CV_GRAY2BGR);
    cdst=src.clone();
     vector<Vec4i> lines;
     HoughLinesP(dst, lines, 1, CV_PI/180, 50, 50, 10 );
     maxDistance=src.rows/10;
     for( size_t i = 0; i < lines.size(); i++ )
     {
       Vec4i l = lines[i];
       findDistance(l,dist,maxDistance,distortion);
       if(dist==1){
       //line( cdst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 3, CV_AA);
       averageDistortion+=distortion;
       ++n;
       }

     }
     averageDistortion/=n;



}

void alignImage::start(Mat const &img, Mat &dst,float &averageDistortion){
    float distortion,distortionInv;
    Mat dstInv;
    alignHorizontal(img,averageDistortion);

    cout<<"Average Distortion: "<<averageDistortion<<endl;

    cv::Point2f pt(img.cols, img.rows);

    cv::Mat r = cv::getRotationMatrix2D(pt, averageDistortion, 1.0);
    cv::warpAffine(img, dst, r, cv::Size(img.cols, img.rows));

    cv::Mat rInv = cv::getRotationMatrix2D(pt, -1*averageDistortion, 1.0);
    cv::warpAffine(img, dstInv, rInv,cv::Size(img.cols, img.rows));

    alignHorizontal(dst,distortion);
    alignHorizontal(img,distortionInv);

    if(distortion>distortionInv){
        dst=dstInv.clone();
        averageDistortion=distortionInv;
    } else {
        averageDistortion=distortion;
    }

}


bool alignImage::exists_file(const string &name){
    ifstream f(name.c_str());
    if (f.good()) {
        f.close();

        return true;
    } else {
        f.close();

        return false;
    }

}

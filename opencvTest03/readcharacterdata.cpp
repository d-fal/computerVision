#include "readcharacterdata.h"

readCharacterData::readCharacterData()
{
}


void readCharacterData::alignPixels(cv::Mat const &image,cv::Mat &result){

    float* output=result.ptr<float>(0);
    for(int j=0;j<image.rows;++j){

    const uchar* current=image.ptr<const uchar>(j);
    for(int i=0;i<image.cols;++i){
    *output++=(current[i] & 0x01);
        //cout<<(current[i] & 0x01)<<endl;
    }
    }

}


void readCharacterData::removeWhitespaces(const Mat &image, Mat &result){
    Mat bin;

    threshold(image,bin,0,256,THRESH_OTSU);
    Mat image2=(bin==0);
    int w=image.cols;
    int h=image.rows;
    int left=0;
    int right=w-1;
    int top=0;
    int bottom=h-1;



    for(int j=0;j<w;j++){
    if(sum(image2.col(j))[0]!=0){
        left = j;
        break;
    }
    }
    for(int j=w-1;j>=0;j--){
    if(sum(image2.col(j))[0]!=0){
        right = j;
        break;
    }
    }
    for(int j=0;j<h;j++){
    if(sum(image2.row(j))[0]!=0){
        top = j;
        break;
    }
    }
    for(int j=h-1;j>=0;j--){
    if(sum(image2.row(j))[0]!=0){
        bottom = j;
        break;
    }
    }

    Rect roi(left,top,right-left,bottom-top);
    result=bin(roi);
    cv::resize(result,result,Size(16,16),0,0,INTER_LINEAR);

    //cvtColor(image,img,CV_GRAY2BGR);
    //cout<<"left: "<<left<<" , right: "<<right<<" , top: "<<top<<" , bottom: "<<bottom<<endl;
    //rectangle(img,Point(left-1,top-1),Point(right+1,bottom+1),Scalar(255,0,0),.5,8,0);

}


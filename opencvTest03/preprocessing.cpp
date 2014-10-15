#include "preprocessing.h"

preProcessing::preProcessing()
{
}

cv::Mat preProcessing::process(const Mat &image){
    Mat blurred,binary2;

    cv::GaussianBlur(image,blurred,cv::Size(5,5),3);
    cvtColor(blurred,binary,CV_RGB2GRAY);
    threshold(binary,binary,0,255,THRESH_OTSU);
    binary=255-binary;


    erode(binary,binary2,Mat(),Point(-1,-1),2);
    binary=binary-binary2;
    Mat sobelY;
    cv::Sobel(binary,sobelY,CV_8U,0,1,3,0.4,128);
    cv::Sobel(sobelY,sobelY,CV_8U,1,0,3,0.4,128);
    //threshold(sobelY,binary,0,255,THRESH_OTSU);
    binary=sobelY>180;
    erode(binary,binary,Mat(),Point(-1,-1),1);
    //blur(binary,binary,Size(3,3),Point(-1,-1));
    return binary;

}

std::vector<int> preProcessing::drawHorizontalLines(const Mat &image){
    cv::Mat result(image.rows,image.cols,CV_8UC3);
    std::vector<int> vec;
    int nl= image.rows; // number of lines
    // total number of elements per line
    int nc= image.cols;
    bool wasLineHere=false;
    for (int j=0; j<nl; j++) {
        bool flag=false;

    // get the address of row j
    const uchar* current=image.ptr<const uchar>(j);
    //Vec3b* output=result.ptr<Vec3b>(j);
    for(int i=0;i<nc;++i){
        uchar pix=current[i];
        if(pix>120){
            flag=true;
            j+=5;
            break;
        }

    }

    if(flag && !wasLineHere){
        line(result,Point(0,j),Point(nc,j),Scalar(0,0,255),2,8);
        wasLineHere=true;
        vec.push_back(j);
    } else wasLineHere=false;

    }
    return vec;
}

cv::Mat preProcessing::detectCharacters(const Mat &image){


    Mat image2=image.clone();

    cv::Mat binary=process(image);
    colorDetect cd;
    vector<int> res=cd.verticalLines(image);
    for(unsigned int i=0;i<res.size();++i){
    line(image2,Point(res[i],0),Point(res[i],image.rows),Scalar(255,0,0),1,1);
    }
    std::vector<int> vec=drawHorizontalLines(binary);
    for(unsigned int i=0;i<vec.size();++i){
    line(image2,Point(0,vec[i]),Point(image.cols,vec[i]),Scalar(0,0,255),2,1);

    }
    vector<vector<cv::Point> > contours;
    vector<Vec4i> hierarchy;
    Mat image_canny,image_gray;
    blur(image,image_gray,Size(3,3),Point(-1,-1));
    cvtColor(image_gray,image_gray,CV_RGB2GRAY);
    Canny( image_gray, image_canny, 100, 200,3 );

    cv::findContours(image_canny,
    contours, hierarchy, // a vector of contours
    CV_RETR_TREE, // retrieve the external contours
    CV_CHAIN_APPROX_SIMPLE,Point(0,0)); // all pixels of each contours
    // Draw black contours on a white image
    vector<Vec2f> reserved;
    cv::Mat result(image.size(),CV_8U,cv::Scalar(0));
    RNG rng(12345);
    cvtColor(result,result,CV_GRAY2BGR);
    characterRecognition ocr;
    for(unsigned int i = 0; i< contours.size(); i++ )
         {

           //Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
           Scalar color=Scalar(0,255,0);
           //cv::Rect r0= cv::boundingRect(cv::Mat(contours[i]));
           //cv::rectangle(result,r0,cv::Scalar(0),2);
           //drawContours( result, contours, i, color, 2, 8, hierarchy, 0, Point() );
           float radius;
           cv::Point2f center;
           bool flag2=false,flag3=false;
           cv::minEnclosingCircle(cv::Mat(contours[i]),center,radius);
           for(unsigned int m=0;m<reserved.size();++m){
             Point2f now=reserved[m];
             //cout<<reserved[m]<<endl;
             float dist=sqrt(pow(now.x-center.x,2)+pow(now.y-center.y,2));
             if(dist<5){
             flag3=true;
             break;
             continue;
                       }
           }

           for(unsigned int k=0;k<vec.size();++k){
            if(center.y<vec[k]+10 && center.y>vec[k]-10){
                reserved.push_back(center);
                flag2=true;
                break;

               }
           }
if(flag2 && !flag3){
           float wid=radius;
           Point start=center-Point2f(wid,wid);
           Point end= center+Point2f(wid,wid);
           if(radius<20){
           //cv::circle(result,center,static_cast<int>(radius),color,2);
           //rectangle(result,start,end,color,1.2,1);
           int w=end.x-start.x;
           int h=end.y-start.y;
           //cout<<start.x<<" , "<<w<<"\n"<<start.y<<" , "<<h<<endl;
           if(start.x+w<image.cols && start.y+h<image.rows && start.x>0 && start.y>0 && w>0 && h>0){


           Rect region_of_interest = Rect(start.x, start.y,w ,h );
           Mat roi=image(region_of_interest);

           //QString filename="C:\\example\\data\\img_"+QString::number((start.y/10))+"_"+QString::number((start.x))+".png";
           //imwrite(filename.toStdString(),roi);

           //cout<<roi.type()<<endl;
           int val=ocr.charRecognition(roi);
           if(val!=-1){
               QString label=QString::number(val);
               putText(result, label.toStdString(), center, FONT_HERSHEY_PLAIN, 1.0, CV_RGB(0,255,0), 2.0);
           //cout<<start.y/10<<" - "<<val<<endl;
}
           }
           }
         }
    }
   // cout<<"Contour size: "<<contours.size()<<"\neffective: "<<reserved.size()<<"\n end"<<endl;

   imshow("",result+.7*image2);
return result;
    //imshow("",.7*image);


}

#include "preprocessing.h"

preprocessing::preprocessing(){

}

cv::Mat preprocessing::detectCharacters(const Mat &image){



    Mat image2=image.clone();
    Mat binary=image;

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
           //cout<<"channels: "<<roi.channels()<<" size: "<<roi.cols<<" x "<<roi.rows<<" , ";
          int val=-1;
           if( roi.cols<8 || roi.rows<8){
            val=0;
           } else{
           val=ocr.charRecognitionANN(roi);
           }
           //cout<<val<<endl;

           if(val!=-1){
               QString label=QString::number(val);
               putText(result, label.toStdString(), center, FONT_HERSHEY_PLAIN, 1.0, Scalar(0,255,100), 2.0);
           //cout<<start.y/10<<" - "<<val<<endl;
}
           }
           }
         }
    }
   // cout<<"Contour size: "<<contours.size()<<"\neffective: "<<reserved.size()<<"\n end"<<endl;

   imshow("",result+.8*image2);
return result;
    //imshow("",.7*image);


}

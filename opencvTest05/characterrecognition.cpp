#include "segmentation.h"

characterRecognition::characterRecognition(){

}

int characterRecognition::charRecognitionANN(const Mat &image){  // USING ANN to discover ................
    CvANN_MLP nnetwork;
    CvFileStorage* storage = cvOpenFileStorage( "C:\\example\\param2.xml", 0, CV_STORAGE_READ );
    CvFileNode *n = cvGetFileNodeByName(storage,0,"DigitOCR");
    nnetwork.read(storage,n);
    cvReleaseFileStorage(&storage);


   // if(image.cols<5 && image.rows<5) return 0;
   // if(image.cols<5) return 1;

Mat data;
if(image.channels()==3){
    cvtColor(image,data,CV_RGB2GRAY);

} else{
     data=image.clone();
}
    //cvtColor(data,data,CV_BGR2GRAY);
    cv::Mat result1(1,ATTRIBUTES,CV_32F);
     removeWhitespaces(data,data);
     if(data.rows<=5 && data.cols<=5) return 0;
    // if(data.rows<8 && data.cols<5) return 1;

     //if(data.cols<5) return 1;
     cv::resize(data,data,Size(20,20),0,0,INTER_LINEAR);
 //   if(data.cols<2 || data.rows<2) return 0;
    alignPixels(data, result1);

    int maxIndex = 0;
    cv::Mat classOut(1,CLASSES,CV_8U);


    nnetwork.predict(result1, classOut);
    float value;
    float maxValue=classOut.at<float>(0,0);
    for(int index=1;index<CLASSES;index++)
    {   value = classOut.at<float>(0,index);
            if(value>maxValue)
            {   maxValue = value;
                maxIndex=index;
            }
    }
data.release();
return maxIndex;



}




void characterRecognition::alignPixels(cv::Mat const &image,cv::Mat &result){

    float* output=result.ptr<float>(0);
    for(int j=0;j<image.rows;++j){

    const uchar* current=image.ptr<const uchar>(j);
    for(int i=0;i<image.cols;++i){
    *output++=(current[i] & 0x01);
        //cout<<(current[i] & 0x01)<<endl;
    }
    }

}


void characterRecognition::removeWhitespaces(const Mat &image, Mat &result){
    Mat bin;
    //deNoise(image,bin);
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


    //cvtColor(image,img,CV_GRAY2BGR);
    //cout<<"left: "<<left<<" , right: "<<right<<" , top: "<<top<<" , bottom: "<<bottom<<endl;
    //rectangle(img,Point(left-1,top-1),Point(right+1,bottom+1),Scalar(255,0,0),.5,8,0);

}

void characterRecognition::deNoise(const Mat &image, Mat &result){
  Mat bin;
  threshold(image,bin,0,255,THRESH_OTSU);
  vector<int> output;
  bin=bin==0;
  Mat img=image.clone();
  float avg=0;
  vector<int> coords;

  for (int i = 0 ; i < image.cols; i++){
      int s = sum(bin.col(i))[0]/255;
      coords.push_back(s);
   //   line(img,Point(i,0),Point(i,s),Scalar(0,255,0),1);
      avg+=s;
  }
  avg/=image.cols;
  for (int i = 0 ; i < coords.size(); i++){
      int s = coords[i];
      if(s<.9*avg) for(int j=0; j<img.rows ; ++j) img.at<uchar>(j,i)=255;

      }

  //line(img,Point(0,avg),Point(image.cols,avg),Scalar(0,0,255),1);
 //imshow("TEST",img);
  result=img;

}



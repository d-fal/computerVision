#include "characterrecognition.h"

characterRecognition::characterRecognition()
{
address="C:\\example\\samples\\";
thresh=0;

}


int characterRecognition::charRecognition(const Mat &image){

int minPos=-1,minVal,formerMinVal=10000;
Size size(8*image.cols,8*image.rows);
//(image.cols,image.rows,CV_8UC1);
for(int i=0;i<=9;++i){
Mat sample,test;
resize(image,test,size);
cvtColor(test,test,CV_RGB2GRAY);
threshold(test,test,0,255,THRESH_OTSU);

sample=imread((address+"img_"+QString::number(i)+".png").toStdString());
resize(sample,sample,size);
cvtColor(sample,sample,CV_RGB2GRAY);
threshold(sample,sample,0,255,THRESH_OTSU);
//cout<<"sample: "<<sample.rows<<" x "<<sample.cols<<"\n test: "<<test.rows<<" x "<<test.cols<<endl;
minVal=(sum(sum(abs((sample-test)!=0))/255)[0]);
if(minVal<formerMinVal && minVal>thresh){
    minPos=i;
    formerMinVal=minVal;
}

//imwrite((address+"op_"+QString::number(i)+".png").toStdString(),abs(sample-test));
}

//imwrite("C:\\example\\img01.png",sample);
return minPos;
}

int characterRecognition::charRecognitionANN(const Mat &image){
    CvANN_MLP nnetwork;
    CvFileStorage* storage = cvOpenFileStorage( "C:\\example\\param2.xml", 0, CV_STORAGE_READ );
    CvFileNode *n = cvGetFileNodeByName(storage,0,"DigitOCR");
    nnetwork.read(storage,n);
    cvReleaseFileStorage(&storage);
    readCharacterData rdChar;

Mat data;
if(image.channels()==3){
    cvtColor(image,data,CV_RGB2GRAY);

} else{
     data=image;
}
    //cvtColor(data,data,CV_BGR2GRAY);
    cv::Mat result1(1,ATTRIBUTES,CV_32F);
    rdChar.removeWhitespaces(data,data);
    rdChar.alignPixels(data, result1);

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

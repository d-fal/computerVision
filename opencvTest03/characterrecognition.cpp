#include "characterrecognition.h"

characterRecognition::characterRecognition()
{
address="C:\\example\\samples\\";
thresh=0;

}


int characterRecognition::charRecognition(const Mat &image){

int minPos=-1,minVal,formerMinVal=10000;
Size size(4*image.cols,4*image.rows);
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

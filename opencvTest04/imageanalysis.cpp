#include "imageanalysis.h"

imageAnalysis::imageAnalysis()
{
refVAspect=800;
refHAspect=700;
}

void imageAnalysis::startIt(){
    characterRecognition CR;
    image=imread("c:\\example\\Test\\test_1.jpg");
    if(image.channels()!=1){
        cvtColor(image,image,CV_BGR2GRAY);
    }
    //resize(image,image,Size(1200,1200),0,0);
    Mat img2,imgRef;

    cvtColor(image,img2,CV_GRAY2BGR);

    refImage=img2;
    image.copyTo(imgRef);
    blur(image,image,Size(5,5),Point(-1,-1));
    threshold(image,image,0,255,THRESH_OTSU);
    image=image==0;
    //preprocessing pre;
    vector<int> coords = findPicture();
    leftMargin   = coords[0];
    rightMargin  = coords[1];
    topMargin    = coords[2];
    bottomMargin = coords[3];
    photoID=refImage(Rect(coords[0],coords[2],coords[1]-coords[0],coords[3]-coords[2]));
    vector<int> margins=detectTextarea();
    CR.topBound      = margins[0];
    CR.belowBound    = margins[1];
    CR.leftTextArea  = margins[2];
    CR.rightTextArea = margins[3];

    for (int i=4 ; i < margins.size() ; ++i ) CR.imgRows.push_back(margins[i]);
    //CR.topBound
    CR.detectCharacters(imgRef);
    //Mat imgX=pre.detectCharacters(image);
    imshow("id",refImage);
}

vector<int> imageAnalysis::findPicture(void){
    vector<int> result;
    float hAspect=image.cols/refHAspect;
    float vAspect=image.rows/refVAspect;
    cout<<image.cols<<" x "<<image.rows<<"   ,  "<<hAspect <<" x "<<vAspect<<endl;
    int top=0,bottom=refVAspect-1,left=0,right=refHAspect-1;

    Mat imgx;

    resize(image,imgx,Size(refHAspect,refVAspect),0,0);
    Mat element(50,20,CV_8U,cv::Scalar(1));
    erode(imgx,imgx,element);
    for(int r=1;r<refVAspect;++r){
    Mat thisRow=imgx.row(r);

    if(sum(thisRow)[0]!=0){
        top=r*.9;
        break;
    }
    }

    for(int r=refVAspect-1;r>=0;--r){
    Mat thisRow=imgx.row(r);
    if(sum(thisRow)[0]!=0){
    bottom=r;
    break;
    }
    }

    for(int h=0;h<refHAspect;++h){
    Mat thisCol=imgx.col(h);
    if(sum(thisCol)[0]!=0){
    left=h*.9;
    break;
    }
    }

    for(int h=refHAspect-1;h>=0;--h){
    Mat thisCol=imgx.col(h);
    if(sum(thisCol)[0]!=0){
    right=h;
    break;
    }
    }

    result.push_back((left-10)*hAspect);
    result.push_back((right+10)*hAspect);
    result.push_back((top-10)*vAspect);
    result.push_back((bottom+10)*vAspect);

    // SET SELECTED PART OF IMAGE TO ZERO
    for(int j=.6*result[2];j<result[3];++j){
        uchar* current = image.ptr<uchar>(j);
        for(int i=0;i<image.cols;++i){
            if(i<1.1*result[1] || i>(2.1*result[1]-result[0]))
            current[i]*=0;
        }
    }
    cout<<hAspect<<" x "<<vAspect<<endl;
    return result;
}


std::vector<int> imageAnalysis::detectTextarea(){
    std::vector<int> result;
    float hAspect=image.cols/refHAspect;
    float vAspect=image.rows/refVAspect;
    Mat resizeImage;
    //resize(image,imgx,Size(refHAspect,refVAspect),0,0);
    resize(image,resizeImage,Size(refHAspect,refVAspect),0,0);
    Mat element1(5,30,CV_8U,cv::Scalar(1));
    erode(resizeImage,resizeImage,element1);
    Sobel(resizeImage,resizeImage,CV_8U,1,0,3,1,128);
    cout<<"Identity grabbed successfully!"<<endl;
    resizeImage=resizeImage==0;
    blur(resizeImage,resizeImage,Size(4,40),Point(-1,-1));
    resizeImage=resizeImage>0;
    morphologyEx(resizeImage,resizeImage,MORPH_CLOSE,element1);
    int top=0,bottom=resizeImage.rows-1;


    for (int j=bottomMargin;j<resizeImage.rows-1;++j){
        int val=sum(resizeImage.row(j))[0];
        int nextVal=sum(resizeImage.row(j+1))[0];
        if(val!=0 && nextVal==0){
            top=j;
            break;
        }

    }

    for (int j=resizeImage.rows-1;j>bottomMargin;--j){
        int val=sum(resizeImage.row(j))[0];
        int nextVal=sum(resizeImage.row(j-1))[0];
        if(val!=0 && nextVal==0){
            bottom=j;
            break;
        }

    }
    cout<<top<<" , "<<bottom<<endl;
    top-=30;
    bottom+=30;
    top*=vAspect;
    bottom*=vAspect;
    //imshow("ref",resizeImage);
    Mat scoresBlock=image(Rect(Point(0,top),Point(refImage.cols,bottom)));
    //Sobel(scoresBlock,scoresBlock,CV_8U,0,1);
    Sobel(scoresBlock,scoresBlock,CV_8U,1,0);
    vector<int> textArea=makeHistogram(scoresBlock);
    vector<int> imgRows=findRows(scoresBlock);
    int m=1;
    for(int i=0; i<imgRows.size() ; ++i){
     line(refImage,Point(0,imgRows[i]+top),Point(refImage.cols,imgRows[i]+top),Scalar(0,150,150),2);
     putText(refImage,(QString::number(m)).toStdString(),
             Point(refImage.cols*.95,imgRows[i]+top),CV_FONT_NORMAL,1,Scalar(255,20,10));
     m++;
    }
   line(refImage,Point(0,top),Point(refImage.cols-1,top),Scalar(255,0,0),2);
   line(refImage,Point(0,bottom),Point(refImage.cols-1,bottom),Scalar(255,0,0),2);
   //imshow("",scoresBlock);
   result.push_back(top);
   result.push_back(bottom);
   result.push_back(textArea[0]);
   result.push_back(textArea[1]);
   result.insert(result.end(),imgRows.begin(),imgRows.end());
   return result;

}



std::vector<int> imageAnalysis::makeHistogram(const Mat &scoresBlock){
    float MaxHeight=scoresBlock.cols;
    vector <histValue> result;
    vector <int>       out;
    float finalValue=0;
    histValue c;
    Mat hist(scoresBlock.rows,scoresBlock.cols,CV_8UC3);
    hist=hist*0;
    finalValue=MaxHeight/6;
    for (int i = 0; i<scoresBlock.cols;++i){
        float height=sum(scoresBlock.col(i))[0]/(255);

        line(hist,Point(i,0),Point(i,height),Scalar(255,255,128),1);
        c.Xposition=i;
        c.value=height;
    //    finalValue+=height;
        if(height>finalValue)
        result.push_back(c);
    }
    //finalValue/=.5*scoresBlock.cols;

    int textInterval[2]={0};
    int interval;
    int prevInterval=0;
    for (int i=0;i<result.size()-1;++i){

        interval=result[i+1].Xposition-result[i].Xposition;
        if(interval>prevInterval){
            textInterval[0]=result[i].Xposition;
            textInterval[1]=result[i+1].Xposition;
            prevInterval=interval;

        }
    }
    out.push_back(textInterval[0]);
    out.push_back(textInterval[1]);
    line(refImage,Point(textInterval[0],0),Point(textInterval[0],MaxHeight),Scalar(255,0,255),3);
    line(refImage,Point(textInterval[1],0),Point(textInterval[1],MaxHeight),Scalar(255,0,255),3);
    line(hist,Point(0,finalValue),Point(scoresBlock.cols,finalValue),Scalar(0,100,255));
    return out;
}

vector<int> imageAnalysis::findRows(const Mat &scoresBlock){
    int width;
    int nextWidth;
    int avg=0;
    vector <int> candidates,result;
    //Mat hist(scoresBlock.rows,scoresBlock.cols,CV_8UC3);
    for (int i = 0 ; i < scoresBlock.rows ; i++){
    width = sum(scoresBlock.row(i))[0]/255;
    //line(hist,Point(0,i),Point(width,i),Scalar(255,0,0));
    avg+=width;
    }
    avg/=scoresBlock.rows;
    for (int i = 1 ; i < scoresBlock.rows-1 ; i++){
    width = sum(scoresBlock.row(i))[0]/255;
    nextWidth = sum(scoresBlock.row(i+1))[0]/255;

    if((width>=avg && nextWidth<avg) || (width<avg && nextWidth>=avg)){
        candidates.push_back(i);
    }

    }
    int m=0;
    for (int i=0 ; i<candidates.size() ; i+=2){
        if(candidates[i+1]-candidates[i]<5) continue;
     int pos=(candidates[i]+candidates[i+1])/2;
     //line(hist,Point(0,pos),Point(5*avg,pos),Scalar(0,255,0),1);
     result.push_back(pos);
     //putText(hist,(QString::number(m)).toStdString(),Point(5*avg,pos),CV_FONT_VECTOR0,1,Scalar(255,20,10));
     }

    //line(hist,Point(avg,0),Point(avg,scoresBlock.rows),Scalar(0,0,255),3);
    //imshow("Hist",hist);
    return result;
}

#include "characterrecognition.h"

characterRecognition::characterRecognition()
{
}


std::vector<POIs> characterRecognition::detectCharacters(const Mat &src){
    vector<POIs> result,interest;
    Mat newImage=src.clone();
    cvtColor(newImage,newImage,CV_GRAY2BGR);
    vector<vector<cv::Point> > contours;
    vector<Vec4i> hierarchy;
    Mat image_canny,image_gray;
    blur(src,image_gray,Size(3,3),Point(-1,-1));

    Canny( image_gray, image_canny, 100, 200,3 );

    cv::findContours(image_canny,
    contours, hierarchy, // a vector of contours
    CV_RETR_TREE, // retrieve the external contours
    CV_CHAIN_APPROX_SIMPLE,Point(0,0)); // all pixels of each contours
    // Draw black contours on a white image


    RNG rng(12345);


      vector<vector<Point> > contours_poly( contours.size() );
      vector<Rect> boundRect( contours.size() );
      vector<Point2f>center( contours.size() );
      vector<float>radius( contours.size() );
      float averageRadius=0;
      for( int i = 0; i < contours.size(); i++ )
         {
           approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
           boundRect[i] = boundingRect( Mat(contours_poly[i]) );
           minEnclosingCircle( (Mat)contours_poly[i], center[i], radius[i] );
           averageRadius+=radius[i];

         }
       averageRadius/=contours.size();

      /// Draw polygonal contour + bonding rects + circles

      for( int i = 0; i< contours.size()-1; i++ )
         {
           Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );

           if(radius[i]<averageRadius){
           //circle( drawing, center[i], (int)radius[i], color, 2, 8, 0 );
            drawContours( originalImage, contours, i, Scalar(0,255,255), 2, 8, hierarchy, 0, Point() );
           POIs c,cNext;
           c.radius=radius[i];
           c.xPos=center[i].x;           c.yPos=center[i].y;
           cNext.xPos=center[i+1].x;     cNext.yPos=center[i+1].y;
           if(sqrt(pow(abs(c.xPos-cNext.xPos),2)+pow(abs(c.yPos-cNext.yPos),2))>=c.radius)
           result.push_back(c);

           }
           }

      interest=alignContours(result,imgRows);
      grabROIS(originalImage,interest);
      Mat testImage=imread("C:\\example\\img16.png",0);

      readCharacterData RCD;
      RCD.deNoise(testImage,testImage);
      imshow("TEST",testImage);
      return result;

}

void characterRecognition::grabROIS(const Mat &src , std::vector<POIs> interestPoints){
    compareNumber CNO;
    Mat drawing(src.rows,src.cols,src.type());
    Point2f center;
    float radius=0;
    for(int i=0; i < interestPoints.size(); ++i) radius+=interestPoints[i].radius;
    radius/=interestPoints.size();

    cout<<"Radius: "<<radius<<endl;
    cout<<"Remarks Panel: "<<remarksPanel<<endl;
    int m=0;
    int res;
    QString str="";
    for( int i = 0; i< interestPoints.size()-1; i++ )
       {
         //Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
         //drawContours( drawing, contours_poly, i, color, 1, 8, vector<Vec4i>(), 0, Point() );
         //rectangle( drawing, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0 );

         POIs c     = interestPoints[i];
         POIs cNext = interestPoints[i+1];
         center.x = c.xPos; center.y=c.yPos; //radius = c.radius;
       if(center.y<belowBound && center.y>topBound &&
               !(center.x>leftTextArea && center.x<rightTextArea) && center.x>2*remarksPanel){
           //cout<<"RADIUS: "<<(interestPoints[i].radius<radius)<<" ,, \n";
if(interestPoints[i].radius<radius) res=0;
else{
       Rect Re;
    if(c.xPos>rightTextArea){
        Re=Rect(Point(c.xPos-.6*c.radius,c.row-2*c.radius),Point(c.xPos+1.2*c.radius,c.row+2*c.radius));
    } else {
        Re=Rect(Point(c.xPos-1.2*c.radius,c.row-2*radius),Point(c.xPos+1.2*c.radius,c.row+2*radius));
    }
Mat roi = originalImage(Re);

//QString address="C:\\example\\grabbed\\img"+QString::number(m)+".png";
//imwrite(address.toStdString(),roi);
res=charRecognitionANN(roi);
}
//rectangle(drawing, Point(c.xPos-.6*radius,c.row-2*radius),Point(c.xPos+1.2*radius,c.row+2*radius), Scalar(0,55,255),1, 8, 0 );

//
  str+=QString::number(res);

  if(abs(c.xPos-cNext.xPos)>4*radius){
      int mark=str.toInt();
      if(c.xPos<rightTextArea) mark=CNO.compare(mark);
      cout<<mark;
//putText(drawing,(QString::number(mark)).toStdString(),Point(c.xPos-4*radius,c.row),CV_FONT_NORMAL,.5,Scalar(0,255,255));
      str="";

      cout<<" , ";
}
  if(c.row!=cNext.row) {
      cout<<"\n\n";

  }
//
m++;
       }
    }
     imshow("NN",drawing+.6*originalImage);

}

std::vector<POIs> characterRecognition::alignContours(std::vector<POIs> centers, std::vector<int> imgRowsx){ // cluster points in rows
    //cout<<"\nSIZE OF ROWs: "<<imgRowsx.size()<<endl;
    vector<POIs> Xorder,Yorder,result;
    float refDist;
    if(imgRowsx.size()>=8) refDist=imgRowsx[2]-imgRowsx[1];
    else refDist=imgRowsx[0];
    //refDist/=5;

    //cout<<"Reference distance: "<<refDist<<endl;
    for (int i = 0 ; i<imgRowsx.size() ; ++i){
    float dist;
    for (int j =0 ; j<centers.size() ; ++j){
    dist = abs(imgRowsx[i]-(int)centers[j].yPos );

    if((dist<=refDist/2)){

    centers[j].row=imgRowsx[i];
    Xorder.push_back(centers[j]);

    }

    } // ALL OF POINTS
    //cout<<"\nRow: "<<i<<" ----------------------"<<endl;

    Yorder = sortPoints(Xorder);
    Xorder.clear();
    // cout<<"\nSIZE OF RESULT: "<<Yorder.size()<<endl;
    result.insert(result.end(),Yorder.begin(),Yorder.end());
    //cout<<"\nSIZE OF RESULT: "<<result.size()<<endl;
    Yorder.clear();
    } // ORDER BY ROWS

    return result;
}

std::vector<POIs> characterRecognition::sortPoints(std::vector<POIs> Xorder){ // sort from leftmost to rightmost
    vector<POIs> result,out;
     //cout<<"\n Size #1: "<<Xorder.size()<<endl;

    while ( Xorder.size()!=0){
        int minValue=Xorder[0].xPos;
        int storedIndex=0;

    for (int i = 1 ; i < Xorder.size() ; ++i){
        //if (i==j) continue;
    if(Xorder[i].xPos<minValue){
    minValue=Xorder[i].xPos;
    storedIndex=i;
    }
    }

    result.push_back(Xorder[storedIndex]);
    Xorder.erase(Xorder.begin()+storedIndex);

    //Xorder[storedIndex].xPos=-1;
    }
    //for (int i = 0 ; i<result.size() ; ++i ) cout<<"( "<<result[i].xPos<<" , "<<result[i].yPos<<" ) , ";
     for (int it = 0 ; it < result.size()-1; ++it){
if(result[it].radius<2) continue;
if (abs(result[it].xPos-result[it+1].xPos)>=1 ) out.push_back(result[it]);
     }
    // cout<<"\n Size #2: "<<out.size()<<endl;
    return out;
}


int characterRecognition::charRecognitionANN(const Mat &image){  // USING ANN to discover ................
    CvANN_MLP nnetwork;
    CvFileStorage* storage = cvOpenFileStorage( "C:\\example\\param2.xml", 0, CV_STORAGE_READ );
    CvFileNode *n = cvGetFileNodeByName(storage,0,"DigitOCR");
    nnetwork.read(storage,n);
    cvReleaseFileStorage(&storage);
    readCharacterData rdChar;

    if(image.cols*image.rows<30) return 0;

Mat data;
if(image.channels()==3){
    cvtColor(image,data,CV_RGB2GRAY);

} else{
     data=image;
}
    //cvtColor(data,data,CV_BGR2GRAY);
    cv::Mat result1(1,ATTRIBUTES,CV_32F);
    rdChar.removeWhitespaces(data,data);
 //   if(data.cols<2 || data.rows<2) return 0;
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


std::vector<POIs> characterRecognition::detectIdNo(const Mat &src){
    vector<POIs> result,interest;
    Mat newImage;
    if(src.channels()!=1){
    cvtColor(src,newImage,CV_BGR2GRAY);
    } else{
    newImage=src.clone();
    }
    cvtColor(newImage,newImage,CV_GRAY2BGR);
    vector<vector<cv::Point> > contours;
    vector<Vec4i> hierarchy;
    Mat image_canny,image_gray;
    blur(src,image_gray,Size(3,3),Point(-1,-1));

    Canny( image_gray, image_canny, 100, 200,3 );

    cv::findContours(image_canny,
    contours, hierarchy, // a vector of contours
    CV_RETR_TREE, // retrieve the external contours
    CV_CHAIN_APPROX_SIMPLE,Point(0,0)); // all pixels of each contours
    // Draw black contours on a white image


    RNG rng(12345);


      vector<vector<Point> > contours_poly( contours.size() );
      vector<Rect> boundRect( contours.size() );
      vector<Point2f>center( contours.size() );
      vector<float>radius( contours.size() );
      float averageRadius=0;
      for( int i = 0; i < contours.size(); i++ )
         {
           approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
           boundRect[i] = boundingRect( Mat(contours_poly[i]) );
           minEnclosingCircle( (Mat)contours_poly[i], center[i], radius[i] );
           averageRadius+=radius[i];

         }
       averageRadius/=contours.size();
      cout<<"\nAVG: "<<averageRadius<<endl;
      /// Draw polygonal contour + bonding rects + circles

      for( int i = 0; i< contours.size()-1; i++ )
         {
           Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );

           if(radius[i]<averageRadius){
           //circle( drawing, center[i], (int)radius[i], color, 2, 8, 0 );
           POIs c,cNext;
           c.radius=radius[i];
           c.xPos=center[i].x;           c.yPos=center[i].y;
           cNext.xPos=center[i+1].x;     cNext.yPos=center[i+1].y;
           if(sqrt(pow(abs(c.xPos-cNext.xPos),2)+pow(abs(c.yPos-cNext.yPos),2))>=c.radius)
           result.push_back(c);
           circle( newImage, center[i], (int)radius[i], color, 2, 8, 0 );
           }
           }


      return result;

}

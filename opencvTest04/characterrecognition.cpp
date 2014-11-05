#include "characterrecognition.h"

characterRecognition::characterRecognition()
{
}


std::vector<POIs> characterRecognition::detectCharacters(const Mat &src){
    vector<POIs> result;
    Mat newImage=src.clone();
    cvtColor(newImage,newImage,CV_GRAY2BGR);
    vector<vector<cv::Point> > contours;
    vector<Vec4i> hierarchy;
    Mat image_canny,image_gray;
    blur(src,image_gray,Size(3,3),Point(-1,-1));
    //cvtColor(image_gray,image_gray,CV_RGB2GRAY);
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
      Mat drawing = Mat::zeros( image_canny.size(), CV_8UC3 );
      for( int i = 0; i< contours.size()-1; i++ )
         {
           Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
           //drawContours( drawing, contours_poly, i, color, 1, 8, vector<Vec4i>(), 0, Point() );
           //rectangle( drawing, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0 );
           if(radius[i]<averageRadius){
           //circle( drawing, center[i], (int)radius[i], color, 2, 8, 0 );
           POIs c,cNext;
           c.radius=radius[i];
           c.xPos=center[i].x;         c.yPos=center[i].y;
           cNext.xPos=center[i+1].x;     cNext.yPos=center[i+1].y;
           if(sqrt(pow(abs(c.xPos-cNext.xPos),2)+pow(abs(c.yPos-cNext.yPos),2))>=c.radius)
           result.push_back(c);

           }
           }

     std::vector<POIs> interest=alignContours(result);
     for (int i = 0 ; i<interest.size() ; ++i )
      cout<<"( "<<interest[i].xPos<<" , "<<interest[i].yPos<<" ) , ";

      grabROIS(newImage,interest);
      return result;

//imshow("3",drawing+.7*newImage);
}

void characterRecognition::grabROIS(const Mat &src , std::vector<POIs> interestPoints){

    Mat drawing = src.clone();
    Point center;
    int radius;
    cout<<"POIs size: "<<interestPoints.size()<<endl;
    int m=0;
    for( int i = 0; i< interestPoints.size(); i++ )
       {
         //Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
         //drawContours( drawing, contours_poly, i, color, 1, 8, vector<Vec4i>(), 0, Point() );
         //rectangle( drawing, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0 );
         POIs c = interestPoints[i];
         center.x = c.xPos; center.y=c.yPos; radius = c.radius;
       if(center.y<belowBound && center.y>topBound && !(center.x>leftTextArea && center.x<rightTextArea)){
circle( drawing, center, 1.5*radius, Scalar(120,255,0),1, 8, 0 );
putText(drawing,(QString::number(m)).toStdString(),Point(c.xPos,c.yPos),CV_FONT_VECTOR0,.3,Scalar(255,20,10));
m++;
       }
    }
     //for (int i=0; i<imgRows.size() ; ++i )
     //line(drawing,Point(0,imgRows[i]+topBound),Point(drawing.cols,imgRows[i]+topBound),Scalar(0,150,150),2);
imshow("NN",drawing);

}

std::vector<POIs> characterRecognition::alignContours(std::vector<POIs> centers){
    vector<POIs> Xorder,Yorder,result;
    float refDist = imgRows[1]-imgRows[0];
    for (int i = 0 ; i<imgRows.size() ; ++i){
    float dist;
    for (int j =0 ; j<centers.size() ; ++j){
    dist = abs(imgRows[i]+topBound-centers[j].yPos );

    if(dist<refDist/2){
    centers[j].row=i;
    Xorder.push_back(centers[j]);
    }

    } // ALL OF POINTS
    //cout<<"\nRow: "<<i<<" ----------------------"<<endl;

    Yorder = sortPoints(Xorder);
    result.insert(result.end(),Yorder.begin(),Yorder.end());
    } // ORDER BY ROWS
    return result;
}

std::vector<POIs> characterRecognition::sortPoints(std::vector<POIs> Xorder){
    vector<POIs> result;


    for (int j = 0 ; j < Xorder.size() ; ++j){
        int minValue=Xorder[j].xPos;
        int storedIndex=j;
        if (Xorder[j].xPos==-1) continue;
    for (int i = 1 ; i < Xorder.size() ; ++i){
        if (Xorder[i].xPos==-1 || i==j) continue;
    if(Xorder[i].xPos<minValue){
    minValue=Xorder[i].xPos;
    storedIndex=i;
    }
    }
    if(j==0) result.push_back(Xorder[storedIndex]);
    else if(abs(Xorder[storedIndex].xPos-result.back().xPos)!=0 && j>0){
    result.push_back(Xorder[storedIndex]);
    }
    Xorder[storedIndex].xPos=-1;
    }
    //for (int i = 0 ; i<result.size() ; ++i ) cout<<"( "<<result[i].xPos<<" , "<<result[i].yPos<<" ) , ";
    return result;
}

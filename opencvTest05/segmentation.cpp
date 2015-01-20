#include "segmentation.h"
#include "flowcontrol.h"

segmentation::segmentation()
{

}

void segmentation::start(){
    originalImage=image.clone();
    if (image.channels()!=1) cvtColor(image,image,CV_BGR2GRAY);
    Mat binary;
    float averageRowHeight;
    std::vector<int> textDigits,grabbedRows,details_rows,Coords,all_columns,final_rows_width;
    /*

      PRE-PROCESSING COMES HERE

    */


   // image(Rect(Point(Coords[0],Coords[2]),Point(Coords[1],Coords[3])))*=0;
    threshold(image,binary,0,255,THRESH_OTSU);
    findRows(binary,averageRowHeight, grabbedRows,details_rows,final_rows_width);
    Mat textAreaBlock=originalImage(Rect(Point(0,grabbedRows[0]),Point(image.cols,grabbedRows.back())));
    textDigits=findTextArea(textAreaBlock,all_columns); // PLACE WHERE SHOULD NOT BE DETECTED

    locatePhoto(image,details_rows,Coords);

    processStart(grabbedRows,textDigits,all_columns,averageRowHeight,final_rows_width);

    //line(originalImage,Point(all_columns[2],0),Point(all_columns[2],originalImage.rows),Scalar(255,0,0));
    int det=details_rows.size();
    Mat nationalCodeBlock=originalImage(Rect(Point(all_columns[2],details_rows[det-2]-.9*averageRowHeight),
    Point(all_columns.back(),details_rows[det-2]+averageRowHeight*.8)));
    segmentNationalCode(nationalCodeBlock);
    //imwrite("C:\\example\\grabbed\\img_nationalCode.png",nationalCodeBlock);
    //vector<int> result=segmentDigits(nationalCodeBlock,textDigits,all_columns);
    //line(originalImage,Point(0,details_rows[det-2]),Point(originalImage.cols,details_rows[det-2]),Scalar(255,0,0));
    //imshow("PHOTO ID: ",nationalCodeBlock);
    //waitKey(0);
    //vector<int> result=segmentDigits(imread("C:\\example\\grabbed\\img_15.png",0),textDigits,all_columns); // THIS SHOULD NOT BE HERE


}
// ############################################ PROCESS START #########################################################################
void segmentation::processStart(std::vector<int> &grabbedRows,const vector<int> &textDigits,const std::vector<int> &all_columns, float &averageWidth,
                                vector<int> final_rows_width){
    ostringstream convert;

    bool flag=false;
    int tries=0;

    for(int i=0;i<grabbedRows.size();i++){
        Mat roiLine;
    if(i!=0)
    roiLine=originalImage(Rect(Point(0,grabbedRows[i]-averageWidth/2),
                                   Point(originalImage.cols,grabbedRows[i]+averageWidth/2+5))).clone();
    else
    roiLine=originalImage(Rect(Point(0,grabbedRows[i]-final_rows_width[i]/5),
                                       Point(originalImage.cols,grabbedRows[i]+final_rows_width[i]/5))).clone();
   // imshow("",roiLine);
   // waitKey(0);
    //cvtColor(roiLine,roiLine,CV_BGR2GRAY);
    convert<<"C:\\example\\grabbed\\img_"<<i+1<<".png";
    //Mat newROI=imread(convert.str(),0);
    //segmentDigits(newROI,textDigits,all_columns); // THIS SHOULD NOT BE HERE


    //imwrite(convert.str(),roiLine);
    convert.str("");
   if(!flag){
    //convert<<"[Row :"<<i+1<<"]";
    //warning(convert.str(),0xF9);
    //convert.str("");
   }
    vector<int> result=segmentDigits(roiLine,textDigits,all_columns);
    //cout<<"\n:::::::::::: size: "<<result.size()<<endl;
    if(tries==9) warning("[ERROR 04] Reading Failed!",0xe7);
    if(result.size()==0 && tries<10){
        i--;
        flag=true;
        tries++;
        continue;
    }
    flag=false;
    tries=0;

    result.clear();
   // textDigits.clear();
   }

}
// ################################################ SEGMENT NATIONAL CODE ##############################################################
std::vector<int> segmentation::segmentNationalCode(const Mat &src){
    characterRecognition OCR;
    vector<int> result,column_values,character_places,character_places2;
    Mat hist,ori=src.clone();
    if (src.channels()==3)
        cvtColor(src,hist,CV_BGR2GRAY);
    else
    hist=src.clone();

    threshold(hist,hist,0,128,THRESH_OTSU);
    hist=hist==0;

    float avgheight=0,height;
    for (int i=0; i<hist.cols; ++i){
        height=sum(hist.col(i))[0]/255;
        avgheight+=height;

        column_values.push_back(height);
    }
    avgheight/=src.cols;


    for(int i=1; i<column_values.size()-1; ++i){
        if(column_values[i]>=avgheight && column_values[i+1]<avgheight){
    character_places.push_back(i);
        } else if(column_values[i]<avgheight && column_values[i+1]>=avgheight){
    character_places.push_back(i+1);
        }
        //line(ori,Point(i,0),Point(i,5*avgheight),Scalar(0,0,255));
    }
    int width=character_places[1]-character_places[0];
    //cout<<"WIDTH : "<<width<<endl;
    for (int i=0; i<character_places.size()-1 ;++i){
        if(character_places[i+1]-character_places[i]>1 )
         character_places2.push_back(character_places[i]);
        if(character_places[i+1]-character_places[i]>3*width) break;
    }
    ostringstream convert,address2;
    convert<<"NATIONAL CODE: ";
    int m=0;
    for (int i=0; i<character_places2.size() && m<10;i+=2){

        address2<<"C:\\example\\grabbed\\founded\\s"<<20+i<<".png";
        //line(ori,Point(character_places2[i],0),Point(character_places2[i],src.rows),Scalar(0,0,255),1);
        //line(ori,Point(character_places2[i+1],0),Point(character_places2[i+1],src.rows),Scalar(255,0,0),1);
        if(i<character_places2.size()-1){
        Mat roi=src(Rect(Point(character_places2[i],0),Point(character_places2[i+1],src.rows))).clone();
        //imwrite(address2.str(),roi);
        address2.str("");
        int res=OCR.charRecognitionANN(roi);
        convert<<res;
        result.push_back(res);
        m++;
        }

    }
    if(result.size()!=10){
        warning("[ERROR : 03 ] ID Nomber Acquisition failed! ",0x27);
        warning(convert.str(),0x27);
    }
    else{
        warning(convert.str(),0x0e);
    }

    //imshow("",ori);
    //waitKey(0);
    if(checkIfTheCodeIsValid(result)){
        warning("[Status OK] National Code is Valid",0x02);
    } else{
        warning("[Status ERRORNEUS] National Code is not valid",0x04);
    }
    return result;

}

// ############################################FIND ROW BLOCKS##########################################################################
void segmentation::findRows(const Mat &src, float &averageWidth, vector<int> &maximum_rows, vector<int> &details_rows, vector<int> &final_rows_width){
    Mat image_canny,image_with_rows;
    vector<int> submitted_rows,center_locs;
    Sobel(src,image_canny,CV_8U,1,0);
    //Sobel(image_canny,image_canny,CV_8U,0,1);
    //Canny(image_canny,image_canny,120,350);
    image_with_rows=image_canny.clone();
    cvtColor(image_with_rows,image_with_rows,CV_GRAY2BGR);
    int width,nextWidth,average=0;
    for (int r=0 ; r<src.rows ; ++r){
        width=sum(image_canny.row(r))[0]/255;
        submitted_rows.push_back(width);
        average+=width;
      }
    average/=src.rows;


    for (int r=0 ; r<(int)submitted_rows.size() ; ++r){
        width=submitted_rows[r];
        nextWidth=submitted_rows[r+1];
        /*if(width>=average){
        line(image_with_rows,Point(0,r),Point(2*average,r),Scalar(255,0,0),1);
        }*/
        if((width>=average && nextWidth<average)){
        maximum_rows.push_back(r);
        final_rows_width.push_back(submitted_rows[r]);
        //line(image_with_rows,Point(0,r),Point(6*average,r),Scalar(0,0,255),1);
        } else if((width<average && nextWidth>=average)) maximum_rows.push_back(r);
    }
   averageWidth=0;
    for (int i=0; i<(int)maximum_rows.size();i+=2) averageWidth+=maximum_rows[i+1]-maximum_rows[i];
    averageWidth/=maximum_rows.size()/2;

    for(int i=0 ; i<(int)maximum_rows.size();i+=2){
        int maxLoc=maximum_rows[i+1]+maximum_rows[i]; maxLoc/=2;

        if((maximum_rows[i+1]-maximum_rows[i])>=2*averageWidth || maximum_rows[i+1]-maximum_rows[i]<.3*averageWidth) {
            continue;
        }
         center_locs.push_back(maxLoc);
        }
        int flag=0;
        maximum_rows.clear();
        for(int i=0; i<(int)center_locs.size()-1;++i){

        if (flag<=1){
        //line(image_with_rows,Point(0,center_locs[i]-averageWidth),Point(src.cols,center_locs[i]-averageWidth),Scalar(0,255,255),1);
        //line(image_with_rows,Point(0,center_locs[i]+averageWidth),Point(src.cols,center_locs[i]+averageWidth),Scalar(255,0,255),1);
        line(image_with_rows,Point(0,center_locs[i]),Point(src.cols,center_locs[i]),Scalar(0,255,255),2);
        if(flag==0){
        details_rows.push_back(center_locs[i]);

        } else if(flag==1)
        maximum_rows.push_back(center_locs[i]);
        //imwrite("C:\\example\\grabbed\\row.png",roiLine);
        }
        if (center_locs[i+1]-center_locs[i]>4*averageWidth) {flag++;}
    }


}
// ################################################LOCATE PHOTO######################################################################
void segmentation::locatePhoto(const Mat &src, std::vector<int> &details_rows, std::vector<int> &Coords){
int x1,y1,x2,y2;
x1=10;

x2=originalImage.cols/7;
y1=details_rows[0];
//int index=details_rows.size()-1;
y2=details_rows.back();
Mat PhotoID=originalImage(Rect(Point(x1,y1),Point(x2,y2))).clone();
Coords.push_back(x1);
Coords.push_back(x2);
Coords.push_back(y1);
Coords.push_back(y2);
//imshow("",PhotoID);
//waitKey(0);



}
// ########################################################SEGMENT DIGITS IN A ROW##############################################################
std::vector<int> segmentation::segmentDigits(const Mat &src, const std::vector<int> &textArea, std::vector<int> all_columns){
    characterRecognition OCR;
    Mat hist=src.clone(),binary;
    ostringstream outStream;
    vector<int> columnValues,charachterBlocks,result,output;
    // # PRE-PROCESSING

    if(src.channels()==3) cvtColor(src,binary,CV_BGR2GRAY);
    else binary=src.clone();

    Sobel(binary,binary,CV_8U,0,1);
    //Canny(binary,binary,128,350);
    threshold(binary,binary,128,255,THRESH_BINARY);
    //morphologyEx(binary,binary,MORPH_OPEN,Mat());
    //binary=binary==0;
    float avgHeight=0;
    for (int c=0 ; c < binary.cols ; ++c){
    int height=sum(binary.col(c))[0]/255;
    avgHeight+=height;
//    line(hist,Point(c,0),Point(c,height),Scalar(255,0,0));
    columnValues.push_back(height);
    }
    avgHeight/=binary.cols;
    //line(hist,Point(0,avgHeight),Point(binary.cols,avgHeight),Scalar(0,0,255),3);

    for (int i=0; i<columnValues.size() ; ++i){
    if( !(i>textArea[0] && i<textArea[1])){
        if((columnValues[i]>=avgHeight && columnValues[i+1]<avgHeight))
        charachterBlocks.push_back(i);
        else if(columnValues[i]<avgHeight && columnValues[i+1]>=avgHeight)
        charachterBlocks.push_back(i+2);
    }
}
    //charachterBlocks.clear();
    float charAvgWidthRef=0;
    float charAvgWidth;
    characterWidthRecognition(charachterBlocks,result,charAvgWidth,charAvgWidthRef);
    charAvgWidthRef=charAvgWidth;
    charachterBlocks.clear();
//cout<<"columns size: "<<all_columns.size()<<" , average width: "<<charAvgWidthRef <<endl;
for (int k=0;k<all_columns.size()-1;k++){
        bool flag=false;
        for (int i=all_columns[k]; i<all_columns[k+1] ; ++i){
        if( !(i>textArea[0] && i<textArea[1])){
            if((columnValues[i]>=avgHeight && columnValues[i+1]<avgHeight))
            charachterBlocks.push_back(i);
            else if(columnValues[i]<avgHeight && columnValues[i+1]>=avgHeight)
            charachterBlocks.push_back(i+2);
        if(i>textArea[1]) flag=true;
        //line(hist,Point(charachterBlocks[k],0),Point(charachterBlocks[k],hist.rows),Scalar(0,0,255),1);
        }
    }
        if(!reportHtml){
        if(charachterBlocks.size()==0){
            //outStream<<" , - ";
            outStream<<"<td></td>";
            continue;}
        //else outStream<<" , ";
        } else{
            if(charachterBlocks.size()==0){
                outStream<<" , - ";

                continue;}
            else outStream<<" , ";


        }
          ostringstream convert;
          string PATH;
          result.clear();
          convert.str("");
    characterWidthRecognition(charachterBlocks,result,charAvgWidth,charAvgWidthRef);
    if(result.size()==0) continue;

    for(int i=0 ; i<result.size(); i+=2){
        Mat detectedCharacter=hist(Rect(Point(result[i],0),Point(result[i+1],hist.rows))).clone();
        PATH = "C:\\example\\grabbed\\founded\\img_";
        //convert.str("");
        //convert<<PATH<<i<<"_"<<k<<".jpg";
        int res=OCR.charRecognitionANN(detectedCharacter);

        convert<<res;

    }
    std::istringstream ss(convert.str());
    int resNo;
    ss>>resNo;
    if (!flag)
    resNo=compareIt(resNo);
   if(!reportHtml){
       outStream<<"<td>"<<resNo<<"</td>";
   } else{
       outStream<<resNo;
   }
    //cout<<resNo;
    output.push_back(resNo);
    charachterBlocks.clear();
    //result.clear();
}
    if(output.size()!=0){
        if(!reportHtml){
        cout<<"<tr>"<<outStream.str();
        //cout<<"\n";
        cout<<"</tr>";
        } else{
            cout<<outStream.str();
            cout<<"\n";
            //cout<<"</tr>";
        }
    }

    return output;
    //   imshow("Histogram",hist);

      // waitKey(0);
}
// #############################################FIND CHARACTER WIDTH ###############################################################
void segmentation::characterWidthRecognition(std::vector<int> &vec, std::vector<int> &result,float &charAvgWidth, float &charAvgWidthRef){
    float currentWidth;
    int   effectiveCharacters=0;
    charAvgWidth=0;
    if(charAvgWidthRef==0){
    for (int i=0 ; i<vec.size() ; i+=2 ){
currentWidth=vec[i+1]-vec[i];
charAvgWidth+=currentWidth;
    }

    charAvgWidth/=vec.size()/2;
} else charAvgWidth=charAvgWidthRef;

    for (int i=0 ; i<vec.size() ; i+=2){
currentWidth=currentWidth=vec[i+1]-vec[i];
if(currentWidth<=1) continue;
if(currentWidth<=(int)2*charAvgWidth){
    result.push_back(vec[i]);
    result.push_back(vec[i+1]);
} else if(currentWidth>charAvgWidth && currentWidth<=(int)4*charAvgWidth){
    result.push_back(vec[i]);
    result.push_back((vec[i]+vec[i+1])/2);
    result.push_back(1+(vec[i]+vec[i+1])/2);
    result.push_back(vec[i+1]);
}
    }
    //cout<<"Charavgwidth: "<<charAvgWidth<<endl;

}

// #############################################FIND TEXT AREA #####################################################################
std::vector<int> segmentation::findTextArea(cv::Mat const& src,std::vector<int> &all_columns){
    std::vector<int> result;
    Mat hist=src.clone();
    //int top,bottom,left,right;
    Mat resizeImage;
    if(src.channels()!=1) cvtColor(src,resizeImage,CV_BGR2GRAY);
    else resizeImage=src.clone();
    Sobel(resizeImage,resizeImage,CV_8U,1,0);
    //Sobel(resizeImage,resizeImage,CV_8U,0,1);
    //Mat element1(2,2,CV_8U,cv::Scalar(1));
    threshold(resizeImage,resizeImage,128,255,THRESH_OTSU);
    //erode(resizeImage,resizeImage,element1);
    // # Histogram
    float average;
    horizontalHist(resizeImage,result,all_columns,average,6);
    // # FIND THE LARGEST DISTANCE IN columnValues, IT WILL BE WHERE TEXT AREA IS PLACED
    /*  for(int i=0; i<all_columns.size()-1;++i)
        line(hist,Point(all_columns[i],0),Point(all_columns[i],hist.rows),Scalar(255,0,0),3);
      cout<<"Number of cols: "<<all_columns.size()<<endl;
      imshow("",hist);
      waitKey(0);
*/

    return result;

}
// ###############################################COMPUTE HORIZONTL DATAGRAM########################################################
void segmentation::horizontalHist(const Mat &src, std::vector<int> &columnData,std::vector<int> &all_columns ,float &average,float t){
    std::vector<int> result,columnValues,fieldsSpaces,textArea,refinedColumnValues;
    average=0;
    for(int c=0; c<src.cols ;++c){
    int height=sum(src.col(c))[0]/255;
    columnValues.push_back(height);
    average+=height;
    }
    average/=src.cols;

    for (int i=0; i<columnValues.size();++i){
        if(columnValues[i]>t*average){
            fieldsSpaces.push_back(i);
        }
    }
    // Refine it
    refinedColumnValues.push_back(fieldsSpaces[0]);

    for(int i=1;i<fieldsSpaces.size()-1;++i)
    {
       //cout<<"DIst: "<<fieldsSpaces[i+1]-refinedColumnValues.back()<<endl;
        if(fieldsSpaces[i]-refinedColumnValues.back()>10)
            refinedColumnValues.push_back(fieldsSpaces[i]);
    }

    int maxDistance[3];
    largestDistance(refinedColumnValues,textArea,maxDistance);

    columnData=textArea;
    all_columns=refinedColumnValues;
    //for(int i=0; i<columnData.size();++i) line(originalImage,Point(columnData[i],0),Point(columnData[i],100),Scalar(255,0,255),1);
    //imshow("",originalImage);
    //waitKey(0);
}
// ############################################## FIND MAXIMUM VALUE IN A VECTOR ##################################################
void segmentation::largestDistance(std::vector<int> &vec, std::vector<int> &out, int (&maxValues)[3]){
    // # maxvalues key>=0 : MAXIMUM DISTANCE, key=>1 : MINIMUM DISTANCE , key=>2 : AVERAGE DISTANCE

    int maxIndex=0,currentVal=0,minimumDistance=1000;
    float averageDistance=0;
    int maxVal=0;
    for(int i=0 ; i<vec.size()-1;i++){
        currentVal=vec[i+1]-vec[i];
       // cout<<"current value: "<<currentVal<<" , where: "<<vec[i]<<" -- "<<vec[i+1]<<endl;
        if(currentVal>maxVal)
        {
        maxVal= currentVal;
        maxIndex=i;
        }
        averageDistance+=currentVal;
        minimumDistance=currentVal<minimumDistance ? currentVal : minimumDistance;
    }
    averageDistance/=vec.size()/2;
    maxValues[0]=maxVal;
    maxValues[1]=minimumDistance;
    maxValues[2]=averageDistance;
    if(maxIndex<vec.size()-1){
        out.push_back(vec[maxIndex]);
        out.push_back(vec[maxIndex+1]);

    } else{
        out.push_back(0); out.push_back(0);
    warning("Error 02 : TEXTAREA NOT FOUND");
    }
}

// ###############################################FIND BOUNDS#######################################################################
std::vector<int> segmentation::findBounds(const Mat &src){
    std::vector<int> output;
    // src should be B&W
    // This function reacts to 1s as white areas

    int leftBound=0,rightBound=src.cols,topBound=0,bottomBound=src.rows;
    // TopBound
    for(int r=0;r<src.rows;++r){
    if(sum(src.row(r))[0]!=0) {topBound=r; break;}
    } // Bottom Bound
    for(int r=src.rows-1;r>=0;--r){
    if(sum(src.row(r))[0]!=0) {bottomBound=r; break;}
    } // Left Bound
    for(int c=0;c<src.cols;++c){
    if(sum(src.col(c))[0]!=0) {leftBound=c; break;}
    }  // Right Bound
    for(int c=src.cols-1;c>=0;--c){
    if(sum(src.col(c))[0]!=0) {rightBound=c; break;}
    }
    output.push_back(leftBound);
    output.push_back(rightBound);
    output.push_back(topBound);
    output.push_back(bottomBound);
    return output;
}

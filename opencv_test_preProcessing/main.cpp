#include "preProcessing.h"

int main(int argc, char* argv[]){
    string command1="-i",filePath;
    if(argc<=1 || argc>3){
        cout<<"[Error 01]\nthere is no input file!";
        return -1;
    } else if(argc==2){
    cout<<"[Error 02]\n"<<argv[1]<<" is not a valid input parameter!";
        return -1;
    } else if(argc==3){
    if(command1.compare(argv[1])!=0){
    cout<<"[Error 03]\ninput file is not exactly defined!";
        return -1;
    }
    }

    alignImage align;
    filePath=argv[2];
    if(!align.exists_file(filePath)){
     cout<<"[Error 04]\nFile not found!";
     return -2;
    }
    float averageDistortion,tmpDistortion=0;

    Mat mainImage,cdstInv,cdst,img=imread(filePath);
    if(img.cols<600 || img.rows<600){
        cout<<"[Error 07]\nImage resolution is not acceptable!";
        return -2;
    }
    mainImage=img.clone();
    //blur(img,img,Size(3,3));
    align.start(img,img,averageDistortion);
    if(abs(averageDistortion)>10){
        cout<<"[Error 05]\nSystem is not able to read this file!";
        return -2;
    }
    ostringstream io;
    io<<filePath<<".jpg";
    imwrite(io.str(),img);
    return 0;
}

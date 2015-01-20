
//#include <QCoreApplication>
#include "flowcontrol.h"
#include "segmentation.h"




int main(int argc, char *argv[])
{
    clock_t t;
    t=clock();
    flowControl flow;
    bool isHtmlReportEnabled=false;

    segmentation seg;
    system("cls");
    string command1="-i";
    string command2="-h";
    string filePath;
    if(argc<=1) flow.warning("NO INPUT ARGUMENT",12);
    if(argc>1) {
        string str=argv[1];
        if(command1.compare(str)==0){
        if(argc<2) flow.warning("ERROR: NO INPUT FILE",12);
        else if (argc==3) filePath=argv[2];
        else if (argc==4) {
        string str2=argv[3];

        if(str2.compare(command2)==0){
           // cout<<str2<<endl;
            isHtmlReportEnabled=true;
        }
        }
        else flow.warning("Error: Too many input arguments",12);

        }else{

            cout<<"ERROR: Command "<<argv[1]<<" is not standard";
        }
    }
    if(!flow.exists_file(filePath)) {
        flow.warning("File Not Found!",0xFC);
        filePath="C:\\example\\test\\test_11.jpg";
        flow.warning("[USING DEFAULT PATH:] "+filePath,14);

    }


    seg.reportHtml=isHtmlReportEnabled;

    Mat image = imread(filePath);
    //resize(image,image,Size(819,1216),0,0);
    seg.image=image.clone();
    seg.start();
    int elapsed=clock()-t;

    cout<<"Elapsed time: "<<elapsed/1000<<" (s) : "<<elapsed%1000<<" (ms) "<<endl;


    return 0;
}

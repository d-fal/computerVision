#ifndef SEGMENTATION_H
#define SEGMENTATION_H


#include <opencv/cv.h>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/core/core.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/ml/ml.hpp>
#include <opencv2/contrib/contrib.hpp>


#include<vector>
#include<cstring>
#include<fstream>
#include <cmath>
#include "time.h"
#define ATTRIBUTES 400  //Number of pixels per sample.16X16
//#define TEST_SAMPLES 1170       //Number of samples in test dataset
#define CLASSES 10
using namespace cv;
using namespace std;
#include "flowcontrol.h"

class flowControl
{
public:
    flowControl();
    void warning(std::string err, int k=7);
    bool exists_file (const std::string& name);
    int hammingDist(int a, int b);
    int compareIt(int a);
    bool checkIfTheCodeIsValid(std::vector<int> const& nCode);



};

class segmentation : public flowControl{

public:
    segmentation();
    void start();
    void findRows(cv::Mat const& src, float &averageWidth, std::vector<int> &maximum_rows, std::vector<int> &details_rows, vector<int> &final_rows_width);
    void locatePhoto(cv::Mat const& src,std::vector<int> &details_rows,std::vector<int> &Coords);
    //void findColumns(cv::Mat const&src)
    std::vector<int> findBounds(cv::Mat const& src);
    std::vector<int> segmentDigits(cv::Mat const& src , std::vector<int> const& textArea,std::vector<int> all_columns);
    std::vector<int> segmentNationalCode(cv::Mat const& src);
    std::vector<int> findTextArea(cv::Mat const& src, std::vector<int> &all_columns);
    void processStart(std::vector<int> &grabbedRows, const vector<int> &textDigits,  const std::vector<int> &all_columns, float &averageWidth, vector<int> final_rows_width);
    void horizontalHist(cv::Mat const& src, std::vector<int> &columnData, std::vector<int> &all_columns, float &average, float t);
    void largestDistance(std::vector<int> &vec , std::vector<int> &out, int (&maxValues)[3]);
    void characterWidthRecognition(std::vector<int> &vec , std::vector<int> &result, float &charAvgWidth, float &charAvgWidthRef);
    cv::Mat image;
    cv::Mat originalImage;
    bool reportHtml=false;

};

class characterRecognition : public flowControl{
public:
    characterRecognition();
    int charRecognitionANN(const cv::Mat &image);
    void alignPixels(cv::Mat const &image,cv::Mat &result);
    void removeWhitespaces(cv::Mat const &image,cv::Mat &result);
    void deNoise(cv::Mat const &image, cv::Mat &result);
};

#endif // SEGMENTATION_H

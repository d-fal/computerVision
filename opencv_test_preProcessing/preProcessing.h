#ifndef PREPROCESSING_H
#define PREPROCESSING_H


#include <opencv/cv.h>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/core/core.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/ml/ml.hpp>
#include <opencv2/contrib/contrib.hpp>
#include <iostream>
#include<vector>
#include<cstring>
#include<fstream>
#include <cmath>
#include "time.h"
#include "windows.h"

using namespace std;
using namespace cv;

class alignImage
{
    public:
    alignImage() {}
    void alignHorizontal(cv::Mat const& src, float &averageDistortion);
    void start(cv::Mat const&img, cv::Mat &dst, float &averageDistortion);
    cv::Mat image;
    void findDistance(Vec4i &l, int &dist, int &maxDist, float &deviationAngle);
    bool exists_file(const string &name);
};

#endif // PREPROCESSING_H

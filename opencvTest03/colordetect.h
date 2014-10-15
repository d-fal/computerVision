#ifndef COLORDETECT_H
#define COLORDETECT_H
#include "mainwindow.h"
class colorDetect
{
public:

    cv::Mat process(const cv::Mat &image);
    cv::Vec3b getDistance(cv::Vec3b bkr);
    cv::Mat followContours(cv::Mat const&);
    void instantiateValues(int r , int g , int b, int d);
    //cv::Mat drawRectangle(cv::Mat const& image, std::vector<Point);
    std::vector<int> verticalLines(cv::Mat const& image);
private:
    int red;
    int blue;
    int green;
    int dst;
};

#endif // COLORDETECT_H

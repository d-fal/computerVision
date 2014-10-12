#ifndef COLORDETECTOR_H
#define COLORDETECTOR_H
#include "mainwindow.h"
#include "assets.h"
class colorDetector
{
public:

    cv::Mat process(cv::Mat const& image);
    cv::Vec3b getDistance(cv::Vec3b);
    void instantiateValues(int , int , int ,int);
private:
    int red;
    int green;
    int blue;
    int dst;
};

#endif // COLORDETECTOR_H

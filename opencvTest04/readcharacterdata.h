#ifndef READCHARACTERDATA_H
#define READCHARACTERDATA_H
#include "mainwindow.h"
class readCharacterData
{
public:
    readCharacterData();

    void alignPixels(cv::Mat const &image,cv::Mat &result);
    void removeWhitespaces(cv::Mat const &image,cv::Mat &result);
    void deNoise(cv::Mat const &image, cv::Mat &result);
};

#endif // READCHARACTERDATA_H

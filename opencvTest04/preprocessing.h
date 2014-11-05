#ifndef PREPROCESSING_H
#define PREPROCESSING_H
#include "mainwindow.h"
class preprocessing
{
public:
    cv::Mat detectCharacters(const cv::Mat &image);
    preprocessing();
};

#endif // CHARACTERRECOGNITION_H

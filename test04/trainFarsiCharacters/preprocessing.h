#ifndef PREPROCESSING_H
#define PREPROCESSING_H
#include "mainwindow.h"
class preProcessing
{
private:
    cv::Mat binary;
public:
    preProcessing();
    cv::Mat process(cv::Mat const& image);
    std::vector<int> drawHorizontalLines(cv::Mat const& image);
    cv::Mat detectCharacters(cv::Mat const& image);

};

#endif // PREPROCESSING_H

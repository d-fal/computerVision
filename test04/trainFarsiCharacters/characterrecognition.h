#ifndef CHARACTERRECOGNITION_H
#define CHARACTERRECOGNITION_H
#include "mainwindow.h"
class characterRecognition
{
public:
    int charRecognition(cv::Mat const& image);
    characterRecognition();
    int charRecognitionANN(const cv::Mat &image);
private:
    int thresh;
    QString address;
};

#endif // CHARACTERRECOGNITION_H

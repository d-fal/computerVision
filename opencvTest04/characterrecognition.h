#ifndef CHARACTERRECOGNITION_H
#define CHARACTERRECOGNITION_H
#include "mainwindow.h"
struct POIs{
    int radius;
    float xPos;
    float yPos;
    int row;
};
class characterRecognition
{
public:
    characterRecognition();
    std::vector<POIs> detectCharacters(const cv::Mat &src);
    void grabROIS(const cv::Mat &src,std::vector<POIs> interestPoints);
    int topBound;
    int belowBound;
    int leftTextArea;
    int rightTextArea;
    std::vector<int> imgRows;
    std::vector<POIs> alignContours(std::vector<POIs> centers);
    std::vector<POIs> sortPoints(std::vector<POIs> Xorder);

};

#endif // CHARACTERRECOGNITION_H

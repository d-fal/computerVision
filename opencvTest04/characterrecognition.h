

#ifndef CHARACTERRECOGNITION_H
#define CHARACTERRECOGNITION_H
#include "mainwindow.h"


struct POIs{
    float radius;
    float xPos;
    float yPos;
    float row;
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
    int remarksPanel;
    int charRecognitionANN(const cv::Mat &image);
    std::vector<int> imgRows;
    std::vector<POIs> alignContours(std::vector<POIs> centers, std::vector<int> imgRowsx);
    std::vector<POIs> sortPoints(std::vector<POIs> Xorder);
    std::vector<POIs> detectIdNo(const cv::Mat &src);

    cv::Mat originalImage;
private:

};

#endif // CHARACTERRECOGNITION_H

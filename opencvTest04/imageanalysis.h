#ifndef IMAGEANALYSIS_H
#define IMAGEANALYSIS_H
#include "mainwindow.h"

struct histValue{
    int value;
    int Xposition;
   };

class imageAnalysis
{
public:
    imageAnalysis();
    void startIt();
    std::vector<int> findPicture();
    std::vector<int> detectTextarea();
    std::vector<int> makeHistogram(cv::Mat const& scoresBlock);
    std::vector<int> findRows(cv::Mat const& scoresBlock);


private:
    int topMargin;
    int bottomMargin;
    int leftMargin;
    int rightMargin;
    cv::Mat image;
    cv::Mat refImage;
    cv::Mat photoID;

    float refVAspect;
    float refHAspect;
};

#endif // IMAGEANALYSIS_H

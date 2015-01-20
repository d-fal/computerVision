#ifndef HUMOMMENTS_H
#define HUMOMMENTS_H

#include "mainwindow.h"
class humomments
{
public:
    humomments();

    std::vector<float> calculateHuMomments(cv::Mat const& image);
    std::vector<float> calculateCentroids(cv::Mat const& image);
private:
    float m_00;
    float m_01;
    float m_10;
};

#endif // HUMOMMENTS_H

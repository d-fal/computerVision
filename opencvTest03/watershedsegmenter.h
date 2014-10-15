#ifndef WATERSHEDSEGMENTER_H
#define WATERSHEDSEGMENTER_H
#include "mainwindow.h"
class WatershedSegmenter
{
private:
    cv::Mat markers;
public:
    WatershedSegmenter();
    void setMarkers(cv::Mat const &markerImage);
    cv::Mat process(cv::Mat const &image);

};

#endif // WATERSHEDSEGMENTER_H

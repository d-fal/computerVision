#include "watershedsegmenter.h"

WatershedSegmenter::WatershedSegmenter()
{

}

void WatershedSegmenter::setMarkers(Mat const &markerImage){


markerImage.convertTo(markers,CV_32S);
}

cv::Mat WatershedSegmenter::process(Mat const  &image){
    cv::watershed(image,markers);
    return markers;

}

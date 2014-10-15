#include "histogram1d.h"

Histogram1D::Histogram1D()
{
    histSize[0]= 256;
    hranges[0]= 0.0;

    hranges[1]= 255.0;
    ranges[0]= hranges;
    channels[0]= 0;
}

cv::MatND  Histogram1D::getHistogram(const cv::Mat &image) {
cv::MatND hist;
// Compute histogram
cv::calcHist(&image,
1, // histogram from 1 image only
channels, // the channel used
cv::Mat(), // no mask is used
hist, // the resulting histogram
1, // it is a 1D histogram
histSize, // number of bins
ranges // pixel value range
);
return hist;
}

cv::Mat Histogram1D::getHistogramImage(const cv::Mat &image){
// Compute histogram first
cv::MatND hist= getHistogram(image);
// Get min and max bin values
double maxVal=0;
double minVal=0;
cv::minMaxLoc(hist, &minVal, &maxVal, 0, 0);
// Image on which to display histogram
cv::Mat histImg(histSize[0], histSize[0],
CV_8U,cv::Scalar(255));
// set highest point at 90% of nbins
int hpt = static_cast<int>(0.9*histSize[0]);
// Draw a vertical line for each bin
for( int h = 0; h < histSize[0]; h++ ) {
float binVal = hist.at<float>(h);
int intensity = static_cast<int>(binVal*hpt/maxVal);
// This function draws a line between 2 points
cv::line(histImg,cv::Point(h,histSize[0]),
cv::Point(h,histSize[0]-intensity),
cv::Scalar::all(0));
}
return histImg;
}

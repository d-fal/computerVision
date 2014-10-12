#include "assets.h"

void colorReduce(cv::Mat const &image, cv::Mat &out, int div) {

int nl= image.rows; // number of lines
// total number of elements per line
int nc= image.cols * image.channels();
for (int j=0; j<nl; j++) {
// get the address of row j
const uchar* data= image.ptr<const uchar>(j);
uchar* output= out.ptr<uchar>(j);
for (int i=0; i<nc; i++) {
// process each pixel ---------------------
*output++= ((*data++)/div)*div;
// end of pixel processing ----------------
}
}
}

cv::Mat iteratorTest(cv::Mat const &image){
cv::Mat result=image.clone();

    cv::Mat_<cv::Vec3b>::const_iterator it=image.begin<cv::Vec3b>();
    cv::Mat_<cv::Vec3b>::const_iterator itend=image.end<cv::Vec3b>();
    cv::Mat_<cv::Vec3b>::iterator itout=result.begin<cv::Vec3b>();
    // for each pixel
    for ( ; it!= itend; ++it, ++itout) {
    // process each pixel ---------------------
    // compute distance from target color

        cv::Vec3b bkr=*it;

        bkr[0]=bkr[1];

*itout=bkr;
    // end of pixel processing ----------------
    }


return result;
}



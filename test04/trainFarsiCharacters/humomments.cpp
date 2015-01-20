#include "humomments.h"

humomments::humomments()
{

}

std::vector<float> humomments::calculateCentroids(const Mat &image){
    std::vector<float> result;
    m_00=0;
    m_10=0;
    m_01=0;

    for(int j=0;j<image.rows;++j){
    const uchar* current=image.ptr<const uchar>(j);
    for(int i=0;i<image.cols;++i){
    m_00+=(current[i])/255;
    m_01+=j*(current[i]>0);
    m_10+=i*(current[i]>0);

}
    }


  result.push_back(m_00);
  result.push_back(m_10);
  result.push_back(m_01);
//cout<<"m_00 : "<<m_00<<" , m_01: "<<m_01<<endl;
  return result;

}

std::vector<float> humomments::calculateHuMomments(const Mat &image){
    std::vector<float> centroids=calculateCentroids(image);
    std::vector<float> result;
    int x=centroids.at(1)/centroids.at(0);
    int y=centroids.at(2)/centroids.at(0);

    //cout<<"centroids: ("<<x<<","<<y<<"), "<<image.cols<<" x "<<image.rows<<endl;

    float mu[4][4]={0};
    float etha[4][4]={0};

    for(int j=0;j<image.rows;++j){
    const uchar* current=image.ptr<const uchar>(j);
        for(int i=0;i<image.cols;++i){
           for(int p=0;p<4;++p){
           for(int q=0;q<4;++q){

     mu[p][q]+=pow((j-y),p)*pow((i-x),q)*(current[i]>0);

           }
            }

        }
    }
for(int p=0;p<4;++p){
    for(int q=0;q<4;++q){
        float power=(p+q+2);
        power/=2;

etha[p][q]=mu[p][q]/pow(mu[0][0],power);
//cout<<p<<" , "<<q<<" th : "<<etha[p][q]<<endl;
    }
}
float hu;
// 1st
hu=etha[2][0]+etha[0][2];
result.push_back(hu);
//2nd
hu=pow(etha[2][0]-etha[0][2],2)+4*pow(etha[1][1],2);
result.push_back(hu);
//3rd
hu=pow(etha[3][0]-3*etha[1][2],2)+3*pow(etha[2][1]-etha[0][3],2);
result.push_back(hu);
//4th
hu=pow(etha[3][0]+etha[1][2],2)+pow(etha[2][1]+etha[0][3],2);
result.push_back(hu);
//5th
hu=(etha[3][0]-3*etha[1][2])*(etha[3][0]+etha[1][2])*(pow(etha[3][0]+etha[1][2],2)-3*pow(etha[2][1]+etha[0][3],2))+
        (3*etha[2][1]-etha[0][3])*(etha[2][1]+etha[0][3])*(3*pow(etha[3][0]+etha[1][2],2)-pow(etha[2][1]+etha[0][3],2));
result.push_back(hu);
//6th
hu=(etha[2][0]-etha[0][2])*(pow(etha[3][0]+etha[1][2],2)-pow(etha[2][1]+etha[0][3],2))+
        4*etha[1][1]*(etha[3][0]+etha[1][2])*(etha[2][1]+etha[0][3]);
result.push_back(hu);
//7th
hu=(3*etha[2][1]-etha[0][3])*(etha[3][0]+etha[1][2])*(pow(etha[3][0]+etha[1][2],2)-3*pow(etha[2][1]+etha[0][3],2))-
        (etha[3][0]-3*etha[1][2])*(etha[2][1]+etha[0][3])*(3*pow(etha[3][0]+etha[1][2],2)-pow(etha[2][1]+etha[0][3],2));
result.push_back(hu);

//for(int i=0;i<result.size();++i) cout<<i+1<<"th: "<<result[i]<<endl;

return result;
}

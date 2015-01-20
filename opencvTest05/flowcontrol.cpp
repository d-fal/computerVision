#include "segmentation.h"
#include "flowcontrol.h"

flowControl::flowControl()
{
}


void flowControl::warning(string err, int k)
{
     HANDLE hConsole; // 7: white  9 blue 4: red 14: yellow
     SetConsoleTextAttribute(hConsole,20);
     hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
     SetConsoleTextAttribute(hConsole, k);
     cout<<err<<endl;
     SetConsoleTextAttribute(hConsole, 7);


}

bool flowControl::exists_file(const string &name){
    ifstream f(name.c_str());
    if (f.good()) {
        f.close();

        return true;
    } else {
        f.close();

        return false;
    }

}



int flowControl::compareIt(int a){

int b=a;
  if(a<100 && a>20) { //TWO DIGITS
b=hammingDist(a,2);
  } else if(a<1000 && a>=100) b=hammingDist(a*10+50,4);
    else if(a<10000 && a>=1000) b=hammingDist(a,4);
    else if(a<100000 && a>=10000) b=hammingDist(a/10,4);
  else if(a<1000000 && a>=100000) b=hammingDist(a/100,4);
  else if(a<10000000 && a>=1000000) b=hammingDist(a/1000,4);
   else if(a<100000000 && a>=10000000) b=hammingDist(a/10000,4);
  else if(a<1000000000 && a>=100000000) b=hammingDist(a/100000,4);

return b;
}


int flowControl::hammingDist(int a, int b){

    float reference[b];
    //reference[0]=.1; reference[1]=.2; reference[2]=.3; reference[3]=0;

    for (int i=0 ; i<b ; i++){
        reference[i]=(1+i);
        reference[i]/=(b);

    }
    float minDist=100; float dist=0; int index=0;
    for(int n=20*pow(100,-1+b/2);n>=10*pow(100,-1+b/2);--n){
        dist=0;

        int r=1;
    for(int i=0;i<b;++i){
        int d1,d2,d;
        d1=a/r; d1%=10;
        d2=n/r; d2%=10;
        r*=10;
        d=abs(d1-d2);

        dist+=(d)*reference[i];
    }

    if (dist<minDist){
    minDist=dist;
    index=n;
    }
    }

    return index;
}

bool flowControl::checkIfTheCodeIsValid(const std::vector<int> &nCode){
    int sumValue=0,remainder;
for (int i=0 ; i<=8 ; ++i){
    sumValue+=nCode[i]*(10-i);
}
    remainder=sumValue%11;
    if(remainder<2 && remainder==nCode[9]) return true;
    if(remainder>=2){
        if(11-remainder==nCode[9]) return true;
    }
return false;
}

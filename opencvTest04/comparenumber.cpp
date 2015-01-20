#include "comparenumber.h"

compareNumber::compareNumber()
{
}

int compareNumber::compare(int a){

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


int compareNumber::hammingDist(int a, int b){

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

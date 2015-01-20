#include "mythread.h"
#include "txrxfuncs.h"

using namespace std;
myThread::myThread(QObject *parent) :
    QThread(parent)
{

}

void myThread::action(const HANDLE &comport2){
    comport=comport2;
    run();

}

void myThread::run(){
    TxRxFuncs txrx;
    while(true){
        sleep(100);
        txrx.recieveByte(comport);
    }


}

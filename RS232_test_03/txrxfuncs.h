#ifndef TXRXFUNCS_H
#define TXRXFUNCS_H
#include "windows.h"
#include <iostream>
#include <stdio.h>
#include <conio.h>

#include "mythread.h"
using namespace std;
class TxRxFuncs
{

public:

    TxRxFuncs();
    void sendByte(BYTE *OUTBUFFER, int dataLen,HANDLE const & comport);
    void recieveByte(HANDLE const & comport);
};

#endif // TXRXFUNCS_H

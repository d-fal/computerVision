#include "windows.h"
#include <iostream>
#include <string>


using namespace std;

int main(int argc , char* argv[]){
    HANDLE serialHandle;
    serialHandle=CreateFile("\\\\.\\COM1",GENERIC_READ | GENERIC_WRITE , 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
    DCB serialParams = {0};
    serialParams.DCBlength=sizeof(serialParams);

    GetCommState(serialHandle,&serialParams);
    serialParams.BaudRate = baudrate;
    serialParams.ByteSize = byteSize;
    serialParams.StopBits = stopBits;
    serialParams.Parity = parity;
    SetCommState(serialHandle, &serialParams);

    // Set timeouts
    COMMTIMEOUTS timeout = { 0 };
    timeout.ReadIntervalTimeout = 50;
    timeout.ReadTotalTimeoutConstant = 50;
    timeout.ReadTotalTimeoutMultiplier = 50;
    timeout.WriteTotalTimeoutConstant = 50;
    timeout.WriteTotalTimeoutMultiplier = 10;

    SetCommTimeouts(serialHandle, &timeout);

    return 0;
}

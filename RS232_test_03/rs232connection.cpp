#include "rs232connection.h"


HANDLE comport  = NULL;
TxRxFuncs txrx;
rs232Connection::rs232Connection()
{
}


void sendit(string str){
    BYTE OUTBUFFER[47];
    OUTBUFFER[0]=0x75;
    OUTBUFFER[1]=0x92;
    OUTBUFFER[2]=0xE7;
    BYTE DATA1[3]={0x55,0x80,0xD5};
    BYTE DATA2[11]={0x5E,0x80,0xDE,0xB2,0xB0,0xB0,0xB2,0xB0,0xB1,0xB1,0xB7};
    BYTE DATA3[3]={0x55,0x80,0xD5};
    BYTE DATA4[11]={0x5E,0x80,0xDE,0xB2,0xB0,0xB0,0xB2,0xB0,0xB1,0xB1,0xB7};
    BYTE DATA5[28]={0x55,0x80,0xD5,
                    0x5E,0x80,0xDE,0xB2,0xB0,0xB0,0xB2,0xB0,0xB1,0xB1,0xB7,
                    0x55,0x80,0xD5,
                    0x5E,0x80,0xDE,0xB2,0xB0,0xB0,0xB2,0xB0,0xB1,0xB1,0xB7};
    txrx.sendByte(OUTBUFFER,3,comport);
    //txrx.recieveByte(comport);

  //  WaitCommEvent(comport, EV_RXCHAR);

    //txrx.sendByte(DATA1,3,comport);

//    Sleep(1000);
    //txrx.sendByte(DATA2,11,comport);

    //txrx.sendByte(DATA3,3,comport);

    txrx.sendByte(DATA5,28,comport);
    //txrx.recieveByte(comport);
}

void recieveIt(string str){
while(true)
txrx.recieveByte(comport);


}

void rs232Connection::makeAConnnection(){


    cout<<"Here!!!"<<endl;



    int bStatus;


    DCB          comSettings;          // Contains various port settings
    COMMTIMEOUTS CommTimeouts;
    FillMemory(&comSettings,sizeof(comSettings),0);
    //strcpy(&OUTBUFFER[0], "The quick brown fox jumped over the lazy dog. \n\r\0");
    // Open COM port
    if ((comport =
         CreateFileA("\\\\.\\COM3", GENERIC_READ | GENERIC_WRITE, // for reading and writing
                    0,0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,NULL)) == INVALID_HANDLE_VALUE)
    {
        // error processing code goes here
    }

    cout<<"Port is open!"<<endl;

    GetCommState(comport, &comSettings);
    SetCommMask(comport,EV_BREAK | EV_CTS | EV_DSR | EV_ERR | EV_RING | EV_RLSD | EV_RXCHAR |  EV_TXEMPTY );
    SetupComm(comport,1024,512);
    CommTimeouts.ReadIntervalTimeout         = -1;
    CommTimeouts.ReadTotalTimeoutMultiplier  =  0;
    CommTimeouts.ReadTotalTimeoutConstant    =  0;
    CommTimeouts.WriteTotalTimeoutMultiplier =  0;
    CommTimeouts.WriteTotalTimeoutConstant   =  5000;

    PurgeComm(comport,PURGE_RXABORT | PURGE_RXCLEAR | PURGE_TXABORT | PURGE_TXCLEAR);

    bStatus = SetCommTimeouts(comport,&CommTimeouts);

    comSettings.BaudRate = 115200;
    comSettings.DCBlength=sizeof(comSettings);
    comSettings.StopBits = ONESTOPBIT;
    comSettings.ByteSize = 8;
    comSettings.Parity   = NOPARITY;
    comSettings.fParity  = FALSE;
    comSettings.XoffLim = 256;
    comSettings.XonLim = 256;
    comSettings.EofChar = 0x1A;
    comSettings.fDtrControl = DTR_CONTROL_ENABLE;
    comSettings.XoffChar = 0x13;
    comSettings.XonChar = 0x11;
    comSettings.EvtChar = 0x00;
    comSettings.ByteSize = 8;
    comSettings.fBinary = true;




    bStatus = SetCommState(comport, &comSettings);





   thread t1(recieveIt,"1");
    thread t2(sendit,"2");






    //Sleep(100);




   t2.join();
   t1.join();

    CloseHandle(comport);

}

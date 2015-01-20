#include "txrxfuncs.h"

TxRxFuncs::TxRxFuncs()
{
}

void TxRxFuncs::sendByte(BYTE *OUTBUFFER, int dataLen, HANDLE const & comport){
    //cout<<"Sending!"<<endl;
    DWORD        bytes_written = 0;    // Number of bytes written to the port

    int bStatus = WriteFile(comport,
    OUTBUFFER,      // Outgoing data
    dataLen,              // Number of bytes to write
    &bytes_written,  // Number of bytes written
    NULL);
    cout<<bytes_written<<" bytes written!"<<endl;
    SetCommMask(comport,EV_BREAK | EV_CTS   | EV_DSR | EV_ERR | EV_RING |
                EV_RLSD | EV_RXCHAR |  EV_TXEMPTY );

    }

void TxRxFuncs::recieveByte(const HANDLE &comport){
    SetCommMask(comport,EV_BREAK | EV_CTS   | EV_DSR | EV_ERR | EV_RING |
                EV_RLSD | EV_RXCHAR |  EV_TXEMPTY );
    char INBUFFER[500];

        DWORD dwCommEvent;
       strcpy(INBUFFER, "");
       if (!SetCommMask(comport, EV_RXCHAR)){

       }
       DWORD        bytes_read    = 0;    // Number of bytes read from port

       if(WaitCommEvent(comport,&dwCommEvent,NULL)){
       BOOL bStatus = ReadFile(comport,   // Handle
                    INBUFFER,            // Incoming data
                    500,                  // Number of bytes to read
                    &bytes_read,          // Number of bytes read
                    NULL);
       if(bStatus && bytes_read!=0 ){
           cout<<INBUFFER<<endl;
       }

       //Sleep(100);
}

}



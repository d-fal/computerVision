#include "serial.h"
#include <thread>
#include "controlcommands.h"

BOOL readData(string str);
void charToHex(char *str);
controlCommands controlComms;
CSerial serial;
int main(int argc , char* argv[]){

    for (int portNo = 0; portNo<5 ; ++portNo){
        if(serial.findAvailablePorts(portNo))
            cout<<"COM"<<portNo<<" available!"<<endl;
    }


    if(serial.Open(3,115200)){
        cout<<"Connection initialized!"<<endl;
    }
      char szMessage[3] = {0x75, 0x92 , 0xE7};

      serial.SendData(szMessage,3);
      char* lpBuffer = new char[100];
      char setOn[6] = {0x52, 0x86 , 0xD4 , 0x5A , 0x80 , 0xDA};
      Sleep(300);
      serial.ReadData(lpBuffer , 30);
      if(controlComms.checkValidity(lpBuffer,20)!=0){
          cout<<"Device is ready!"<<endl;
      } else{
          cout<<"Device is not ready!"<<endl;

      }
      Sleep(1000);



      //Sleep(1000);
      serial.SendData(setOn,sizeof(setOn));
      Sleep(300);



      thread t1(readData,"");

    t1.join();
    serial.Close();
    printf("\n");
    return 0;
}

BOOL readData(string str){

    char* lpBuffer = new char[100];

    while(true){


        if(serial.ReadDataWaiting()){
            try{
        int bytesRead = serial.ReadData(lpBuffer,30);
        controlComms.printChars(lpBuffer);
        Sleep(500);
        delete []lpBuffer;
            } catch(exception ex){

            }
        }
    Sleep(100);

    }
    if(serial.IsOpened()) serial.Close();

}



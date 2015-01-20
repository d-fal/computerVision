#ifndef CONTROLCOMMANDS_H
#define CONTROLCOMMANDS_H

#include "serial.h"
class controlCommands
{
public:
    controlCommands();

    void printChars(char *str);
    int  checkValidity(char *str, int len);
    int masterCommand(char *str);
    void clientCommand(char* str, int &clientNo , int &choice , bool &validity);

private:
   char start_response[15] =  {0x78 , 0x93 , 0xEA , 0x81 , 0x80 , 0x78 , 0x93 , 0xEA , 0x81 , 0x80 , 0x78 , 0x93 , 0xEA , 0x81 , 0x80};

};

#endif // CONTROLCOMMANDS_H

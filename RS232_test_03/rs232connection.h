#ifndef RS232CONNECTION_H
#define RS232CONNECTION_H
#include <thread>
#include "txrxfuncs.h"

class rs232Connection
{
public:
    rs232Connection();
    void makeAConnnection();


protected:
    void run();

};

#endif // RS232CONNECTION_H

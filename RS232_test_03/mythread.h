#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include "txrxfuncs.h"
class myThread : public QThread
{
    Q_OBJECT
public:
    int dbNo;
    explicit myThread(QObject *parent = 0);


void action(HANDLE const & comport2);
void run();
private:
HANDLE const & comport;


};



#endif // MYTHREAD_H

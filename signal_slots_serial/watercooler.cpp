#include "watercooler.h"

waterCooler::waterCooler(QObject *parent) :
    QObject(parent)
{
    Person Joe;
    Person Jenny;

    connect(&Joe,SIGNAL(Speak(QString)),&Jenny,SLOT(Listen(QString)));
    connect(&Joe,SIGNAL(Speak(QString)),this,SLOT(echos(QString)));
Joe.gossip("James is bald");

}

void waterCooler::echos(QString words){

    qDebug()<<"This is the echo of "<<words;
}

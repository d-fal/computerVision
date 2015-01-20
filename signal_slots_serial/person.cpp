#include "person.h"

Person::Person(QObject *parent) :
    QObject(parent)
{
}

void Person::Listen(QString words){

    qDebug()<<Name<<" someone told me ... "<<words;
}

void Person::gossip(QString words){

    qDebug()<<Name<<" says ...";
    emit Speak(words);
}

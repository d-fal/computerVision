#ifndef PERSON_H
#define PERSON_H
#include <QDebug>
#include <QString>
#include <QObject>


class Person : public QObject
{
    Q_OBJECT
public:
    explicit Person(QObject *parent = 0);
    QString Name;
    void gossip(QString words);
signals:
void Speak(QString words);
public slots:
void Listen(QString words);

};

#endif // PERSON_H

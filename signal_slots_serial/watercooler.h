#ifndef WATERCOOLER_H
#define WATERCOOLER_H
#include "person.h"
#include <QObject>

class waterCooler : public QObject
{
    Q_OBJECT
public:
    explicit waterCooler(QObject *parent = 0);

signals:
    void spread(QString words);
public slots:
    void echos(QString words);
};

#endif // WATERCOOLER_H

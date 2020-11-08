#ifndef DMDAO_H
#define DMDAO_H
#include<QStringList>
#include<QVector>
#include<QQueue>
#include<QMap>
#include <table.h>
#include<qDebug>
class dmDao{
public:
    bool insertDao(QString tableName,QString columnList,QString paramList);
    bool deleteDao(QString tableName,QQueue<QString> condtion);
    bool updateDao(QString tableName,QQueue<QString> condtion);
};

#endif // DMDAO_H

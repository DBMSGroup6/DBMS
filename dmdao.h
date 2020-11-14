#ifndef DMDAO_H
#define DMDAO_H
#include<QStringList>
#include<QVector>
#include<QQueue>
#include<QMap>
#include<table.h>
#include<QRegularExpression>
#include<QRegularExpressionMatch>
#include<qDebug>
#include<set>
#include<algorithm>
class dmDao{
public:
    bool insertDao(QString tableName,QStringList columnList,QStringList paramList);
    bool deleteDao(QString tableName,QStringList judgeList);
    bool updateDao(QString tableName,QString column,QString value,QStringList judgeList);
    Table selectDao(QString tableName,QString columnList,QStringList judgeList);
};

#endif // DMDAO_H

#ifndef TABLE_H
#define TABLE_H
#include<QMap>
#include<QQueue>
#include<QVector>
#include<QFile>
#include<QTextStream>
#include<QDebug>
#include<algorithm>
#include<field.h>
#include<QRegularExpression>
#include<QRegularExpressionMatch>
class Table{
public:
    Table();
    Table(QString tableName);
    bool readHead();
    bool readData();
    void setData(QVector<QVector<QString>> newData);
    void setHead(QVector<field> newHead);
    bool UpdateAllData();
    bool UpdateOneData(int id,QString column,QString value);
//    int FindData(QString column,QString judge,QString condtion);
    QVector<int> FindAllData(QString column,QString judge,QString condtion);
//    bool DeleteData(int i);
    bool DeleteAllData();
    bool InsertData(QMap<QString,QString> row);
    Table SelectData(QStringList columnList,QStringList groupList,QStringList orderList);//查询
    QVector<int> getWhere(QStringList judgeList);
    bool sort(QStringList orderList,bool desc);
    QString getTableName();
    QVector<field> getHead();
    QVector<QVector<QString>> getData();
    QString getFieldType(QString name);
    int getFieldIndex(QString name);
    Table Cartesian(Table t);   
    //bool cmp(const QVector<QVector<QString>> &v1,const QVector<QVector<QString>>);
protected:
public:
    QString tableName;
    QVector<QVector<QString>> data;
    QVector<field> head;
};

#endif // TABLE_H

#ifndef TABLE_H
#define TABLE_H
#include<QMap>
#include<QQueue>
#include<QVector>
#include<QFile>
#include<QTextStream>
#include<QDebug>
#include<field.h>
class Table{
public:
    Table();
    Table(QString tableName);
    bool readHead();
    bool readData();
    void setData(QVector<QVector<QString>> newData);
    bool UpdateAllData();
    bool UpdateOneData(int id,QString column,QString value);
    bool JudgeOneData(int id,QStringList judgeList);
    int FindData(QString column,QString judge,QString condtion);
    QVector<int> FindAllData(QString column,QString judge,QString condtion);
    bool DeleteData(int i);
    bool DeleteAllData();
    bool InsertData(QMap<QString,QString> row);
    Table SelectData(QString columnList,QQueue<QString> condtion);//单表查询
    QVector<field> getHead();
    QVector<QVector<QString>> getData();
    QString getFieldType(QString name);
    int getFieldIndex(QString name);
    Table Cartesian(Table t);
    QString getTableName();
    bool isWrong();
    void setWrong(bool wrong);
protected:
private:
    QString tableName;
    QVector<QVector<QString>> data;
    QVector<field> head;
    bool Wrong = false;
};

#endif // TABLE_H

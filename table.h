#ifndef TABLE_H
#define TABLE_H
#include<QMap>
#include<QVector>
#include<QFile>
#include<QTextStream>
#include<QDebug>
class Table{
public:
    Table();
    Table(QString tableName);
    bool readHead();
    bool readData();
    bool UpdateAllData();
    bool UpdateOneData(int id,QString column,QString value);
    int FindData(QString column,QString judge,QString condtion);
    QVector<int> FindAllData(QString column,QString judge,QString condtion);
    bool DeleteData(int i);
    bool DeleteAllData();
    bool InsertData(QMap<QString,QString> row);
    Table Select(QString columnList,QString condtion);//单表查询
    QVector<QVector<QString>> getHead();
    QVector<QVector<QString>> getData();
protected:
private:
    QString tableName;
    QVector<QVector<QString>> data;
    QVector<QVector<QString>> head;
};

#endif // TABLE_H

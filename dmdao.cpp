#include <dmdao.h>

bool dmDao::insertDao(QString tableName,QString columnList, QString paramList){
    QStringList list1 = columnList.split(",");
    QStringList list2 = paramList.split(",");
    QVector<QVector<QString>> map;
    QMap<QString,QString> row;
    //读取表文件获取表字段
    Table t(tableName);
    map =  t.getHead();
    if(map.isEmpty())
        qDebug()<<tableName;
    //遍历比较字段与列参数表
    for(int j=0;j<list1.size();j++){
        for(int i=0;i<map.size();i++){
            if(map[i].contains(list1.at(j))){
                row.insert(list1.at(j),list2.at(j));
            }
        }
    }
    if(t.InsertData(row))
    return true;
    return false;
}

bool dmDao::deleteDao(QString tableName, QQueue<QString> condtion){
    Table t(tableName);
    //没有条件时，全部删除
    if(condtion.isEmpty()){
        t.DeleteAllData();
        return true;
    }
    if(condtion.dequeue()=="where"){
        QString column = condtion.dequeue();
        QString judge = condtion.dequeue();
        QString cond = condtion.dequeue();
        int id = -1;
        id = t.FindData(column,judge,cond);
        while(id != -1){
            t.DeleteData(id);
            id = t.FindData(column,judge,cond);
        }
        t.UpdateAllData();
        return true;
    }
    return false;
}
bool dmDao::updateDao(QString tableName, QQueue<QString> condtion){
     Table t(tableName);
     QString temp;
     QString columnName;
     QString value;
     temp=condtion.dequeue();
     if(temp=="set"){
        columnName = condtion.dequeue();
        if(condtion.dequeue()=="="){
            value = condtion.dequeue();
            if(condtion.dequeue()=="where"){
                QString column = condtion.dequeue();
                QString judge = condtion.dequeue();
                QString cond = condtion.dequeue();
                QVector<int> id;
                id = t.FindAllData(column,judge,cond);
                for(int i=0;i<id.size();i++){
                    t.UpdateOneData(id.at(i),columnName,value);
                }
                t.UpdateAllData();
                return true;
            }
            //没有约束条件则全部更新
        }
     }
     return false;
}

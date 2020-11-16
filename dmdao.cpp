#include <dmdao.h>

bool dmDao::insertDao(QString tableName,QStringList columnList, QStringList paramList){
    try{
        QVector<field> map;
        QMap<QString,QString> row;
        //读取表文件获取表字段
        Table t(tableName);
        map =  t.getHead();
        if(!map.isEmpty()){
            if(!columnList.isEmpty()){
                //遍历比较字段与列参数表
                bool find =false;
                for(int j=0;j<columnList.size();j++){
                    find=false;
                    for(int i=0;i<map.size();i++){
                        if(map[i].get_name()==columnList.at(j)){
                            row.insert(columnList.at(j),paramList.at(j));
                            find=true;
                        }
                    }
                    //判断是否出现未知字段
                    if(!find){
                        throw QString("出现未知字段");
                    }
                }
                return (t.InsertData(row));
            }
            //缺省：全参数
            else if(map.size()==paramList.size()){
                for(int i=0;i<map.size();i++){
                   row.insert(map[i].get_name(),paramList.at(i));
                }
                return (t.InsertData(row));
            }
            else{
                throw QString("参数不匹配");
            }
        }
        else{
            throw QString("表字段为空");
        }
   }catch(QString exception){
       throw QString(exception);
   }
     return false;
}

bool dmDao::deleteDao(QString tableName,QStringList judgeList){
    try{
        Table t(tableName);
        //没有约束条件时，全部删除
        if(judgeList.isEmpty()){
            t.DeleteAllData();
        }
        else{
             QVector<int> where = t.getWhere(judgeList);
            QVector<QVector<QString>> newData;
            for(int i=0;i<t.getData().size();i++){
                if(!where.contains(i)){
                    newData.append(t.getData()[i]);
                }
            }
            t.setData(newData);
            t.UpdateAllData();
        }
        return true;
   }catch(QString exception){
       throw QString(exception);
   }
}
bool dmDao::updateDao(QString tableName, QString column1,QString value1,QStringList judgeList){
     try{
        Table t(tableName);
         //没有约束条件时，全部修改
         if(judgeList.isEmpty()){
             for(int i=0;i<t.getData().size();i++){
                 t.UpdateOneData(i,column1,value1);
             }
             t.UpdateAllData();
             return true;
         }
         else{
             QVector<int> where = t.getWhere(judgeList);
             for(int i=0;i<t.getData().size();i++){
                 if(where.contains(i)){
                     t.UpdateOneData(i,column1,value1);
                 }
             }
             t.UpdateAllData();
             return true;
         }
    }catch(QString exception){
        throw QString(exception);
    }
     return false;
}
Table dmDao::selectDao(QStringList tableList, QStringList columnList, QStringList judgeList,QStringList groupList,QStringList orderList){
    try{
        Table all;//总表
        //暂不考虑子查询
        for(int i=0;i<tableList.size();i++){
            //qDebug()<<tableList[i];
            Table temp(tableList[i]);
            all = all.Cartesian(temp);
            //qDebug()<<all.getHead().size();
        }
        if(!judgeList.isEmpty()){
             QVector<int> where = all.getWhere(judgeList);
    //        qDebug()<<OR.size();
            //只保留符合where条件的数据
            QVector<QVector<QString>> newData;
            for(int i=0;i<all.getData().size();i++){
                if(where.contains(i)){
                    newData.append(all.getData()[i]);
                    qDebug()<<i;
                }
            }
            all.setData(newData);
        }
    }catch(QString exception){
        throw WString(exception);
    }
    return all;//.SelectData(columnList,groupList,orderList);
    //return all.SelectData(columnList,groupList,orderList);
}

#include <dmdao.h>

bool dmDao::insertDao(QString tableName,QStringList columnList, QStringList paramList){
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
                    return false;
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
    }
     return false;
}

bool dmDao::deleteDao(QString tableName,QStringList judgeList){
    Table t(tableName);
    //没有约束条件时，全部删除
    if(judgeList.isEmpty()){
        t.DeleteAllData();
    }
    else{
        QString temp;
        QRegularExpression re("([A-Za-z_]+)\\s?(>|<|>=|<=|!=|=)\\s?(\\w+)");
        QRegularExpressionMatch match;
        QString column;
        QString judge;
        QString value;
        QVector<int> OR;
        // or判断
        for(int i=0;i<judgeList.size();i++){
            temp=judgeList[i];
            QVector<int> AND;
            // and 判断
            if(temp.contains("\\sand\\s")){
                QStringList AndList = temp.split("\\sand\\s");
                for(int i=0;i<AndList.size();i++){
                    QVector<int> tem;
                    match = re.match(AndList[i]);
                    if(match.hasMatch())
                    {
                        column = match.captured(1);
                        judge=match.captured(2);
                        value = match.captured(3);
                        //判断字段是否存在
                        if(t.getFieldIndex(column)==-1){
                            return false;
                        }
                        tem = t.FindAllData(column,judge,value);
                        if(i==0){
                          AND=tem;
                        }
                        else{
                            //交集
                            QVector<int> temAND;
                            std::sort(tem.begin(),tem.end());
                            std::sort(AND.begin(),AND.end());
                            std::set_intersection(AND.begin(),AND.end(),tem.begin(),tem.end(),std::back_inserter(temAND));
                            AND = temAND;
                        }
                    }
                    else {
                        AND.clear();
                    }
                }
                //并集
                QVector<int> ORAND;
                std::sort(OR.begin(),OR.end());
                std::sort(AND.begin(),AND.end());
                std::set_union(AND.begin(),AND.end(),OR.begin(),OR.end(),std::back_inserter(ORAND));
                OR = ORAND;
            }
            else{
                QVector<int> tem;
                match = re.match(temp);
                if(match.hasMatch())
                {
                    column = match.captured(1);
                    judge=match.captured(2);
                    value = match.captured(3);
                    tem = t.FindAllData(column,judge,value);
                }
                //做并集
                QVector<int> temOR;
                std::sort(OR.begin(),OR.end());
                std::sort(tem.begin(),tem.end());
                std::set_union(tem.begin(),tem.end(),OR.begin(),OR.end(),std::back_inserter(temOR));
                OR = temOR;
            }
        }
        QVector<QVector<QString>> newData;
        for(int i=0;i<t.getData().size();i++){
            if(!OR.contains(i)){
                newData.append(t.getData()[i]);
            }
        }
        t.setData(newData);
        t.UpdateAllData();
    }
    return true;
}
bool dmDao::updateDao(QString tableName, QString column1,QString value1,QStringList judgeList){
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
         QString temp;
         QRegularExpression re("([A-Za-z_]+)\\s?(>|<|>=|<=|!=|=)\\s?(\\w+)");
         QRegularExpressionMatch match;
         QString column;
         QString judge;
         QString value;
         QVector<int> OR;
         // or判断
         for(int i=0;i<judgeList.size();i++){
             temp=judgeList[i];
             QVector<int> AND;
             // and 判断
             if(temp.contains(" and ")){
                 QStringList AndList = temp.split(" and ");
                 for(int i=0;i<AndList.size();i++){
                     QVector<int> tem;
                     match = re.match(AndList[i]);
                     if(match.hasMatch())
                     {
                         column = match.captured(1);
                         judge=match.captured(2);
                         value = match.captured(3);
                         //判断字段是否存在
                         if(t.getFieldIndex(column)==-1){
                             return false;
                         }
                         tem = t.FindAllData(column,judge,value);
                         if(i==0){
                           AND=tem;
                         }
                         else{
                             //交集
                             QVector<int> temAND;
                             std::sort(tem.begin(),tem.end());
                             std::sort(AND.begin(),AND.end());
                             std::set_intersection(AND.begin(),AND.end(),tem.begin(),tem.end(),std::back_inserter(temAND));
                             AND = temAND;
                             for(int i=0;i<AND.size();i++)
                                 qDebug()<<"and"<<AND[i];
                         }
                     }
                     else {
                         AND.clear();
                     }
                 }
                 //并集
                 QVector<int> ORAND;
                 std::sort(OR.begin(),OR.end());
                 std::sort(AND.begin(),AND.end());
                 std::set_union(AND.begin(),AND.end(),OR.begin(),OR.end(),std::back_inserter(ORAND));
                 OR = ORAND;
             }
             else{
                 QVector<int> tem;
                 match = re.match(temp);
                 if(match.hasMatch())
                 {
                     column = match.captured(1);
                     judge=match.captured(2);
                     value = match.captured(3);
                     tem = t.FindAllData(column,judge,value);
                 }
                 //做并集
                 QVector<int> temOR;
                 std::sort(OR.begin(),OR.end());
                 std::sort(tem.begin(),tem.end());
                 std::set_union(tem.begin(),tem.end(),OR.begin(),OR.end(),std::back_inserter(temOR));
                 OR = temOR;
             }
         }
         for(int i=0;i<t.getData().size();i++){
             if(OR.contains(i)){
                 t.UpdateOneData(i,column1,value1);
             }
         }
         t.UpdateAllData();
         return true;
     }
     return false;
}
Table dmDao::selectDao(QStringList table, QStringList columnList, QStringList judgeList){
    //多表查询
    if(tableName.contains(",")){
        QStringList tableList = tableName.split(",");
        Table t;
        return t.SelectData(columnList,condtion);
    }
    //单表查询
    else{
        Table t(tableName);
         return t.SelectData(columnList,condtion);
    }
}

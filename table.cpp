#include <table.h>

Table::Table(QString tableName){
    this->tableName=tableName;
    readHead();
    readData();
}

bool Table::readHead(){
    //读取字段文件
    QFile f("table/"+tableName+".txt");
    if(!f.open(QIODevice::ReadOnly|QIODevice::Text)){
        return false;
    }
    QVector<QString> row;
    //记录列名
    while(!f.atEnd()){
        QByteArray line = f.readLine();
        QString str(line);
        QStringList list = str.split(",");
        for(int i=0;i<list.size();i++){
            if(list.at(i)!="\n")
            row.append(list.at(i));
        }
        head.append(row);
        row.clear();
    }
    f.close();
}
bool Table::readData(){
    //读取数据文件
    QFile f("data/"+tableName+".txt");
    if(!f.open(QIODevice::ReadOnly|QIODevice::Text)){
        return false;
    }
    while(!f.atEnd()){
        QVector<QString> row;
        QByteArray line = f.readLine();
        QString str(line);
        QStringList list = str.split(",");
        for(int i=0;i<list.size();i++){
            if(list.at(i)!="\n")
            row.append(list.at(i));
        }
        data.append(row);
    }
    f.close();
}
QVector<QVector<QString>> Table::getHead(){
    return head;
}
QVector<QVector<QString>> Table::getData(){
    return data;
}
bool Table::UpdateAllData(){
    //打开数据文件
    QFile f("data/"+tableName+".txt");
   if(!f.open(QIODevice::WriteOnly|QIODevice::Text)){
       return false;
   }
   QTextStream out(&f);
   QString oneRow;
   qDebug()<<data.size();
   for(int i=0;i<data.size();i++){
       for(int j=0;j<data.at(i).size();j++){
           oneRow.append(data.at(i).at(j));
           oneRow.append(",");
       }
       qDebug()<<oneRow;
       out<<oneRow<<endl;
       oneRow.clear();
   }
}
bool Table::InsertData(QMap<QString,QString> row){
    QFile f("data/"+tableName+".txt");
   if(!f.open(QIODevice::ReadWrite | QIODevice::Append)){
       return false;
   }
   QString oneRow;
   QTextStream out(&f);
   for(int i=0;i<head.size();i++){
       if(row.contains(head.at(i).at(0))){
           oneRow.append(row.find(head.at(i).at(0)).value());
       }
       oneRow.append(",");
   }
   out<<oneRow<<endl;
   f.close();
}
int Table::FindData(QString column, QString judge, QString condtion){
    int order = -1;
    for(int i=0;i<head.size();i++){
        if(head.at(i).at(0)==column){
            order=i;
            break;
        }
    }
    if(order==-1){
        return false;
    }
    for(int j=0;j<data.size();j++){
        if(judge==">="){
            if(data.at(j).at(order)>=condtion){
                return j;
            }
        }
        if(judge=="<="){
            if(data.at(j).at(order)<=condtion){
                return j;
            }
        }
        if(judge=="!="){
            if(data.at(j).at(order)!=condtion){
                return j;
            }
        }
        if(judge==">"){
            if(data.at(j).at(order)>condtion){
                return j;
            }
        }
        if(judge=="<"){
            if(data.at(j).at(order)<condtion){
                return j;
            }
        }
        if(judge=="="){
            if(data.at(j).at(order)==condtion){
                return j;
            }
        }
    }
    return -1;
}
QVector<int> Table::FindAllData(QString column, QString judge, QString condtion){
    QVector<int> all;
    int order = -1;
    for(int i=0;i<head.size();i++){
        if(head.at(i).at(0)==column){
            order=i;
            break;
        }
    }
    if(order==-1){
        return all;
    }
    for(int j=0;j<data.size();j++){
        if(judge==">="){
            if(data.at(j).at(order)>=condtion){
                all.append(j);
            }
        }
        else if(judge=="<="){
            if(data.at(j).at(order)<=condtion){
                all.append(j);
            }
        }
        else if(judge=="!="){
            if(data.at(j).at(order)!=condtion){
                all.append(j);
            }
        }
        else if(judge==">"){
            if(data.at(j).at(order)>condtion){
                all.append(j);
            }
        }
        else if(judge=="<"){
            if(data.at(j).at(order)<condtion){
                all.append(j);
            }
        }
        else if(judge=="="){
            if(data.at(j).at(order)==condtion){
                all.append(j);
            }
        }
    }
    return all;
}

bool Table::DeleteData(int i){
    data.removeAt(i);
    return true;
}

bool Table::DeleteAllData(){
    //打开数据文件
    QFile f("data/"+tableName+".txt");
   if(!f.open(QIODevice::WriteOnly|QIODevice::Text)){
       return false;
   }
   f.close();
   return true;
}
bool Table::UpdateOneData(int id, QString column, QString value){
    int order = -1;
    for(int i=0;i<head.size();i++){
        if(head.at(i).at(0)==column){
            order=i;
            break;
        }
    }
    if(order==-1){
        return false;
    }
    data[id][order]=value;
    return true;
}

#include <table.h>

Table::Table(){

}

Table::Table(QString tableName){
    this->tableName=tableName;
    if(!readHead()||!readData()){
        Wrong=true;
    }
}
bool Table::isWrong(){
    return Wrong;
}
void Table::setWrong(bool wrong){
    this->Wrong=wrong;
}

bool Table::readHead(){
    //读取字段文件
    QFile f("table/"+tableName+".txt");
    if(!f.open(QIODevice::ReadOnly|QIODevice::Text)){
        return false;
    }
    //记录字段属性
    while(!f.atEnd()){
        QByteArray line = f.readLine();
        QString str(line);
        QStringList list = str.split(",");
        field row;
        row.set_name(list.at(0));
        row.set_dataType(list.at(1));
        head.append(row);
    }
    f.close();
}
void Table::setData(QVector<QVector<QString> > newData){
    this->data=newData;
}

bool Table::readData(){
    //读取数据文件
    QFile f("data/"+tableName+".txt");
    if(!f.open(QIODevice::ReadOnly|QIODevice::Text)){
        qDebug()<<"error";
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
QVector<field> Table::getHead(){
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
   for(int i=0;i<data.size();i++){
       for(int j=0;j<data.at(i).size();j++){
           oneRow.append(data.at(i).at(j));
           oneRow.append(",");
       }
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
       if(row.contains(head[i].get_name())){
           oneRow.append(row.find(head[i].get_name()).value());
       }
       oneRow.append(",");
   }
   out<<oneRow<<endl;
   f.close();
}

int Table::FindData(QString column, QString judge, QString condtion){
    int order =getFieldIndex(column);
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
    int order = getFieldIndex(column);
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
    int order = getFieldIndex(column);
    if(order==-1){
        return false;
    }
    data[id][order]=value;
    return true;
}
Table Table::SelectData(QString columnList, QQueue<QString> condtion){
    Table t;
    if(columnList=="*"){
        for(int i=0;i<head.size();i++){
            field row;
            row.set_name(head[i].get_name());
            row.set_dataType(head[i].get_dataType());
            t.head.append(row);
        }
    }
    else if(!columnList.isEmpty()){
        QStringList list = columnList.split(",");
        for(int i=0;i<list.size();i++){
            field row;
            //存在未知字段
            if(getFieldIndex(list.at(i))==-1){
                t.setWrong(true);
                return t;
            }
            row.set_name(list.at(i));
            row.set_dataType(getFieldType(list.at(i)));
            t.head.append(row);
        }
    }
    else{
        t.setWrong(true);
        return t;
    }

    if(!condtion.isEmpty()){
        if(condtion.dequeue()=="where"){
            QString column = condtion.dequeue();
            QString judge = condtion.dequeue();
            QString cond = condtion.dequeue();
            QVector<int> temp = FindAllData(column,judge,cond);
            for(int i=0;i<temp.size();i++){
                QVector<QString> row;
                for(int j=0;j<t.head.size();j++){
                    row.append(data.at(temp.at(i)).at(getFieldIndex(t.head[j].get_name())));
                }
                t.data.append(row);
            }
            return t;
        }
    }
    else{
        for(int i=0;i<data.size();i++){
             QVector<QString> row;
            for(int j=0;j<t.head.size();j++){
                row.append(data.at(i).at(getFieldIndex(t.head[j].get_name())));
            }
            t.data.append(row);
        }
        return t;
    }
    t.setWrong(true);
    return t;
}
int Table::getFieldIndex(QString name){
    for(int i=0;i<head.size();i++){
        if(head[i].get_name()==name){
            return i;
        }
    }
    return -1;
}
QString Table::getFieldType(QString name){
    for(int i=0;i<head.size();i++){
        if(head[i].get_name()==name){
            return head[i].get_dataType();
        }
    }
    return "";
}
//得到两个表的笛卡尔积
Table Table::Cartesian(Table t){
    Table newT;
    QString sameFieldName;
    int id=-1;
    //添加字段
    for(int i=0;i<t.getHead().size();i++){
        id = getFieldIndex(t.getHead()[i].get_name());
        //具有相同字段时加前缀 table.field
        if(id!=-1){
            sameFieldName = head[id].get_name();
            QString newName;
            newName.append(t.getTableName());
            newName.append(".");
            newName.append(sameFieldName);
            t.getHead()[i].set_name(newName);
            newName.clear();
            newName.append(head[id].get_name());
            newName.append(".");
            newName.append(sameFieldName);
            head[id].set_name(tableName+head[id].get_name());
        }
        newT.getHead().append(t.getHead()[i]);
    }
    //添加字段
    for(int i=0;i<getHead().size();i++){
      newT.getHead().append(getHead()[i]);
    }
    //添加数据
    for(int i=0;i<t.getData().size();i++){
        for(int j=0;j<getData().size();j++){
            QVector<QString> row;
            row.append(t.getData()[i]);
            row.append(getData()[j]);
            newT.getData().append(row);
        }
    }
    return newT;
}
QString Table::getTableName(){
    return tableName;
}

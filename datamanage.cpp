#include "datamanage.h"
#include "ui_datamanage.h"

DataManage::DataManage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DataManage)
{
    ui->setupUi(this);

}

DataManage::~DataManage()
{
    delete ui;
}

void DataManage::init(){
     ui->outputText->setText("");
}

void DataManage::on_pushButton_clicked()
{
    QString sql = ui->inputText->toPlainText();
    QStringList sqls = sql.split(";");
    for(int i=0;i<sqls.length();i++){
        sql = sqls.at(i);
        if(!sql.isEmpty())
        Parse(sqls[i]);
    }
}

bool DataManage::Parse(QString sql){
    //QString::trimmed() 移除字符串两端空白符
    //QString::simplified() 移除字符串两端空白符，使用单个空格字符代替字符串中出现的空白字符
    //remove(QRegExp("\\s)) 移除所有空白字符
    judge.append("!=");
    judge.append(">=");
    judge.append("<=");
    judge.append("=");
    judge.append(">");
    judge.append("<");
    for(int i=0;i<judge.length();i++){
        if(sql.contains(judge.at(i))){
            sql.replace(judge.at(i)," "+judge.at(i)+" ");
        }
    }
    sql = sql.simplified();
    sql = sql.toLower();
    sqlList = sql.split(" ",QString::SkipEmptyParts);
    queue.clear();
    for(int i=0;i<sqlList.size();i++){
        queue.enqueue(sqlList[i]);
    }
    QString tem = queue.dequeue() ;
    if(tem=="insert"){
        if(!Insert("test")){
            ui->outputText->append("出现语法错误");
        }
    }
    else if(tem=="delete"){
        if(!Delete("test")){
            ui->outputText->append("出现语法错误");
        }
    }
    else if(tem=="update"){
        if(!Update("test")){
            ui->outputText->append("出现语法错误");
        }
    }
    else if(tem=="select"){
        if(!Select("test")){
            ui->outputText->append("出现语法错误");
        }
    }
    else{
        ui->outputText->append("出现语法错误");
    }
}
bool DataManage::Insert(QString database){
    if(queue.dequeue()=="into"){
        QString tem = queue.dequeue();
        QString tableName;
        QString columnList;
        QString paramList;
        if(tem.contains("(",Qt::CaseInsensitive)){
            tableName = tem.mid(0, tem.indexOf("("));
            columnList = tem.mid(tem.indexOf("("));
        }
        else{
            tableName = tem;
            tem = queue.dequeue();
            if(!tem.contains("values"))
            columnList = tem;
        }
        tem = queue.dequeue();
        if(tem.contains("values")){
            if(tem.contains("(",Qt::CaseInsensitive)){
                paramList = tem.mid(tem.indexOf("("));
            }
            else{
                paramList = queue.dequeue();
            }
            columnList.remove('(');
            columnList.remove(')');
            paramList.remove('(');
            paramList.remove(')');
            if(dao.insertDao(tableName,columnList,paramList)){
                //插入成功
                ui->outputText->append("插入成功");
                return true;
            }
        }
    }
    return false;
}
bool DataManage::Delete(QString database){
    QString tableName;
    if(queue.dequeue()=="from"){
        tableName=queue.dequeue();
        if(dao.deleteDao(tableName,queue)){
             ui->outputText->append("删除成功");
            return true;
        }
    }
    return false;
}
bool DataManage::Update(QString database){
    QString tableName;
    tableName = queue.dequeue();
    if(dao.updateDao(tableName,queue)){
         ui->outputText->append("更新成功");
        return true;
    }
    return false;
}

bool DataManage::Select(QString database){
    QString tableName;
    QString columnList;
    Table t;
    columnList = queue.dequeue();
    if(queue.dequeue()=="from"){
        tableName=queue.dequeue();
        t = dao.selectDao(tableName,columnList,queue);
        QString row;
        for(int i=0;i<t.getHead().size();i++){
            row.append(t.getHead()[i].get_name());
            row.append(",");
        }
        ui->outputText->append(row);
        row.clear();
        for(int i=0;i<t.getData().size();i++){
            for(int j = 0;j<t.getData().at(i).size();j++){
                row.append(t.getData()[i][j]);
                row.append(",");
            }
            ui->outputText->append(row);
            row.clear();
        }
    }
    return true;
}


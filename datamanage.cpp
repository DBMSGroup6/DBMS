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
        if(!sql.isEmpty()){
            Parse(sql);
            //match(sqls[i]);
        }
    }
}
QString DataManage::match(QString sql){
    //     ^select\\s((?:\\w+,)*\\w+)\\sfrom\\s((?:\\w+,)*\\w+)
    //     (?:\\swhere\\s((?:[A-Za-z_]+\\s?(?:>|<|>=|<=|!=|=)\\s?\\w+\\s(?:and|or)\\s)*[A-Za-z_]+\\s?(?:>|<|>=|<=|!=|=)\\s?\\w+))?
    //     (?:\\sgroup\\sby\\s((?:\\w+,)*\\w+))?
    //     (?\\shaving\\s(sum|count|avg)\\(\\w+\\)\\s?(?:>|<|>=|<=|!=|=)\\s?\\w+)?
    //     (?:\\sorder\\sby\\s((?:\\w+,)*\\w+)\\s(?:asc))?
    QRegularExpression re("([A-Za-z_\\.]+)\\s?(>|<|>=|<=|!=|=)\\s?([\\w\\.]+)");
    QRegularExpressionMatch match=re.match(sql);
    if(match.hasMatch())
    {
        QString matched1 = match.captured(1);
        ui->outputText->append(matched1);
        QString matched2 = match.captured(2);
        ui->outputText->append(matched2);
        QString matched3 = match.captured(3);
        ui->outputText->append(matched3);
        QString matched4 = match.captured(4);
        ui->outputText->append(matched4);
        QString matched5 = match.captured(5);
        ui->outputText->append(matched5);
    }
     return "   ";
}

bool DataManage::Parse(QString sql){
    //QString::trimmed() 移除字符串两端空白符
    //QString::simplified() 移除字符串两端空白符，使用单个空格字符代替字符串中出现的空白字符
    //remove(QRegExp("\\s)) 移除所有空白字符
    sql = sql.simplified();
    //全部转换为小写
    sql = sql.toLower();
    sqlList = sql.split(" ",QString::SkipEmptyParts);
    QString tem = sqlList[0];
    try{
        if(tem=="insert"){
            if(!Insert("test",sql)){
                ui->outputText->append("出现语法错误");
            }
            else{
                ui->outputText->append("插入成功");
            }
        }
        else if(tem=="delete"){
            if(!Delete("test",sql)){
                ui->outputText->append("出现语法错误");
            }
            else{
                ui->outputText->append("删除成功");
            }
        }
        else if(tem=="update"){
            if(!Update("test",sql)){
                ui->outputText->append("出现语法错误");
            }
            else{
                ui->outputText->append("更新成功");
            }
        }
        else if(tem=="select"){
            if(!Select("test",sql)){
                ui->outputText->append("出现语法错误");
            }
            else{
                ui->outputText->append("查询成功");
            }
        }
        else{
            ui->outputText->append("出现语法错误");
        }
    }catch(QString exception){
        ui->outputText->append(exception);
    }

}
bool DataManage::Insert(QString database,QString sql){
    try{
        QRegularExpression re("^insert\\sinto\\s([A-Za-z_]+)\\s?\\(((?:[A-Za-z_]+,)*[A-Za-z_]+)\\)\\svalues\\s?\\(((?:.*,)*.*)\\)");
        QRegularExpressionMatch match=re.match(sql);
        QString tableName;
        QString column;
        QString param;
        QStringList columnList;
        QStringList paramList;
        //有表参数
        if(match.hasMatch())
        {
            tableName = match.captured(1);
            column = match.captured(2);
            param = match.captured(3);
            //qDebug()<<param;
            columnList = column.split(",");
            paramList = param.split(",");
            if(columnList.length()==paramList.length()){
                return dao.insertDao(tableName,columnList,paramList);
            }
        }
        //无表参数
        else{
            QRegularExpression reg("^insert\\sinto\\s([A-Za-z_]+)\\svalues\\s?\\(((?:.*,)*.*)\\)");
            match=reg.match(sql);
            if(match.hasMatch())
            {
                tableName = match.captured(1);
                param = match.captured(2);
                paramList = param.split(",");
                return dao.insertDao(tableName,columnList,paramList);
            }
            else{
                throw QString("不符合语法规范");
            }
        }
   }catch(QString exception){
       throw QString(exception);
   } 
    return false;
}
bool DataManage::Delete(QString database,QString sql){
    try{
        QString tableName;
        QStringList judgeList;
        QString judge;
        if(!sql.contains("where")){
            QRegularExpression re("^delete\\sfrom\\s(\\w+)");
            QRegularExpressionMatch match=re.match(sql);
            if(match.hasMatch())
            {
                tableName = match.captured(1);
                return dao.deleteDao(tableName,judgeList);
            }
            else{
                throw QString("不符合语法规范");
            }
        }
        else{
            QRegularExpression re("^delete\\sfrom\\s(\\w+)\\swhere\\s((?:[A-Za-z_]+\\s?(?:>|<|>=|<=|!=|=)\\s?\\w+\\s(?:and|or)\\s)*[A-Za-z_]+\\s?(?:>|<|>=|<=|!=|=)\\s?\\w+)");
            QRegularExpressionMatch match=re.match(sql);
            if(match.hasMatch())
            {
                tableName = match.captured(1);
                judge=match.captured(2);
                judgeList = judge.split(" or ");
                return dao.deleteDao(tableName,judgeList);
            }
            else{
                throw QString("不符合语法规范");
            }
        }
        }catch(QString exception){
            throw QString(exception);
        }

    return false;
}
bool DataManage::Update(QString database,QString sql){
    try{
        QString tableName;
        QStringList judgeList;
        QString column;
        QString value;
        QString judge;
        if(!sql.contains("where")){
            QRegularExpression re("^update\\s(\\w+)\\sset\\s(\\w+)\\s?=\\s?(\\w+)");
            QRegularExpressionMatch match=re.match(sql);
            if(match.hasMatch())
            {
                tableName = match.captured(1);
                column = match.captured(2);
                value = match.captured(3);
                return dao.updateDao(tableName,column,value,judgeList);
            }
            else{
                throw QString("不符合语法规范");
            }
        }
        else{
            QRegularExpression re("^update\\s(\\w+)\\sset\\s(\\w+)\\s?=\\s?(\\w+)\\swhere\\s((?:[A-Za-z_]+\\s?(?:>|<|>=|<=|!=|=)\\s?\\w+\\s(?:and|or)\\s)*[A-Za-z_]+\\s?(?:>|<|>=|<=|!=|=)\\s?\\w+)");
            QRegularExpressionMatch match=re.match(sql);
            if(match.hasMatch())
            {
                tableName = match.captured(1);
                column = match.captured(2);
                value = match.captured(3);
                judge=match.captured(4);
                judgeList = judge.split(" or ");
                return dao.updateDao(tableName,column,value,judgeList);
            }
            else{
                throw QString("不符合语法规范");
            }
        }
        }catch(QString exception){
            throw QString(exception);
        }

    return false;
}

bool DataManage::Select(QString database,QString sql){
    try{
        Table t;
        QString table;
        QString column;
        QString judge;
        QString group;
        QString order;
        //QString having;
        bool desc=true;
        QStringList columnList;//SELECT ...
        QStringList tableList;//FROM ...
        QStringList judgeList;//WHERE
        QStringList groupList;//GROUP BY (...,)...
        QStringList orderList;//ORDER BY (...,)... (ASC)
        //QStringList havingList;//HAVING ... >|<|>=|<=|=|!= ...

        //     ^select\\s((?:\\w+,)*\\w+)\\sfrom\\s((?:\\w+,)*\\w+)
        //     (?:\\swhere\\s((?:[A-Za-z_]+\\s?(?:>|<|>=|<=|!=|=)\\s?\\w+\\s(?:and|or)\\s)*[A-Za-z_]+\\s?(?:>|<|>=|<=|!=|=)\\s?\\w+))?
        //     (?:\\sgroup\\sby\\s((?:\\w+,)*\\w+))?
        //     (?\\shaving\\s(sum|count|avg)\\(\\w+\\)\\s?(?:>|<|>=|<=|!=|=)\\s?\\w+)?
        //     (?:\\sorder\\sby\\s((?:\\w+,)*\\w+)\\s(?:asc))?

        QRegularExpression re("^select\\s((?:\\w+,)*\\w+|\\*)\\sfrom\\s((?:\\w+,)*\\w+)"
                              "(?:\\swhere\\s((?:[A-Za-z_\\.]+\\s?(?:>|<|>=|<=|!=|=)\\s?[\\w\\.]+"
                              "\\s(?:and|or)\\s)*[A-Za-z_\\.]+\\s?(?:>|<|>=|<=|!=|=)\\s?[\\w\\.]+))?"
                              "(?:\\sgroup\\sby\\s((?:\\w+,)*\\w+))?(?:\\sorder\\sby\\s((?:\\w+,)*\\w+)\\s?(?:asc|desc)?)?$");
        QRegularExpressionMatch match=re.match(sql);
        if(match.hasMatch()){
            if(sql.contains("where")){
                QRegularExpression re("\\swhere\\s((?:[A-Za-z_\\.]+\\s?(?:>|<|>=|<=|!=|=)\\s?[\\w\\.]+\\s(?:and|or)\\s)*[A-Za-z_\\.]+\\s?(?:>|<|>=|<=|!=|=)\\s?[\\w\\.]+)");
                QRegularExpressionMatch match=re.match(sql);
                if(match.hasMatch())
                {
                    judge = match.captured(1);
                    judgeList = judge.split(" or ");
                }
            }
           if(sql.contains("group by")){
               QRegularExpression re("\\sgroup\\sby\\s((?:\\w+,)*\\w+)");
               QRegularExpressionMatch match=re.match(sql);
               if(match.hasMatch())
               {
                   group = match.captured(1);
                   groupList = group.split(",");
        //           QRegularExpression reg("\\shaving\\s(sum|count|avg)\\(\\w+\\)\\s?(?:>|<|>=|<=|!=|=)\\s?\\w+");
        //           QRegularExpressionMatch match=reg.match1(match.captured(0));
        //           if(match.hasMatch())
        //           {
        //               having = match.captured(1);
        //               havingList = having.split(",");
        //           }
               }
           }
           if(sql.contains("order by")){
               QRegularExpression re("\\sorder\\sby\\s((?:\\w+,)*\\w+)\\s?(?:asc|desc)?");
               QRegularExpressionMatch match=re.match(sql);
               if(match.hasMatch())
               {
                   if(match.captured(0).contains("asc")){
                       desc=false;
                   }
                   order = match.captured(1);
                   orderList = order.split(",");
               }
           }
            QRegularExpression re("^select\\s((?:\\w+,)*\\w+|\\*)\\sfrom\\s((?:\\w+,)*\\w+)");
            QRegularExpressionMatch match=re.match(sql);
            if(match.hasMatch())
            {
                column = match.captured(1);
                table = match.captured(2);
                tableList = table.split(",");
                columnList = column.split(",");
                t = dao.selectDao(tableList,columnList,judgeList,groupList,orderList);
                QString row;
                for(int i=0;i<t.getHead().size();i++){
                    row.append(t.getHead()[i].get_name());
                    row.append(",");
                }
                ui->outputText->append(row);
                row.clear();
                //qDebug()<<t.getData().size();
                for(int i=0;i<t.getData().size();i++){
                    for(int j=0;j<t.getData()[i].size();j++){
                        row.append(t.getData()[i][j]);
                        row.append(",");
                    }
                   ui->outputText->append(row);
                   row.clear();
                }
                return true;
            }
            else{
                throw QString("不符合语法规范");
            }
        }
        else{
            throw QString("不符合语法规范");
        }
        }catch(QString exception){
            throw QString(exception);
        }
    return false;
}


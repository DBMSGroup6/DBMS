#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFile"
#include "QMessageBox"
#include "QTextStream"
#include "qlogging.h"
#include "qdebug.h"
#include "QDir"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->setupUi(this);
//        ui->textEdit->setPlaceholderText(QStringLiteral("Please input..."));
        connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(on_clicked()));  //连接信号槽事件
    ///格式：connect(发送信号控件,SIGNAL(控件里的一个信号),接收的界面或控件(在同一页面一般是this),SLOT(刚定义的槽函数(函数写实现的功能));
}

void MainWindow::read_tableField(QString tableName){
    QString fileName = "D:\\qt\\build-CreateTable-Desktop_Qt_5_9_9_MinGW_32bit-Debug\\table" + tableName;
    QFile table(fileName);

    if(!table.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        this->ui->textBrowser->setText("CAN'T OPEN THE FILE!");
        return;

    }
    else{

        while(!table.atEnd()){//筛选属性
            QByteArray line = table.readLine();
            QString str(line);
            str = str.simplified();
            QStringList strList = str.split(" ");


            field a_field;
            a_field.set_tableName(this->thisField.get_tableName());
            a_field.set_name(strList[0]);
            a_field.set_dataType(strList[1]);
            a_field.set_PK(strList[2]);
            a_field.set_unique(strList[3]);
            a_field.set_notNull(strList[4]);
            a_field.set_defaultValue(strList[5]);
            a_field.set_checkUP(strList[6]);
            a_field.set_checkDown(strList[7]);
            a_field.set_FK_tableName(strList[8]);
            a_field.set_deleteLimit(strList[9]);


            this->allFields.append(a_field);


        }

        table.close();
        return;
    }
}



//用于清除字段文件中的内容并写入allFields
void MainWindow::update_field_file(QString tableName){

     filename = "D:\\qt\\build-CreateTable-Desktop_Qt_5_9_9_MinGW_32bit-Debug\\table" + tableName;
    QFile table(filename);
    table.open(QIODevice::WriteOnly|QIODevice::Text);
    QTextStream stream(&table);
    stream.seek(table.size());
    stream << "";
    table.close();


    table.open(QIODevice::WriteOnly|QIODevice::Append);
    QTextStream stream1(&table);
    stream1.seek(table.size());
    QVector<field>::iterator iter; //迭代器
    for(iter=allFields.begin();iter!=allFields.end();iter++){
        QString aline = iter->get_name() + " "
                        + iter->get_dataType() + " "
                        + iter->get_PK() + " "
                        + iter->get_unique() + " "
                        + iter->get_notNull() + " "
                        + iter->get_defaultValue() + " "
                        + iter->get_checkUP() + " "
                        + iter->get_checkDown() + " "
                        + iter->get_FK_tableName() + " "
                        + iter->get_deleteLimit();
        qDebug()<<aline;
        stream1 << aline << endl;
    }
    table.close();


}
//create table student(sno varchar2(9) PK,sname varchar2(12) notnull,age int unique);
    void MainWindow::on_clicked()
    {


         str = ui->textEdit->toPlainText();//这句获取输入的信息
         str=str.simplified();
         qDebug()<<"s="<<str;
         QStringList list = str.split(";");
         for(int i=0;i<list.size();i++){
             if(!list.isEmpty()){
                 prase(list.at(i));
             }


         }

     }
    bool MainWindow::prase(QString str){
        if(str.startsWith("create table")){
            if(createTable(str)){

                return true;
            }
        }
        else if(str.startsWith("drop table")){
            if(dropTable(str)){
                return true;
            }
        }
        else if(str.startsWith("create index")){
            if(createIndex(str)){
                return true;
            }
        }
        return false;
    }
    bool MainWindow::createTable(QString str){
        tmp=str.section("(",0,0);//分出create table+表名
        b=str.section("(",1,50);
        b.chop(1);
        qDebug()<<b;
        QStringList a=tmp.split(" ");

        if(a.size()<3){
            ui->textBrowser->clear();  //先把原来浏览器的内容清空，再把结果显示出来。
            ui->textBrowser->append(str2+"\n");//把str追加到textBrowser中；
            return false;
        }
        tableName=a.at(2);
        str=ui->textEdit->toPlainText();
        QRegExp exp("\\(((?:.*,).*)\\)");
        if(str.indexOf(exp)>=0)
        {
            QStringList list =exp.cap(1).split(",");
            QRegExp first("[a-z]+");//匹配 第一个单词
            QRegExp second("\\s+[^\\s]+");//匹配 第二个单词
            QRegExp PK("\\bPK\\b");//匹配“PK”
            QRegExp notn("\\bnotnull\\b");//匹配“notnull”
            QRegExp uniq("\\bunique\\b");//匹配“unique”
            QRegExp de("\\bdefault\\b");//匹配“default”
            filename=tableName+".txt";
            QDir dir;
            if(!dir.exists("table")){
                dir.mkdir("table");
            }
            dir="table";
            QString path=dir.filePath(filename);
            QFile file;
            file.setFileName(path);
            if(file.exists()){
                ui->textBrowser->clear();  //先把原来浏览器的内容清空，再把结果显示出来。
                ui->textBrowser->append("表已存在！");//把str追加到textBrowser中；
                return false;
            }
            file.open(QIODevice::ReadWrite|QIODevice::Text);
            QTextStream out(&file);

            for (int i=0;i<list.size();i++) {
                if(list.at(i).indexOf(first)>=0){

                out<<first.cap();
                qDebug()<<first.cap();
                }
                if(list.at(i).indexOf(second)>=0){
                    if(list.at(i).indexOf(PK)>=0){
                        qDebug()<<PK.cap();
                    if(PK.cap()=="PK"){
                        out<<second.cap()+" TRUE FALSE FALSE FALSE FALSE FALSE FALSE RESTRICT\n";
                        filename="index.txt";
                        QDir dir3;
                        if(!dir3.exists("table")){
                            dir3.mkdir("table");
                        }
                        dir3="table";
                        QString path3=dir3.filePath(filename);
                        QFile file3;
                        file3.setFileName(path3);
                        file3.open(QIODevice::ReadWrite|QIODevice::Text|QIODevice::Append);
                        QTextStream out3(&file3);
                        out3<<"index_"+first.cap()+"\n";
                        file3.close();
                    }
                    }else{

                    }
                    if(list.at(i).indexOf(notn)>=0){
                        qDebug()<<notn.cap();
                    if(notn.cap()=="notnull"){
                        out<<second.cap()+" FALSE FALSE TRUE FALSE FALSE FALSE FALSE RESTRICT\n";
                    }

                    }else{

                    }
                    if(list.at(i).indexOf(uniq)>=0){
                        qDebug()<<uniq.cap();
                    if(uniq.cap()=="unique"){
                        out<<second.cap()+" FALSE TRUE FLASE FALSE FALSE FALSE FALSE RESTRICT\n";
                    }
                    }else{

                    }
                    if(list.at(i).indexOf(de)>=0){
                        qDebug()<<de.cap();
                    if(de.cap()=="default"){
                        out<<second.cap()+" FALSE FALSE FLASE TRUE FALSE FALSE FALSE RESTRICT\n";
                    }
                    }else{

                    }
                }
            }
             file.close();
            }
        QDir dir1;
        if(!dir1.exists("data")){
            dir1.mkdir("data");
        }
        dir1="data";
        QString path1=dir1.filePath(filename);
        QFile file1;
        file1.setFileName(path1);
        file1.open(QIODevice::ReadWrite|QIODevice::Text);
        QTextStream out1(&file1);
        file1.close();
        ui->textBrowser->clear();  //先把原来浏览器的内容清空，再把结果显示出来。
        ui->textBrowser->append("表已创建");//把str追加到textBrowser中；

}
    //drop table student;
bool MainWindow::dropTable(QString str){
    qDebug()<<"str="<<str;
    QStringList list=str.split(" ");
    if(list.size()<3){
        ui->textBrowser->clear();  //先把原来浏览器的内容清空，再把结果显示出来。
        ui->textBrowser->append("语法错误！");//把str追加到textBrowser中；
        return false;
    }
    tableName=list.at(2);
    filename=tableName+".txt";
    QDir dir;
    if(!dir.exists("table")){
        dir.mkdir("table");
    }
    dir="table";
    QString path=dir.filePath(filename);

    qDebug()<<"文件名="<<filename;
    QFile file;
    file.setFileName(path);

    if(file.exists())
    {
        file.remove();
    }
    ui->textBrowser->clear();  //先把原来浏览器的内容清空，再把结果显示出来。
    ui->textBrowser->append("表已删除");//把str追加到textBrowser中；
}
//create index index_sno on student(sno);
bool MainWindow::createIndex(QString str){
    QStringList list=str.split(" ");
    indexName=list.at(2);
    filename="index.txt";
    QDir dir3;
    if(!dir3.exists("table")){
        dir3.mkdir("table");
    }
    dir3="table";
    QString path3=dir3.filePath(filename);

    qDebug()<<"文件名="<<filename;
    QFile file3;
    file3.setFileName(path3);
    file3.open(QIODevice::ReadWrite|QIODevice::Text|QIODevice::Append);
    QTextStream out3(&file3);
    out3<<indexName;
    file3.close();
    ui->textBrowser->clear();  //先把原来浏览器的内容清空，再把结果显示出来。
    ui->textBrowser->append("索引已创建");//把str追加到textBrowser中；
}

MainWindow::~MainWindow()
{
    delete ui;
}


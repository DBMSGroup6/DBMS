#include "login.h"
#include "mydbms.h"
#include "ui_login.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
#include<QMessageBox>
#include<QFile>
#include <QTextStream>

login::login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    mysystemDataBase();
    mysystemuser();
    //服务器设置
    tcpServer=new QTcpServer(this);
    //使用了IPv4的本地主机地址，等价于QHostAddress("127,0,0,1")
    if(!tcpServer->listen(QHostAddress("127.0.0.1"),8899))
    {
        qDebug()<<tcpServer->errorString();
        close();
    }
    connect(tcpServer,SIGNAL(newConnection()),this,SLOT(sendMessage()));
}

login::~login()
{
    delete ui;
}

void login::sendMessage()
{
    clientConnection =tcpServer->nextPendingConnection();
    qDebug()<<"sendmessage";
    connect(clientConnection,SIGNAL(readyRead()),this,SLOT(readMessage()));
}
void login::readMessage()
{
    clientConnection->read(a,8);//接收数据
}

//D:\\test
void login::mysystemDataBase() {//建立数据库
    QString pathName = "D:\\test\\system" ;
    if (QDir(pathName).exists() == false) {
        if (QDir().mkdir(pathName))//返回0表示创建成功,-1表示失败
            qDebug()<<"success";
        else
            qDebug()<<"error";
        return;
    }
    qDebug()<<"have that";
}

bool isFileExist()
{
    QString fullFileName = "D:\\test\\system\\user.txt";
    QFileInfo fileInfo(fullFileName);
    if(fileInfo.isFile())
    {
        return true;
    }
    return false;
}

void login::mysystemuser(){
    if(!isFileExist()){
        QFile file("D:\\test\\system\\user.txt");
            if(! file.open(QIODevice::Append|QIODevice::Text))  //append追加，不会覆盖之前的文件
            {
                QMessageBox::critical(this,"错误","文件打开失败，信息没有保存！","确定");
                return;
            }

            QTextStream out(&file);//写入
            QString mes = "root,123456,true,true,true";
            QStringList a = mes.split(",");
            for (int j=0;j<a.count();j++) {
                out<<a[j];
                out<<",";
                if((j+1)%5 == 0)
                    out << '\n';
            }
            file.close();
    }
    else
        qDebug()<<"have that filetxt";

}

void login::readtxt()
{
    QFile f("D:\\test\\system\\user.txt");
        if(!f.open(QIODevice::ReadOnly|QIODevice::Text)){
            qDebug()<<"not found filetxt";
            return;
        }
        while(!f.atEnd()){
            QVector<QString> row;
            QByteArray line = f.readLine();
            QString str(line);
            //str = str.simplified();
            //str.remove(" ");
            QStringList list = str.split(",");
            pathtxt.insert(list[0],list[1]);
//            for(int i=0;i<list.size();i++){
//                if(list[i]!="\n")
//                row.append(list.at(i));
//            }
        }
        f.close();
}

void login::on_pushButton_clicked()
{
    //获得用户和密码
    QString name=ui->lineEdit->text();
    QString password=ui->lineEdit_2->text();
    QString p;
    readtxt();
    if (pathtxt.contains(name) ){
        qDebug()<<"have user";
        p = pathtxt[name];
        qDebug()<<pathtxt.find(name).value();
        qDebug()<<"password  "+pathtxt[name];
        if(password == p)
        {
            ui->lineEdit->clear();
            ui->lineEdit_2->clear();
            //在这里直接跳转
            pathtxt.clear();
            MainWindow *dia=new MainWindow(this);
            dia->show();
            connect(dia,SIGNAL(mysignal()),this,SLOT(my_show_slot())); //收到第二个窗口关闭信号显示第一窗口
            this->hide();
        }
    }
    else{
        QMessageBox::warning(this,"警告！","用户名或者密码错误",QMessageBox::Yes);
        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
    }

}

void login::my_show_slot()
{
    this->show();
}

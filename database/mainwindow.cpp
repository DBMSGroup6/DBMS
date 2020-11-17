#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <mydbms.h>
#include <QDebug>
#include <qdebug.h>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    db = new myDBMS();
    ui->setupUi(this);
    connect(db,SIGNAL(sendmessage(QString)),this,SLOT(message(QString)));

}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init(){
    ui->textEdit->setText("");
}

void MainWindow::dbtest(QString sql){

    while (1) {
        sql = sql.toLower();
        squece = sql.split(" ");
        if (squece[0] == "exit"){

        }
        if(squece.size() != 3){
            ui->textEdit->setText("WRONG");
            return;
        }
        //cout << "db.cmd = " << db.cmd << endl;

        if (squece[0] == "create") {
            QString name;
            name = squece[2];

            //cout << "db.cmd:" << db.cmd << " name:" << name << endl;
            if (squece[1] == "database")
                db->myCreateDataBase(name);
            else cout << "命令语句有误!" << endl;
        }
        else if (squece[0] == "drop") {
            QString name;
            name = squece[2];
            if (db->cmd == "database")
                db->myDropDataBase(name);
            else cout << "命令语句有误!" << endl;
        }
        else if (squece[0] == "open") {
            qDebug()<< "**************";
            QString name;
            name = squece[2];
            db->openDataBase(name);
        }
        else if (squece[0] == "close") {
            QString name;
            name = squece[2];

            if (db->cmd == "database")
                db->closeDataBase(name);
            else cout << "命令语句有误!" << endl;
        }
        else {
            ui->textEdit->setText("WRONG");
            return;
        }
    }
}

void MainWindow::message(QString s){
    ui->textEdit->setText(s);
}

void MainWindow::on_pushButton_2_clicked()
{
    qDebug()<< "**************";
    db->cmd = ui->lineEdit->text();

    QString sql=db->cmd;
        sql = sql.toLower();
        squece = sql.split(" ");
        if (squece[0] == "exit"){

        }
        if(squece.size() != 3){
            ui->textEdit->setText("WRONG");
        }
        //cout << "db.cmd = " << db.cmd << endl;

        if (squece[0] == "create") {
            QString name;
            name = squece[2];

            //cout << "db.cmd:" << db.cmd << " name:" << name << endl;
            if (squece[1] == "database")
                db->myCreateDataBase(name);
            else ui->textEdit->setText("WRONG SQUENCE");
        }
        else if (squece[0] == "drop") {
            QString name;
            name = squece[2];
            if (squece[1] == "database")
                db->myDropDataBase(name);
            else ui->textEdit->setText("drop WRONG SQUENCE");
        }
        else if (squece[0] == "open") {
            qDebug()<< "**************";
            QString name;
            name = squece[2];
            db->openDataBase(name);
        }
        else if (squece[0] == "close") {
            QString name;
            name = squece[2];

            if (squece[1] == "database")
                db->closeDataBase(name);
            else ui->textEdit->setText("close WRONG SQUENCE");
        }
        else {
            ui->textEdit->setText("WRONG");
            return;
        }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    emit mysignal(); //发送信号
}
void MainWindow::on_pushButton_clicked()
{
    emit mysignal();
    this->close();
}

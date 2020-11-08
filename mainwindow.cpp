#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}



























void MainWindow::on_open_triggered()//打开xx
{
     QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"C:/Users/ywjy/Desktop/data",tr("txt (*.txt)"));//打开文件
}

void MainWindow::on_addtable_triggered()//创建表
{
    QFile file("C:/Users/ywjy/Desktop/data/success.txt");
//    123bool ok = file.open(QIODevice::ReadWrite);
}

void MainWindow::on_findtable_triggered()//获取表
{
    QDir dir("C:/Users/ywjy/Desktop/data");//将目标文件夹下所有文件获取并输出
    QStringList nameFilters;
    nameFilters << "*.jpg" << "*.png" <<"*.txt";
    QStringList files = dir.entryList(nameFilters, QDir::Files|QDir::Readable, QDir::Name);
    QString listname = files.join("\n");
    ui->textEdit->setText(listname);
    ui->treeWidget->clear();
    ui->treeWidget->windowFilePath();
    ui->treeWidget->setWindowIconText(listname);

}

void MainWindow::on_backbutton_clicked()//撤销
{
    QFile f("C:/Users/ywjy/Desktop/data/beifen.txt");//从缓存文件中获取之前的语句内容并还原
    f.open(QIODevice::ReadOnly);
    QTextStream t(&f);
    QString text = t.readAll();
    ui->textEdit->setPlainText(text);
}

void MainWindow::on_pushButton_clicked()//执行
{
    QFile f("C:/Users/ywjy/Desktop/data/beifen.txt");//将当前输入框内容缓存备份
    f.open(QFile::WriteOnly|QFile::Truncate);
    f.close();
    QString text = ui->textEdit->toPlainText();
    f.open(QFile::WriteOnly|QFile::Truncate);
    QTextStream out(&f);
    out<<text<<endl;
    f.close();

    //执行语法
}

void MainWindow::on_clearbutton_clicked()//清除
{

    QFile f("C:/Users/ywjy/Desktop/data/beifen.txt");//将当前输入框内容缓存备份
    f.open(QFile::WriteOnly|QFile::Truncate);
    f.close();
    QString text = ui->textEdit->toPlainText();
    f.open(QFile::WriteOnly|QFile::Truncate);
    QTextStream out(&f);
    out<<text<<endl;
    f.close();

    ui->textEdit->clear();//清空文本
}


void MainWindow::on_readtable_triggered()//打开表
{
    Table t("student");

    ui->tableWidget->setColumnCount(t.getData()[0].size());//设置表格大小
    ui->tableWidget->setRowCount(t.getData().size());

//    ui->tableWidget->horizontalHeader()->setVisible(false);// 隐藏表头
//    ui->tableWidget->verticalHeader()->setVisible(false);

    for(int i=0;i<t.getData().size();i++)
    {
        for(int j=0;j<t.getData()[0].size();j++)
        {
            ui->tableWidget->setHorizontalHeaderItem(j,new QTableWidgetItem(t.getHead()[j].get_name()));//设置表头
            ui->tableWidget->setItem(i,j,new QTableWidgetItem(t.getData()[i][j]));//读取内容
        }
    }
}

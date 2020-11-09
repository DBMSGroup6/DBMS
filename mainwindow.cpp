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
    QFile file("data/success.txt");
//    123bool ok = file.open(QIODevice::ReadWrite);
}

void MainWindow::on_findtable_triggered()//获取表
{
    QDir dir("data");//将目标文件夹下所有文件获取并输出
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
    QFile f("cache/cache.txt");//从缓存文件中获取之前的语句内容并还原
    f.open(QIODevice::ReadOnly);
    QTextStream t(&f);
    QString text = t.readAll();
    ui->textEdit->setPlainText(text);
}

void MainWindow::on_pushButton_clicked()//执行
{
    QFile f("cache/cache.txt");//将当前输入框内容缓存备份
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

    QFile f("cache/cache.txt");//将当前输入框内容缓存备份
    f.open(QFile::WriteOnly|QFile::Truncate);
    f.close();
    QString text = ui->textEdit->toPlainText();
    f.open(QFile::WriteOnly|QFile::Truncate);
    QTextStream out(&f);
    out<<text<<endl;
    f.close();

    ui->textEdit->clear();//清空文本
}


void MainWindow::on_readtable_triggered(QString filename)//打开表
{
    Table t(filename);

    ui->tableWidget->setColumnCount(t.getData()[0].size());//设置表格大小
    ui->tableWidget->setRowCount(t.getData().size());

//    ui->tableWidget->horizontalHeader()->setVisible(false);// 隐藏表头
//    ui->tableWidget->verticalHeader()->setVisible(false);

         for(int i=0;i<t.getData().size();i++)
         {
             for(int j=0;j<t.getData()[0].size();j++)
             {
     //            if(t.getData()[i][j]==NULL)
     //            {
     //                t.getData()[i][j]="null";
     //            }
                 ui->tableWidget->setHorizontalHeaderItem(j,new QTableWidgetItem(t.getHead()[j].get_name()));//设置表头
                 ui->tableWidget->setItem(i,j,new QTableWidgetItem(t.getData()[i][j]));//读取内容
             }
         }
}

void MainWindow::on_readdb_triggered()//打开数据库
{
//    ui->treeWidget->clear();//清空树

    ui->treeWidget->setColumnCount(1);//设置树冠
    QStringList header;
    header<<QString("DB List");//不能使用中文
    ui->treeWidget->setHeaderLabels(header);


    QDir dirdbs("database");//获取数据库
    QStringList dbsfiles;
    dbsfiles << "*.jpg" << "*.png" <<"*.txt";
    QStringList dbs = dirdbs.entryList(dbsfiles, QDir::Files|QDir::Readable, QDir::Name);
    QStringList toplevel;//一级节点 数据库
    for(int i=0;i<dbs.size();i++)
    {;
        QStringList dbsname = dbs[i].split(".txt");
        toplevel<<dbsname;
        QTreeWidgetItem *top = new QTreeWidgetItem(ui->treeWidget,toplevel);
        toplevel.clear();

        QDir dir("data");//获取表
        QStringList nameFilters;
        nameFilters << "*.jpg" << "*.png" <<"*.txt";
        QStringList files = dir.entryList(nameFilters, QDir::Files|QDir::Readable, QDir::Name);
        QStringList seclevel;//二级节点 表
        for(int j=0;j<files.size();j++)
        {
            QStringList tablename = files[j].split(".txt");
            seclevel<<tablename;//读入文件数量
            QTreeWidgetItem *childitem = new QTreeWidgetItem(top,seclevel);
            top->addChild(childitem);
            seclevel.clear();//清空队列
        }
    }
//    connect(ui->treeWidget,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),this,SLOT(clicktreeitem()));
}


void MainWindow::on_treeWidget_itemSelectionChanged()//点击二级节点后的响应事件
{
    QTreeWidgetItem *item = ui->treeWidget->currentItem();

    QDir dir("data");//获取表
    QStringList nameFilters;
    nameFilters << "*.jpg" << "*.png" <<"*.txt";
    QStringList files = dir.entryList(nameFilters, QDir::Files|QDir::Readable, QDir::Name);
    QStringList seclevel;//二级节点 表

    Table t(item->text(0));

    if(t.getData().size()!=NULL)
    {
        for(int j=0;j<files.size();j++)
        {
            QStringList tablename = files[j].split(".txt");
            seclevel<<tablename;//读入文件数量
            if(item->text(0)==seclevel[0])//不能存在空表，否则会报错
            {
                on_readtable_triggered(item->text(0));
            }
            seclevel.clear();//清空队列
        }
    }
    else//空表 展示
    {
        ui->tableWidget->clear();
        ui->tableWidget->setColumnCount(1);
        ui->tableWidget->setRowCount(1);
        ui->tableWidget->setItem(0,0,new QTableWidgetItem("This table is null!"));
    }
}

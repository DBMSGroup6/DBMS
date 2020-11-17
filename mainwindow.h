#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QQueue>
#include <QVector>
#include "field.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString filename;
    QString str;
    QString tmp;
    QString b;
    QString tableName;	    //表名
    QString indexName;
    int atrribute;           //属性个数
    int remcount;			//元组个数


    QQueue<QString> queue;
    QStringList a2;

private:
    Ui::MainWindow *ui;
    field thisField;
    QVector<field> allFields;

public slots:
    void on_clicked();
//    void createFile(QString filePath,QString fileName);
    bool createTable(QString str);
    bool dropTable(QString str);
    bool prase(QString str);
    void update_field_file(QString tableName);
    void read_tableField(QString tableName);

    bool createIndex(QString str);



};
#endif // MAINWINDOW_H

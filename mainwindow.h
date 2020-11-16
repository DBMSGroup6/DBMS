#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QFileDialog>
#include <QVector>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include "field.h"
#include "user.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QString insert_field();//插入字段
    QString drop_field();//删除字段
    void read_tableField(QString tableName);//预读表内字段
    void update_field_file(QString tableName);//更新表内字段

    QString insert_user();//插入用户
    QString drop_user();//删除用户
    void read_userField();
    void update_user_file();//更新用户表内字段

private slots:
    void on_pushButton_clicked();

private:
    user nowUser;//此时正在操作DBMS的用户
    user thisUser;//要操作的用户
    field thisField;//要操作的字段

    QVector<field> allFields;//将字段文件预读入此
    QVector<user> allUsers;//将用户文件预读于此

    QString sql;//sql语句
    QStringList sqlList;//按空格分割后的sql语句

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

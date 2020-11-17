#ifndef LOGIN_H
#define LOGIN_H
#include<QMap>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMainWindow>
#include <QAbstractSocket>
#include <QtNetwork>

namespace Ui {
class login;
}

class login : public QMainWindow
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();
    void mysystemDataBase();
    void mysystemuser();
    void readtxt();
    void sendMessage();
    void readMessage();
private slots:
    void on_pushButton_clicked();
    void my_show_slot();
private:
    Ui::login *ui;
    QTcpServer *ser;
    QTcpSocket *cli;
    QMap<QString,QString> pathtxt;
    char a[20];
    QTcpServer *tcpServer=new QTcpServer(this);//用于创建服务器连接
    QTcpSocket *clientConnection;//用于处理连接成功后和客户端的数据处理
};

#endif // LOGIN_H

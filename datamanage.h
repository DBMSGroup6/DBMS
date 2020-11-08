#ifndef DATAMANAGE_H
#define DATAMANAGE_H

#include <QWidget>
#include <QVector>
#include <QQueue>
#include <dmdao.h>
#include <QMap>
namespace Ui {
class DataManage;
}

class DataManage : public QWidget
{
    Q_OBJECT

public:
    explicit DataManage(QWidget *parent = 0);
    ~DataManage();
    void init();
    bool Select(QString database);
    bool Insert(QString database);
    bool Delete(QString database);
    bool Update(QString database);
    bool Parse(QString sql);//解析
    void Exec();//执行
private slots:
    void on_pushButton_clicked();

private:
    Ui::DataManage *ui;
    QStringList sqlList;
    QString sql;
    QQueue<QString> queue;
    QVector<QString> judge;
    QMap<QString,QVector<QString>> map;
    dmDao dao;
};

#endif // DATAMANAGE_H

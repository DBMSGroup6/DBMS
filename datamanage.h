#ifndef DATAMANAGE_H
#define DATAMANAGE_H

#include <QWidget>
#include <QVector>
#include <QQueue>
#include <dmdao.h>
#include <QMap>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
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
    bool Select(QString database,QString sql);
    bool Insert(QString database,QString sql);
    bool Delete(QString database,QString sql);
    bool Update(QString database,QString sql);
    bool Parse(QString sql);//解析
    QString match(QString sql);
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

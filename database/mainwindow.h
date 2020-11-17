#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <mydbms.h>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void init();
    void dbtest(QString);
signals:
    void mysignal(); //自定义信号
private slots:
    void message(QString);
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    myDBMS *db;
    QStringList squece;

protected:

    virtual void closeEvent(QCloseEvent *event);

};
#endif // MAINWINDOW_H

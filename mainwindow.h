#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QDir>
#include <QDebug>
#include<QFileDialog>
#include <QTableView>
#include <QStandardItemModel>
#include <table.h>
#include <field.h>
#include <qtextcodec.h>
#include <QTextCodec>
#include <QPushButton>
#include <QMenu>
#include <QMessageBox>
#include <QCloseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_open_triggered();

    void on_addtable_triggered();

    void on_findtable_triggered();

    void on_backbutton_clicked();

    void on_pushButton_clicked();

    void on_clearbutton_clicked();

    void on_readtable_triggered(QString);

    void on_readdb_triggered();

    void on_treeWidget_itemSelectionChanged();

private:
    Ui::MainWindow *ui;
    QString filename;
};
#endif // MAINWINDOW_H

#include "mydbms.h"


void myDBMS::transfer() {
    for (int i = 0; i < cmd.size(); i++)
        cmd[i] = cmd[i].toLower();
}

void myDBMS::openDataBase(QString dataBaseName) {
    if (open) {
        emit sendmessage("请先关闭当前打开的数据库");
        return;
    }
    QString pathName = "D:\\test\\" + dataBaseName;
    if (QDir(pathName).exists() == false)printf("该数据库不存在");
    else {
        prePath = pathName + "\\";
         emit sendmessage("打开数据库成功");
        open = true;
    }
}

void myDBMS::closeDataBase(QString dataBaseName) {//和析构函数相同
    if (!open) {
        emit sendmessage("请先打开数据库");
        return;
    }
    QString pathName = "D:\\test\\" + dataBaseName;
    if (QDir(pathName).exists() == false)printf("该数据库不存在");
    else {
        for (int i = 0; i < tab.size(); i++) {
            if (tab[i]->fp != NULL)
                fclose(tab[i]->fp);
            delete tab[i];
        }
        tab.resize(0);
        cmd = "";
        prePath = "";
        emit sendmessage("关闭数据库成功");
        open = false;
    }


}

//D:\\test
void myDBMS::myCreateDataBase(QString dataBaseName) {//建立数据库
    QString pathName = "D:\\test\\" + dataBaseName;
    if (QDir(pathName).exists() == false) {
        if (QDir().mkdir(pathName))//返回0表示创建成功,-1表示失败
            emit sendmessage("创建成功");
        else
            emit sendmessage("创建失败");
        return;
    }
    emit sendmessage("该数据库已存在");
}

void myDBMS::myDropDataBase(QString dataBaseName) {//删除数据库
    QString pathName = "D:\\test\\" + dataBaseName;
    if (QDir(pathName).exists() == true) {

        if (DelDir(pathName) == true)
           emit sendmessage("删除数据库成功");
        else
           emit sendmessage("删除数据库失败");
        return;
    }
    emit sendmessage("数据库不存在");
}

//删除文件夹
bool myDBMS::DelDir(const QString &path)
{
    if (path.isEmpty()){
        return false;
    }
    QDir dir(path);
    if(!dir.exists()){
        return true;
    }
    dir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot); //设置过滤
    QFileInfoList fileList = dir.entryInfoList(); // 获取所有的文件信息
    foreach (QFileInfo file, fileList){ //遍历文件信息
        if (file.isFile()){ // 是文件，删除
            file.dir().remove(file.fileName());
        }else{ // 递归删除
            DelDir(file.absoluteFilePath());
        }
    }
    return dir.rmpath(dir.absolutePath()); // 删除文件夹
}

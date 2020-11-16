#include "mainwindow.h"
#include "ui_mainwindow.h"


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


//预读字段表内字段
void MainWindow::read_tableField(QString tableName){
    QString fileName = "D:\\Qtopen\\DBMS-YBY-FIELD\\table\\" + tableName;
    QFile table(fileName);

    if(!table.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        this->ui->textEdit_2->setText("CAN'T OPEN THE FILE!");
        return;

    }
    else{

        while(!table.atEnd()){//筛选属性
            QByteArray line = table.readLine();
            QString str(line);
            str = str.simplified();
            QStringList strList = str.split(" ");


            field a_field;
            a_field.set_tableName(this->thisField.get_tableName());
            a_field.set_name(strList[0]);
            a_field.set_dataType(strList[1]);
            a_field.set_PK(strList[2]);
            a_field.set_unique(strList[3]);
            a_field.set_notNull(strList[4]);
            a_field.set_defaultValue(strList[5]);
            a_field.set_checkUP(strList[6]);
            a_field.set_checkDown(strList[7]);
            a_field.set_FK_tableName(strList[8]);
            a_field.set_deleteLimit(strList[9]);


            this->allFields.append(a_field);


        }

        table.close();
        return;
    }
}



//用于清除字段文件中的内容并写入allFields
void MainWindow::update_field_file(QString tableName){
    int i = 0;
    QString fileName = "D:\\Qtopen\\DBMS-YBY-FIELD\\table\\" + tableName;
    QFile table(fileName);
    table.open(QIODevice::WriteOnly|QIODevice::Text);
    QTextStream stream(&table);
    stream.seek(table.size());
    stream << "";
    table.close();


    table.open(QIODevice::WriteOnly|QIODevice::Append);
    QTextStream stream1(&table);
    stream1.seek(table.size());
    QVector<field>::iterator iter; //迭代器
    for(iter=allFields.begin();iter!=allFields.end();iter++){
        QString aline = iter->get_name() + " "
                        + iter->get_dataType() + " "
                        + iter->get_PK() + " "
                        + iter->get_unique() + " "
                        + iter->get_notNull() + " "
                        + iter->get_defaultValue() + " "
                        + iter->get_checkUP() + " "
                        + iter->get_checkDown() + " "
                        + iter->get_FK_tableName() + " "
                        + iter->get_deleteLimit();
        qDebug()<<aline;

        stream1 << aline;
        i++;
        if(i != allFields.count()){
            stream1 << endl;
        }
    }
    table.close();


}

//对字段文件执行插入行操作 ALTER TABLE student ADD cno VARCHAR(20)
QString MainWindow::insert_field(){

    QVector<field>::iterator iter; //迭代器,检查是否插入同名属性
    for(iter=allFields.begin();iter!=allFields.end();iter++){
       if(iter->get_name() == this->thisField.get_name()){

           this->ui->textEdit_2->setText("THE ATTRIBUTE NAME IS ALREADY IN USE");
           return "THE ATTRIBUTE NAME IS ALREADY IN USE";
       }
    }

    this->allFields.append(this->thisField);
    this->update_field_file(this->thisField.get_tableName());
    this->ui->textEdit_2->setText("INSERT SUCCESSFULLY!");
    return "INSERT SUCCESSFULLY!";

}



//对字段文件执行删除行操作ALTER TABLE student DROP COLUMN cno
QString MainWindow::drop_field(){

    int i = 0;
    QVector<field>::iterator iter; //迭代器,检查有无该属性
    for(iter=allFields.begin();iter!=allFields.end();iter++){
       if(iter->get_name() == this->thisField.get_name()){
           this->allFields.remove(i);
           this->update_field_file(this->thisField.get_tableName());
           this->ui->textEdit_2->setText("DROP SUCCESSFULLY!");
           return "DROP SUCCESSFULLY!";
       }
       i++;
    }

    this->ui->textEdit_2->setText("CAN'T FIND IT!");
    return "DROP FAILED!";
}

/****************************************************************************/





//预读用户信息
void MainWindow::read_userField(){
    QString fileName = "D:\\Qtopen\\DBMS-YBY-FIELD\\user.txt";
    QFile table(fileName);

    if(!table.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        this->ui->textEdit_2->setText("CAN'T OPEN THE FILE!");
        return;

    }
    else{

        while(!table.atEnd()){//筛选属性
            QByteArray line = table.readLine();
            qDebug() <<line;
            QString str(line);
            str = str.simplified();
            QStringList strList = str.split(" ");


            user a_user;
            a_user.set_Name(strList[0]);
            a_user.set_Password(strList[1]);
            a_user.set_DBA(strList[2]);
            a_user.set_RESOURCE(strList[3]);
            a_user.set_CONNECT(strList[4]);


            this->allUsers.append(a_user);


        }

        table.close();
        return;
    }
}

void MainWindow::update_user_file(){
    int i =0;
    QString userName = "D:\\Qtopen\\DBMS-YBY-FIELD\\user.txt";
    QFile file(userName);
    file.open(QIODevice::WriteOnly|QIODevice::Text);
    QTextStream stream(&file);
    stream.seek(file.size());
    stream << "";
    file.close();


    file.open(QIODevice::WriteOnly|QIODevice::Append);
    QTextStream stream1(&file);
    stream1.seek(file.size());
    QVector<user>::iterator iter; //迭代器
    for(iter=allUsers.begin();iter!=allUsers.end();iter++){
        QString aline = iter->get_Name() + " "
                        + iter->get_Password() + " "
                        + iter->get_DBA() + " "
                        + iter->get_RESOURCE() + " "
                        + iter->get_CONNECT();
        qDebug()<<aline;

        stream1 << aline;
        i++;
        if(i != allUsers.count()){
            stream1 << endl;
        }
    }
    file.close();


}


//添加新用户 CREATE USER yby IDENTIFIED BY yby
QString MainWindow::insert_user(){
    QVector<user>::iterator iter; //迭代器,检查是否插入同名属性

    for(iter=allUsers.begin();iter!=allUsers.end();iter++){
       if(iter->get_Name() == this->thisUser.get_Name()){

           this->ui->textEdit_2->setText("THE USER IS ALREADY IN USE");
           return "THE USER ALREADY IN USE";
       }

    }

    this->allUsers.append(this->thisUser);
    this->update_user_file();
    this->ui->textEdit_2->setText("CREATE USER SUCCESSFULLY!");
    return "CREATE USER SUCCESSFULLY!";
}

QString MainWindow::drop_user(){
    int i = 0;
    QVector<user>::iterator iter; //迭代器,检查有无该属性
    for(iter=allUsers.begin();iter!=allUsers.end();iter++){
       if(iter->get_Name() == this->thisUser.get_Name()){
           this->allUsers.remove(i);
           this->update_user_file();
           this->ui->textEdit_2->setText("DROP USER SUCCESSFULLY!");
           return "DROP USER SUCCESSFULLY!";
       }
       i++;
    }

    this->ui->textEdit_2->setText("CAN'T FIND IT!");
    return "DROP USER FAILED!";

}



//SQL 解析
void MainWindow::on_pushButton_clicked()
{
    this->thisField.refresh_field();//刷新对象
    this->thisUser.refresh_user();//刷新用户
    this->allFields.clear();//刷新字段容器
    this->allUsers.clear();//刷新用户容器


    //按空格切割sql语句
    this->sql = this->ui->textEdit->toPlainText();
    sql = sql.simplified();
    sql = sql.remove(QChar(';'), Qt::CaseInsensitive);//括号清除
    QString firstSql = sql.toLower();//保存初始sql用于正则表达式处理

    sql = sql.replace(QRegExp("\\,"), " "); 
    sql = sql.toLower();
    this->sqlList = sql.split(" ");
    qDebug() << sqlList.size();


    //确认该语句指向字段修改
    if(sqlList[0].toLower() == "alter" && sqlList[1].toLower() == "table"){

        this->thisField.set_tableName(sqlList[2] + ".txt");//确认关系名
        this->read_tableField(this->thisField.get_tableName());//读入容器

    }

    //CREATE USER 111 IDENTIFIED BY 111;创建用户
    else if(sqlList[0].toLower() == "create" && sqlList[1].toLower() == "user"
            && sqlList[3].toLower() == "identified" && sqlList[4].toLower() == "by" && sqlList.length() == 6){
        this->read_userField();//读入用户
        this->thisUser.set_Name(sqlList[2]);
        this->thisUser.set_Password(sqlList[5]);
        insert_user();
        return;
    }

    //DROP USER 111;删除用户
    else if(sqlList[0].toLower() == "drop" && sqlList[1].toLower() == "user" && sqlList.length() == 3){
        this->read_userField();//读入用户
        this->thisUser.set_Name(sqlList[2]);
        drop_user();
        return;
    }

    //GRAND CONNECT, RESOURCE, DBA TO yby;授权
    else if(sqlList[0] == "grand" && sqlList.length() >= 4){
        QRegularExpression rx1("^(grand)\\s(connect|dba|resource)\\s(to)\\s([A-Za-z0-9]+)$");
        QRegularExpressionMatch match1 = rx1.match(firstSql);
        QRegularExpression rx2("^(grand)\\s(connect|dba|resource)\\s*(\\,)\\s*(connect|dba|resource)\\s(to)\\s([A-Za-z0-9]+)$");
        QRegularExpressionMatch match2 = rx2.match(firstSql);
        QRegularExpression rx3("^(grand)\\s(connect|dba|resource)\\s*(\\,)\\s*(connect|dba|resource)\\s*\\,\\s*(connect|dba|resource)\\s(to)\\s([A-Za-z0-9]+)$");
        QRegularExpressionMatch match3 = rx3.match(firstSql);
        QRegularExpression rx8("^grand all on [A-Za-z0-9]+ to [A-Za-z0-9]+$");
        QRegularExpressionMatch match8 = rx8.match(firstSql);
        //if(match1.hasMatch()){

        this->read_userField();//读入用户
        this->thisUser.set_Name(sqlList[sqlList.length()-1]);
        int i = 0;
        QVector<user>::iterator iter; //迭代器,找到对应的用户
        for(iter=allUsers.begin();iter!=allUsers.end();iter++){
            if(iter->get_Name() == this->thisUser.get_Name()){
                break;
            }
            i++;
            if(i == this->allUsers.count()){
                this->ui->textEdit_2->setText("CAN'T FIND USER!");
                return;
            }
        }

        this->thisUser.set_Name(sqlList[sqlList.length()-1]);
        if(match1.hasMatch()){
                if(sqlList[1] == "dba"){
                    allUsers[i].set_DBA("TRUE");
                    update_user_file();
                    this->ui->textEdit_2->setText("GRAND succeeded!");
                    return;
                }
                else if(sqlList[1] == "connect"){
                    allUsers[i].set_CONNECT("TRUE");
                    update_user_file();
                    this->ui->textEdit_2->setText("GRAND succeeded!");
                    return;
                }
                else if(sqlList[1] == "resource"){
                    allUsers[i].set_RESOURCE("TRUE");
                    update_user_file();
                    this->ui->textEdit_2->setText("GRAND succeeded!");
                    return;
                }
                else{
                    this->ui->textEdit_2->setText("WRONG SQL STATEMENT!");
                    return;
                }
            }
        else if(match2.hasMatch()){
            if(sqlList[1] != "dba" && sqlList[2] != "connect"){
                allUsers[i].set_CONNECT("TRUE");
                allUsers[i].set_RESOURCE("TRUE");
                update_user_file();
                this->ui->textEdit_2->setText("GRAND succeeded!");
                return;
            }
            else if(sqlList[1] != "connect" && sqlList[2] != "connect"){
                allUsers[i].set_DBA("TRUE");
                allUsers[i].set_RESOURCE("TRUE");
                update_user_file();
                this->ui->textEdit_2->setText("GRAND succeeded!");
                return;
            }
            else if(sqlList[1] != "resource" && sqlList[2] != "resource"){
                allUsers[i].set_DBA("TRUE");
                allUsers[i].set_CONNECT("TRUE");
                update_user_file();
                this->ui->textEdit_2->setText("GRAND succeeded!");
                return;
            }
            else{
                this->ui->textEdit_2->setText("WRONG SQL STATEMENT!");
                return;
            }
        }
        else if(match3.hasMatch()){
            allUsers[i].set_CONNECT("TRUE");
            allUsers[i].set_RESOURCE("TRUE");
            allUsers[i].set_DBA("TRUE");
            update_user_file();
            this->ui->textEdit_2->setText("GRAND succeeded!");
            return;
        }

        //具体到表的权限GRAND ALL ON STUDENT TO WMY;
        else if(match8.hasMatch()){
            QString filename = "D:\\Qtopen\\DBMS-YBY-FIELD\\user\\" +sqlList[3]+".txt";
            QFile usertable(filename);
            QStringList strList1;

            if(!usertable.open(QIODevice::ReadWrite | QIODevice::Text))
            {
                this->ui->textEdit_2->setText("CAN'T OPEN THE FILE!");
                return;

            }
            else{
                while(!usertable.atEnd()){
                    QByteArray line = usertable.readLine();
                    QString str(line);
                    if(str == this->thisUser.get_Name()){
                        this->ui->textEdit_2->setText("GRAND succeeded!");
                        return;
                    }
                }
            }
            usertable.close();

            if(!usertable.open(QIODevice::ReadWrite | QIODevice::Append))
            {
                this->ui->textEdit_2->setText("CAN'T OPEN THE FILE!");
                return;

            }
            else{

                QTextStream stream1(&usertable);
                stream1.seek(usertable.size());
                stream1 << endl << this->thisUser.get_Name();
                }

                usertable.close();
                this->ui->textEdit_2->setText("GRAND succeeded!");
                return;
        }



        else{

            this->ui->textEdit_2->setText("WRONG SQL STATEMENT!");
            return;
        }

    }

    //REVOKE CONNECT, RESOURCE, DBA FROM yby;删权
    else if(sqlList[0] == "revoke" && sqlList.length() >= 4){
        QRegularExpression rx1("^(revoke)\\s(connect|dba|resource)\\s(from)\\s([A-Za-z0-9]+)$");
        QRegularExpressionMatch match1 = rx1.match(firstSql);
        QRegularExpression rx2("^(revoke)\\s(connect|dba|resource)\\s*(\\,)\\s*(connect|dba|resource)\\s(from)\\s([A-Za-z0-9]+)$");
        QRegularExpressionMatch match2 = rx2.match(firstSql);
        QRegularExpression rx3("^(revoke)\\s(connect|dba|resource)\\s*(\\,)\\s*(connect|dba|resource)\\s*\\,\\s*(connect|dba|resource)\\s(from)\\s([A-Za-z0-9]+)$");
        QRegularExpressionMatch match3 = rx3.match(firstSql);
        QRegularExpression rx8("^revoke all on [A-Za-z0-9]+ from [A-Za-z0-9]+$");
        QRegularExpressionMatch match8 = rx8.match(firstSql);


        this->read_userField();//读入用户
        this->thisUser.set_Name(sqlList[sqlList.length()-1]);
        int i = 0;
        QVector<user>::iterator iter; //迭代器,找到对应的用户
        for(iter=allUsers.begin();iter!=allUsers.end();iter++){
            if(iter->get_Name() == this->thisUser.get_Name()){
                break;
            }
            i++;
            if(i == this->allUsers.count()){
                this->ui->textEdit_2->setText("CAN'T FIND IT!");
                return;
            }
        }

        this->thisUser.set_Name(sqlList[sqlList.length()-1]);
        if(match1.hasMatch()){
                if(sqlList[1] == "dba"){
                    allUsers[i].set_DBA("FALSE");
                    update_user_file();
                    this->ui->textEdit_2->setText("REVOKE succeeded!");
                    return;
                }
                else if(sqlList[1] == "connect"){
                    allUsers[i].set_CONNECT("FALSE");
                    update_user_file();
                    this->ui->textEdit_2->setText("REVOKE succeeded!");
                    return;
                }
                else if(sqlList[1] == "resource"){
                    allUsers[i].set_RESOURCE("FALSE");
                    update_user_file();
                    this->ui->textEdit_2->setText("REVOKE succeeded!");
                    return;
                }
                else{
                    this->ui->textEdit_2->setText("WRONG SQL STATEMENT!");
                    return;
                }
            }
        else if(match2.hasMatch()){
            if(sqlList[1] != "dba" && sqlList[2] != "connect"){
                allUsers[i].set_CONNECT("FALSE");
                allUsers[i].set_RESOURCE("FALSE");
                update_user_file();
                this->ui->textEdit_2->setText("REVOKE succeeded!");
                return;
            }
            else if(sqlList[1] != "connect" && sqlList[2] != "connect"){
                allUsers[i].set_DBA("FALSE");
                allUsers[i].set_RESOURCE("FALSE");
                update_user_file();
                this->ui->textEdit_2->setText("REVOKE succeeded!");
                return;
            }
            else if(sqlList[1] != "resource" && sqlList[2] != "resource"){
                allUsers[i].set_DBA("FALSE");
                allUsers[i].set_CONNECT("FALSE");
                update_user_file();
                this->ui->textEdit_2->setText("REVOKE succeeded!");
                return;
            }
            else{
                this->ui->textEdit_2->setText("WRONG SQL STATEMENT!");
                return;
            }
        }
        else if(match3.hasMatch()){
            allUsers[i].set_CONNECT("FALSE");
            allUsers[i].set_RESOURCE("FALSE");
            allUsers[i].set_DBA("FALSE");
            update_user_file();
            this->ui->textEdit_2->setText("REVOKE succeeded!");
            return;
        }

        //删除具体权限REVOKE ALL ON STUDENT FROM WMY;
        else if(match8.hasMatch()){
            QString filename = "D:\\Qtopen\\DBMS-YBY-FIELD\\user\\" +sqlList[3]+".txt";
            QFile usertable1(filename);
            QStringList strList1;

            if(!usertable1.open(QIODevice::ReadWrite | QIODevice::Text))
            {
                this->ui->textEdit_2->setText("CAN'T OPEN THE FILE!");
                return;

            }
            else{
                while(!usertable1.atEnd()){

                    QByteArray line = usertable1.readLine();
                    QString str(line);
                    if(str != this->thisUser.get_Name()){
                        strList1 << str;

                    }

                }
            }
            usertable1.close();

            /********************************/

            usertable1.open(QIODevice::WriteOnly|QIODevice::Text);
            QTextStream stream(&usertable1);
            stream.seek(usertable1.size());
            stream << "";
            usertable1.close();


            usertable1.open(QIODevice::WriteOnly|QIODevice::Append);
            QTextStream stream1(&usertable1);
            stream1.seek(usertable1.size());

            for(int i = 0;i<strList1.length();){
                QString aline = strList1[i];
                aline = aline.simplified();
                qDebug()<<aline;
                stream1 << aline;
                i++;
                if(i != strList1.length()){
                    stream1 << endl;
                }
            }
            usertable1.close();
            this->ui->textEdit_2->setText("REVOKE succeeded!");
            return;
        }


        else{
            this->ui->textEdit_2->setText("WRONG SQL STATEMENT!");
            return;
        }

    }
    else{
        this->ui->textEdit_2->setText("WRONG SQL STATEMENT!");
        return;
    }

/**************************************************************************************************/
    //确认该语句指向添加属性, 若为 add column 则长度必然大于等于七个单词
    //ALTER TABLE student ADD COLUMN cno VARCHAR(20) UNIQUE NOTNULL DEFAULT XXX;
    if(sqlList[3].toLower() == "add" && sqlList[4].toLower() == "column" && sqlList.length() >=7 ){

        this->thisField.set_tableName(sqlList[2] + ".txt");//确认表名

        //正则表达式判断数据类型书写正确性
        QRegularExpression rx4("(varchar|int)\\([0-9]*\\)");
        QRegularExpressionMatch match4 = rx4.match(firstSql);
        QRegularExpression rx5("(varchar|int)");
        QRegularExpressionMatch match5 = rx5.match(firstSql);

        if(!match4.hasMatch() && !match5.hasMatch()){
            this->ui->textEdit_2->setText("WRONG SQL STATEMENT!");
            return;
        }
        this->thisField.set_name(sqlList[5]);//确认属性名
        this->thisField.set_dataType(sqlList[6]);//确认属性数据类型
        //(varchar\([0-9]*\)|int\([0-9]*\))

        if(sqlList.length() == 7){
            insert_field();//插入
            return;
        }

        else if(sqlList.length() == 8){
            if(sqlList[7].toLower() == "notnull"){//非空设置
                this->thisField.set_notNull("TRUE");
                insert_field();//插入
                return;
            }
            else if(sqlList[7].toLower() == "unique"){//唯一设置
                this->thisField.set_unique("TRUE");
                insert_field();//插入
                return;
            }
            else{
                this->ui->textEdit_2->setText("WRONG SQL STATEMENT!");
                return;
            }
        }

        else if(sqlList.length() == 9){
            if(sqlList[7].toLower() == "default"){//默认值设置
                this->thisField.set_defaultValue(sqlList[8]);
                insert_field();//插入
                return;
            }
            else if(sqlList[7].toLower() == "unique" && sqlList[8].toLower() == "notnull"){
                this->thisField.set_unique("TRUE");
                this->thisField.set_notNull("TRUE");
                insert_field();//插入
                return;
            }
            else if(sqlList[8].toLower() == "unique" && sqlList[7].toLower() == "notnull"){
                this->thisField.set_unique("TRUE");
                this->thisField.set_notNull("TRUE");
                insert_field();//插入
                return;
            }
            else{
                this->ui->textEdit_2->setText("WRONG SQL STATEMENT!");
                return;
            }
        }

        else if(sqlList.length() == 10){//既有非空又有默认值
            if(sqlList[7].toLower() == "default" && sqlList[9].toLower() == "notnull"){//默认值和非空设置
                this->thisField.set_defaultValue(sqlList[8]);
                this->thisField.set_notNull("TRUE");
                insert_field();//插入
                return;
            }
            else if(sqlList[7].toLower() == "default" && sqlList[9].toLower() == "unique"){//默认值和唯一设置
                this->thisField.set_defaultValue(sqlList[8]);
                this->thisField.set_unique("TRUE");
                insert_field();//插入
                return;
            }
            else if(sqlList[7].toLower() == "notnull" && sqlList[8].toLower() == "default"){//默认值和非空设置
                this->thisField.set_defaultValue(sqlList[9]);
                this->thisField.set_notNull("TRUE");
                insert_field();//插入
                return;
            }
            else if(sqlList[7].toLower() == "unique" && sqlList[8].toLower() == "default"){//默认值和唯一设置
                this->thisField.set_defaultValue(sqlList[9]);
                this->thisField.set_unique("TRUE");
                insert_field();//插入
                return;
            }
            else{
                this->ui->textEdit_2->setText("WRONG SQL STATEMENT!");
                return;
            }
        }

        else if(sqlList.length() == 11){//三项全占
            if(sqlList[7].toLower() == "default" && sqlList[9].toLower() == "notnull" && sqlList[10].toLower() == "unique"){
                this->thisField.set_defaultValue(sqlList[8]);
                this->thisField.set_unique("TRUE");
                this->thisField.set_notNull("TRUE");
                insert_field();//插入
                return;
            }
            else if(sqlList[7].toLower() == "default" && sqlList[10].toLower() == "notnull" && sqlList[9].toLower() == "unique"){
                this->thisField.set_defaultValue(sqlList[8]);
                this->thisField.set_unique("TRUE");
                this->thisField.set_notNull("TRUE");
                insert_field();//插入
                return;
            }
            else if(sqlList[8].toLower() == "default" && sqlList[7].toLower() == "notnull" && sqlList[10].toLower() == "unique"){
                this->thisField.set_defaultValue(sqlList[9]);
                this->thisField.set_unique("TRUE");
                this->thisField.set_notNull("TRUE");
                insert_field();//插入
                return;
            }
            else if(sqlList[8].toLower() == "default" && sqlList[10].toLower() == "notnull" && sqlList[7].toLower() == "unique"){
                this->thisField.set_defaultValue(sqlList[9]);
                this->thisField.set_unique("TRUE");
                this->thisField.set_notNull("TRUE");
                insert_field();//插入
                return;
            }
            else if(sqlList[9].toLower() == "default" && sqlList[7].toLower() == "notnull" && sqlList[8].toLower() == "unique"){
                this->thisField.set_defaultValue(sqlList[10]);
                this->thisField.set_unique("TRUE");
                this->thisField.set_notNull("TRUE");
                insert_field();//插入
                return;
            }
            else if(sqlList[9].toLower() == "default" && sqlList[8].toLower() == "notnull" && sqlList[7].toLower() == "unique"){
                this->thisField.set_defaultValue(sqlList[10]);

                this->thisField.set_unique("TRUE");
                this->thisField.set_notNull("TRUE");
                insert_field();//插入
                return;
            }
            else{
                this->ui->textEdit_2->setText("WRONG SQL STATEMENT!");
                return;
            }

        }
        else{
            this->ui->textEdit_2->setText("WRONG SQL STATEMENT!");
            return;
        }


    }


/**************************************************************************************************/
    //确认语句指向删除字段
    //ALTER TABLE student DROP COLUMN cno RESTRICT|CASCADE;
    else if(sqlList[3].toLower() == "drop" && sqlList[4].toLower() == "column" && sqlList.length() >=6){

        this->thisField.set_name(sqlList[5]);//确认属性名
        this->thisField.set_tableName(sqlList[2] + ".txt");//确认表名

        //若为 drop column 则长度必然大于等于六个单词，等于六为默认删除
        if(sqlList.length()<7){
            this->thisField.set_deleteLimit("RESTRICT");
            drop_field();//删除字段
            return;
        }

        else if(sqlList.length() == 7){//确认删除类型

            if(sqlList[6].toLower() == "restrict" || sqlList[6].toLower() == "cascade"){
                this->thisField.set_deleteLimit(sqlList[6].toUpper());
                drop_field();//删除字段
                return;
            }

            else{
                this->ui->textEdit_2->setText("WRONG SQL STATEMENT!");
                return;
            }

        }

        else{
            this->ui->textEdit_2->setText("WRONG SQL STATEMENT!");
            return;
        }

    }


/**************************************************************************************************/
    //修改字段的属性
    //ALTER TABLE student MODIFY COLUMN cno UNIQUE|DEFAULT XXX|NOTNULL|DATATYPE
    //ALTER TABLE student MODIFY COLUMN cno DEFAULT XXX
    //ALTER TABLE student MODIFY COLUMN sno INT(10) UNIQUE
    else if(sqlList[3].toLower() == "modify" && sqlList[4].toLower() == "column" && sqlList.length() >=7){
        this->thisField.set_name(sqlList[5]);//确认属性名
        this->thisField.set_tableName(sqlList[2] + ".txt");//确认表名
        //正则表达式判断数据类型书写正确性
        QRegularExpression rx6("(varchar|int)\\([0-9]*\\)");
        QRegularExpressionMatch match6 = rx6.match(firstSql);
        QRegularExpression rx7("(varchar|int)");
        QRegularExpressionMatch match7 = rx7.match(firstSql);

//        if(!match6.hasMatch() && !match7.hasMatch()){
//            this->ui->textEdit_2->setText("WRONG SQL STATEMENT!");
//            return;
//        }

        int i = 0;
        QVector<field>::iterator iter; //迭代器,找到对应的字段
        for(iter=allFields.begin();iter!=allFields.end();iter++){
           if(iter->get_name() == this->thisField.get_name()){

               break;
           }
           i++;
           if(i == this->allFields.count()){
               this->ui->textEdit_2->setText("CAN'T FIND IT!");
               return;
           }
        }

        //单项修改
        if(sqlList.length() == 7){//修改数据类型

            if(match6.hasMatch() || match7.hasMatch()){
                allFields[i].set_dataType(sqlList[6].toUpper());

                this->update_field_file(this->thisField.get_tableName());
                this->ui->textEdit_2->setText("Modification succeeded!");
                return;
            }
            else if(sqlList[6].toLower() == "unique"){//修改唯一性
                allFields[i].set_unique("TRUE");

                this->update_field_file(this->thisField.get_tableName());
                this->ui->textEdit_2->setText("Modification succeeded!");
                return;
            }
            else if(sqlList[6].toLower() == "notnull"){//修改非空
                allFields[i].set_notNull("TRUE");

                this->update_field_file(this->thisField.get_tableName());
                this->ui->textEdit_2->setText("Modification succeeded!");
                return;
            }
            else{
                this->ui->textEdit_2->setText("WRONG SQL STATEMENT!");
                return;
            }

        }

        else if(sqlList.length() == 8){
            if(sqlList[6].toLower() == "notnull" && sqlList[7].toLower() == "unique"){//非空且唯一
                allFields[i].set_notNull("TRUE");
                allFields[i].set_unique("TRUE");

                this->update_field_file(this->thisField.get_tableName());
                this->ui->textEdit_2->setText("Modification succeeded!");
                return;
            }
            else if(sqlList[7].toLower() == "notnull" && sqlList[6].toLower() == "unique"){//非空且唯一
                allFields[i].set_notNull("TRUE");
                allFields[i].set_unique("TRUE");

                this->update_field_file(this->thisField.get_tableName());
                this->ui->textEdit_2->setText("Modification succeeded!");
                return;
            }
            else if((match6.hasMatch() || match7.hasMatch())
                    && sqlList[6].toLower() == "unique"){//数据类型和唯一
                allFields[i].set_dataType(sqlList[7].toUpper());
                allFields[i].set_unique("TRUE");

                this->update_field_file(this->thisField.get_tableName());
                this->ui->textEdit_2->setText("Modification succeeded!");
                return;
            }
            else if((match6.hasMatch() || match7.hasMatch())
                    && sqlList[7].toLower() == "unique"){//数据类型和唯一
                allFields[i].set_dataType(sqlList[6].toUpper());
                allFields[i].set_unique("TRUE");

                this->update_field_file(this->thisField.get_tableName());
                this->ui->textEdit_2->setText("Modification succeeded!");
                return;
            }
            else if(sqlList[7].toLower() == "notnull" && (match6.hasMatch() || match7.hasMatch())){//数据类型和非空
                allFields[i].set_notNull("TRUE");
                allFields[i].set_dataType(sqlList[6].toUpper());

                this->update_field_file(this->thisField.get_tableName());
                this->ui->textEdit_2->setText("Modification succeeded!");
                return;
            }
            else if(sqlList[6].toLower() == "notnull" && (match6.hasMatch() || match7.hasMatch())){//数据类型和非空
                allFields[i].set_notNull("TRUE");
                allFields[i].set_dataType(sqlList[7].toUpper());

                this->update_field_file(this->thisField.get_tableName());
                this->ui->textEdit_2->setText("Modification succeeded!");
                return;
            }
            else if(sqlList[6].toLower() == "default"){//修改默认值
                allFields[i].set_defaultValue(sqlList[7]);
                this->update_field_file(this->thisField.get_tableName());
                this->ui->textEdit_2->setText("Modification succeeded!");
                return;
            }
            else{
                this->ui->textEdit_2->setText("WRONG SQL STATEMENT!");
                return;
            }
        }

        else if(sqlList.length() == 9){
            if(sqlList[6].toLower() == "default"){//默认值设置,且非空或唯一或数据类型
                allFields[i].set_defaultValue(sqlList[7]);

                if(sqlList[8].toLower() == "notnull"){//非空
                    allFields[i].set_notNull("TRUE");
                    this->update_field_file(this->thisField.get_tableName());
                    this->ui->textEdit_2->setText("Modification succeeded!");
                    return;
                }

                else if(sqlList[8].toLower() == "unique"){//唯一
                    allFields[i].set_unique("TRUE");
                    this->update_field_file(this->thisField.get_tableName());
                    this->ui->textEdit_2->setText("Modification succeeded!");
                    return;
                }

                else if(match6.hasMatch() || match7.hasMatch()){//数据类型
                    allFields[i].set_dataType(sqlList[8].toUpper());
                    this->update_field_file(this->thisField.get_tableName());
                    this->ui->textEdit_2->setText("Modification succeeded!");
                    return;
                }
                else{
                    this->ui->textEdit_2->setText("WRONG SQL STATEMENT!");
                    return;
                }

            }

            else if(sqlList[7].toLower() == "default"){//默认值设置,且非空或唯一或数据类型
                allFields[i].set_defaultValue(sqlList[8]);

                if(sqlList[6].toLower() == "notnull"){//非空
                    allFields[i].set_notNull("TRUE");
                    this->update_field_file(this->thisField.get_tableName());
                    this->ui->textEdit_2->setText("Modification succeeded!");
                    return;
                }

                else if(sqlList[6].toLower() == "unique"){//唯一
                    allFields[i].set_unique("TRUE");
                    this->update_field_file(this->thisField.get_tableName());
                    this->ui->textEdit_2->setText("Modification succeeded!");
                    return;
                }

                else if(match6.hasMatch() || match7.hasMatch()){//数据类型
                    allFields[i].set_dataType(sqlList[6].toUpper());
                    this->update_field_file(this->thisField.get_tableName());
                    this->ui->textEdit_2->setText("Modification succeeded!");
                    return;
                }
                else{
                    this->ui->textEdit_2->setText("WRONG SQL STATEMENT!");
                    return;
                }
            }

            else if(sqlList[6].toLower() == "notnull" && (match6.hasMatch() || match7.hasMatch()) && sqlList[8].toLower() == "unique"){//非空、数据类型、唯一
                allFields[i].set_unique("TRUE");
                allFields[i].set_dataType(sqlList[7].toUpper());
                allFields[i].set_notNull("TRUE");

                this->update_field_file(this->thisField.get_tableName());
                this->ui->textEdit_2->setText("Modification succeeded!");
                return;
            }

            else if(sqlList[6].toLower() == "notnull" && (match6.hasMatch() || match7.hasMatch()) && sqlList[7].toLower() == "unique"){
                allFields[i].set_unique("TRUE");
                allFields[i].set_dataType(sqlList[8].toUpper());
                allFields[i].set_notNull("TRUE");

                this->update_field_file(this->thisField.get_tableName());
                this->ui->textEdit_2->setText("Modification succeeded!");
                return;
            }

            else if(sqlList[7].toLower() == "notnull" && (match6.hasMatch() || match7.hasMatch()) && sqlList[8].toLower() == "unique"){
                allFields[i].set_unique("TRUE");
                allFields[i].set_dataType(sqlList[6].toUpper());
                allFields[i].set_notNull("TRUE");

                this->update_field_file(this->thisField.get_tableName());
                this->ui->textEdit_2->setText("Modification succeeded!");
                return;
            }

            else if(sqlList[8].toLower() == "notnull" && (match6.hasMatch() || match7.hasMatch()) && sqlList[7].toLower() == "unique"){
                allFields[i].set_unique("TRUE");
                allFields[i].set_dataType(sqlList[6].toUpper());
                allFields[i].set_notNull("TRUE");

                this->update_field_file(this->thisField.get_tableName());
                this->ui->textEdit_2->setText("Modification succeeded!");
                return;
            }

            else if(sqlList[7].toLower() == "notnull" && (match6.hasMatch() || match7.hasMatch()) && sqlList[6].toLower() == "unique"){
                allFields[i].set_unique("TRUE");
                allFields[i].set_dataType(sqlList[8].toUpper());
                allFields[i].set_notNull("TRUE");

                this->update_field_file(this->thisField.get_tableName());
                this->ui->textEdit_2->setText("Modification succeeded!");
                return;
            }

            else if(sqlList[8].toLower() == "notnull" && (match6.hasMatch() || match7.hasMatch()) && sqlList[6].toLower() == "unique"){
                allFields[i].set_unique("TRUE");
                allFields[i].set_dataType(sqlList[7].toUpper());
                allFields[i].set_notNull("TRUE");

                this->update_field_file(this->thisField.get_tableName());
                this->ui->textEdit_2->setText("Modification succeeded!");
                return;
            }

            else{
                this->ui->textEdit_2->setText("WRONG SQL STATEMENT!");
                return;
            }
        }
        else{
            this->ui->textEdit_2->setText("WRONG SQL STATEMENT!");
            return;
        }
    }


/**************************************************************************************************/
    //添加CHECK约束
    //ALTER TABLE student ADD CHECK (sno>10)
    //ALTER TABLE student ADD CHECK (sno>10 AND sex<5)
    else if(sqlList[3].toLower() == "add" && sqlList[4].toLower() == "check" && sqlList.length() >= 6){

        sqlList[5] = sqlList[5].remove(QChar('('), Qt::CaseInsensitive);//括号清除
        sqlList[5] = sqlList[5].remove(QChar(')'), Qt::CaseInsensitive);//括号清除
        //sqlList[5] = sqlList[5].replace(QRegExp("\\)"), " ");

        if(sqlList[5].contains(">",Qt::CaseSensitive) == true) {
            int i = 0;            
            QStringList a_check = sqlList[5].split(">");
            QVector<field>::iterator iter; //迭代器,检查是否插入同名属性
            for(iter=allFields.begin();iter!=allFields.end();iter++){
               if(iter->get_name() == a_check[0]){
                    allFields[i].set_checkDown(a_check[1]);
                    this->update_field_file(this->thisField.get_tableName());
                    this->ui->textEdit_2->setText("Modification succeeded!");
                    return;
               }
               i++;
            }

            if(sqlList.length() == 8){
                if(sqlList[7].contains(">",Qt::CaseSensitive) == true){
                    int j = 0;
                    QStringList a_check = sqlList[7].split(">");
                    QVector<field>::iterator iter; //迭代器,检查是否插入同名属性
                    for(iter=allFields.begin();iter!=allFields.end();iter++){
                       if(iter->get_name() == a_check[0]){
                            allFields[j].set_checkDown(a_check[1]);
                            this->update_field_file(this->thisField.get_tableName());
                            this->ui->textEdit_2->setText("Modification succeeded!");
                            return;
                       }
                       j++;
                    }

                }
                else if(sqlList[7].contains("<",Qt::CaseSensitive) == true){
                    int j = 0;
                    QStringList a_check = sqlList[7].split(">");
                    QVector<field>::iterator iter; //迭代器,检查是否插入同名属性
                    for(iter=allFields.begin();iter!=allFields.end();iter++){
                       if(iter->get_name() == a_check[0]){
                            allFields[j].set_checkUP(a_check[1]);
                            this->update_field_file(this->thisField.get_tableName());
                            this->ui->textEdit_2->setText("Modification succeeded!");
                            return;
                       }
                       j++;
                    }
                }
                else{
                    this->ui->textEdit_2->setText("WRONG SQL STATEMENT OR CAN NOT FIND IT!");
                    return;
                }
            }
            this->ui->textEdit_2->setText("WRONG SQL STATEMENT OR CAN NOT FIND IT!");
            return;
        }
        else if(sqlList[5].contains("<",Qt::CaseSensitive) == true){
            int i = 0;
            QStringList a_check = sqlList[5].split("<");
            QVector<field>::iterator iter; //迭代器,检查是否插入同名属性
            for(iter=allFields.begin();iter!=allFields.end();iter++){
               if(iter->get_name() == a_check[0]){
                    allFields[i].set_checkUP(a_check[1]);
                    this->update_field_file(this->thisField.get_tableName());
                    this->ui->textEdit_2->setText("Modification succeeded!");
                    return;
               }
               i++;     
            }
            if(sqlList.length() == 8){
                if(sqlList[7].contains(">",Qt::CaseSensitive) == true){
                    int j = 0;
                    QStringList a_check = sqlList[7].split(">");
                    QVector<field>::iterator iter; //迭代器,检查是否插入同名属性
                    for(iter=allFields.begin();iter!=allFields.end();iter++){
                       if(iter->get_name() == a_check[0]){
                            allFields[j].set_checkDown(a_check[1]);
                            this->update_field_file(this->thisField.get_tableName());
                            this->ui->textEdit_2->setText("Modification succeeded!");
                            return;
                       }
                       j++;
                    }

                }
                else if(sqlList[7].contains("<",Qt::CaseSensitive) == true){
                    int j = 0;
                    QStringList a_check = sqlList[7].split(">");
                    QVector<field>::iterator iter; //迭代器,检查是否插入同名属性
                    for(iter=allFields.begin();iter!=allFields.end();iter++){
                       if(iter->get_name() == a_check[0]){
                            allFields[j].set_checkUP(a_check[1]);
                            this->update_field_file(this->thisField.get_tableName());
                            this->ui->textEdit_2->setText("Modification succeeded!");
                            return;
                       }
                       j++;
                    }
                }
                else{
                    this->ui->textEdit_2->setText("WRONG SQL STATEMENT OR CAN NOT FIND IT!");
                    return;
                }

            this->ui->textEdit_2->setText("WRONG SQL STATEMENT OR CAN NOT FIND IT!");
            return;
            }
        }
        else{
            this->ui->textEdit_2->setText("WRONG SQL STATEMENT OR CAN NOT FIND IT!");
            return;
        }

    }


/**************************************************************************************************/

    else{
        this->ui->textEdit_2->setText("WRONG SQL STATEMENT!");
        return;
    }

}

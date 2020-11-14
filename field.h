#ifndef FIELD_H
#define FIELD_H
#include<QString>

class field
{
public:
    field();
    void set_tableName(QString tableName);
    void set_name(QString name);
    void set_dataType(QString dataType);
    void set_unique(QString unique);
    void set_PK(QString PK);
    void set_notNull(QString notNull);
    void set_checkUP(QString checkUP);
    void set_checkDown(QString checkDown);
    void set_FK_tableName(QString FK_tableName);
    void set_deleteLimit(QString deleteLimit);

    QString get_tableName();
    QString get_name();
    QString get_dataType();
    QString get_unique();
    QString get_PK();
    QString get_notNull();
    QString get_checkUP();
    QString get_checkDown();
    QString get_FK_tableName();
    QString get_deleteLimit();

private:
    QString tableName;//所属表
    QString name;//名称
    QString dataType;//数据类型

    QString PK = "FALSE";//主键
    QString unique = "FALSE";//唯一
    QString notNull = "FALSE";//非空

    QString checkUP = "FALSE";//check上限
    QString checkDown = "FALSE";//check下限

    QString FK_tableName = "FALSE";//外键引用表名
    QString deleteLimit = "RESTRICT";//删除约束
};

#endif // FIELD_H

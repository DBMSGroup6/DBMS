#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <string>
#include <sstream>
#include <iomanip>

#include <direct.h>
#include <io.h>

#include <fstream>

using namespace std;

const int inf = 0x3f3f3f3f;

struct Tables {
	string name;
	string pathName;
	vector<string>colName;//列名称
	vector<string>type;
	vector<int>size;
	FILE* fp;
};

class myDBMS {
	vector<Tables*>tab;
	bool open;
public:
	string cmd;
	string prePath;//数据库的文件路径

	myDBMS() {
		cmd = "";
		prePath = "";
		open = false;
		//建库删库
		cout << "请按以下规则输入命令语句(命令不分大小写)" << endl;
		cout << "新建数据库: create database 数据库名字" << endl;
		cout << "删除数据库: drop database 数据库名字" << endl;
		cout << "打开数据库: open database 数据库名字" << endl;
		cout << "关闭数据库: close database 数据库名字" << endl;
		cout << "退出程序  : exit" << endl;
	}
	~myDBMS() {
		for (int i = 0; i < tab.size(); i++) {
			if (tab[i]->fp != NULL)
				fclose(tab[i]->fp);
			delete tab[i];
		}
		tab.resize(0);
		cmd = "";
		prePath = "";
	}

	void transfer();//转为小写
	void openDataBase(string);//打开数据库
	void closeDataBase();//关闭数据库
	void myCreateDataBase(string); //建立数据库	
	void myDropDataBase(string); //删除数据库	


	int posIsNos(string);//辅助函数
};

void myDBMS::transfer() {
	for (int i = 0; i < cmd.size(); i++) 
		cmd[i] = tolower(cmd[i]);
}

void myDBMS::openDataBase(string dataBaseName) {
	if (open) {
		cout << "请先关闭当前打开的数据库" << endl;
		return;
	}
	string pathName = "D:\\test\\" + dataBaseName;
	if (0 != access(pathName.c_str(), 0))printf("该数据库不存在");
	else {
		prePath = pathName + "\\";
		cout << "打开数据库成功" << endl;
		open = true;
	}
}

void myDBMS::closeDataBase() {//和析构函数相同
	for (int i = 0; i < tab.size(); i++) {
		if (tab[i]->fp != NULL)
			fclose(tab[i]->fp);
		delete tab[i];
	}
	tab.resize(0);
	cmd = "";
	prePath = "";
	open = false;
}

//D:\\test
void myDBMS::myCreateDataBase(string dataBaseName) {//建立数据库
	string pathName = "D:\\test\\" + dataBaseName;
	if (0 != access(pathName.c_str(), 0)) {
		if (0 == mkdir(pathName.c_str()))//返回0表示创建成功,-1表示失败
			cout << "创建成功" << endl;
		else
			cout << "创建失败" << endl;
		return;
	}
	cout << "该数据库已存在" << endl;
}

void myDBMS::myDropDataBase(string dataBaseName) {//删除数据库
	string pathName = "D:\\test\\" + dataBaseName;
	if (0 == access(pathName.c_str(), 0)) {
		pathName = "rd " + pathName;
		if (0 == system(pathName.c_str()))
			cout << "删除数据库" << dataBaseName << "成功" << endl;
		else
			cout << "删除数据库" << dataBaseName << "失败" << endl;
		return;
	}
	cout << "数据库" << dataBaseName << "不存在" << endl;
}

int main(void) {
	myDBMS db;
	while (cin >> db.cmd) {
		db.transfer();
		//cout << "db.cmd = " << db.cmd << endl;
		if (db.cmd == "exit")break;
		if (db.cmd == "create") {
			string name;
			cin >> db.cmd >> name;
			db.transfer();
			//cout << "db.cmd:" << db.cmd << " name:" << name << endl;
			if (db.cmd == "database")
				db.myCreateDataBase(name);
			else cout << "命令语句有误!" << endl;
		}
		else if (db.cmd == "drop") {
			string name;
			cin >> db.cmd >> name;
			db.transfer();
			if (db.cmd == "database")
				db.myDropDataBase(name);
			else cout << "命令语句有误!" << endl;
		}
		else if (db.cmd == "open") {
			string name;
			cin >> db.cmd >> name;
			db.openDataBase(name);
		}
		else if (db.cmd == "close") {
			string name;
			cin >> db.cmd >> name;
			db.transfer();
			if (db.cmd == "database")
				db.closeDataBase();
			else cout << "命令语句有误!" << endl;
		}
		else {
			string tmp;
			getline(cin, tmp);
			cout << "输入命令错误,请检查!" << endl;
		}
	}
	return 0;
}

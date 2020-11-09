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
	vector<string>colName;//������
	vector<string>type;
	vector<int>size;
	FILE* fp;
};

class myDBMS {
	vector<Tables*>tab;
	bool open;
public:
	string cmd;
	string prePath;//���ݿ���ļ�·��

	myDBMS() {
		cmd = "";
		prePath = "";
		open = false;
		//����ɾ��
		cout << "�밴���¹��������������(����ִ�Сд)" << endl;
		cout << "�½����ݿ�: create database ���ݿ�����" << endl;
		cout << "ɾ�����ݿ�: drop database ���ݿ�����" << endl;
		cout << "�����ݿ�: open database ���ݿ�����" << endl;
		cout << "�ر����ݿ�: close database ���ݿ�����" << endl;
		cout << "�˳�����  : exit" << endl;
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

	void transfer();//תΪСд
	void openDataBase(string);//�����ݿ�
	void closeDataBase();//�ر����ݿ�
	void myCreateDataBase(string); //�������ݿ�	
	void myDropDataBase(string); //ɾ�����ݿ�	


	int posIsNos(string);//��������
};

void myDBMS::transfer() {
	for (int i = 0; i < cmd.size(); i++) 
		cmd[i] = tolower(cmd[i]);
}

void myDBMS::openDataBase(string dataBaseName) {
	if (open) {
		cout << "���ȹرյ�ǰ�򿪵����ݿ�" << endl;
		return;
	}
	string pathName = "D:\\test\\" + dataBaseName;
	if (0 != access(pathName.c_str(), 0))printf("�����ݿⲻ����");
	else {
		prePath = pathName + "\\";
		cout << "�����ݿ�ɹ�" << endl;
		open = true;
	}
}

void myDBMS::closeDataBase() {//������������ͬ
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
void myDBMS::myCreateDataBase(string dataBaseName) {//�������ݿ�
	string pathName = "D:\\test\\" + dataBaseName;
	if (0 != access(pathName.c_str(), 0)) {
		if (0 == mkdir(pathName.c_str()))//����0��ʾ�����ɹ�,-1��ʾʧ��
			cout << "�����ɹ�" << endl;
		else
			cout << "����ʧ��" << endl;
		return;
	}
	cout << "�����ݿ��Ѵ���" << endl;
}

void myDBMS::myDropDataBase(string dataBaseName) {//ɾ�����ݿ�
	string pathName = "D:\\test\\" + dataBaseName;
	if (0 == access(pathName.c_str(), 0)) {
		pathName = "rd " + pathName;
		if (0 == system(pathName.c_str()))
			cout << "ɾ�����ݿ�" << dataBaseName << "�ɹ�" << endl;
		else
			cout << "ɾ�����ݿ�" << dataBaseName << "ʧ��" << endl;
		return;
	}
	cout << "���ݿ�" << dataBaseName << "������" << endl;
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
			else cout << "�����������!" << endl;
		}
		else if (db.cmd == "drop") {
			string name;
			cin >> db.cmd >> name;
			db.transfer();
			if (db.cmd == "database")
				db.myDropDataBase(name);
			else cout << "�����������!" << endl;
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
			else cout << "�����������!" << endl;
		}
		else {
			string tmp;
			getline(cin, tmp);
			cout << "�����������,����!" << endl;
		}
	}
	return 0;
}


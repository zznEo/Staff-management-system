#include "workerManager.h"

WorkerManager::WorkerManager() {

	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	if (!ifs.is_open()) {
		//cout << "文件不存在!" << endl;
		this->m_EmpNum = 0;
		this->m_EmpArry = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		//cout << "文件为空！" << endl;
		this->m_EmpNum = 0;
		this->m_EmpArry = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	int num = this->get_EmpNum();
	//cout << "当前文件中有" << num << endl;
	this->m_EmpNum = num;

	this->m_EmpArry = new Worker* [this->m_EmpNum];
	this->init_Emp();
	/*for (int i = 0; i < this->m_EmpNum; i++) {
		cout << "职工号： " << this->m_EmpArry[i]->m_Id
			<< " 职工姓名： " << this->m_EmpArry[i]->m_Name
			<< " 部门编号： " << this->m_EmpArry[i]->m_DeptId << endl;
	}*/
}

void WorkerManager::Add_Emp() {
	cout << "请输入添加职工数量：";
	int addNum = 0;
	cin >> addNum;
	if (addNum > 0) {
		int newSize = this->m_EmpNum + addNum;

		Worker **newSpace = new Worker* [newSize];

		if (this->m_EmpNum != 0) {
			for (int i = 0; i < this->m_EmpNum; i++) {
				newSpace[i] = this->m_EmpArry[i];
			}
		}

		for (int i = 0; i < addNum; i++) {
			int id, did;
			string name;
			cout << "请输入第 " << i + 1 << " 个新职工编号：" << endl;
			cin >> id;

			cout << "请输入第 " << i + 1 << " 个新职工姓名：" << endl;
			cin >> name;

			cout << "请选择该职工的岗位：" << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
			cin >> did;

			Worker* wk = NULL;
			switch (did)
			{
			case 1:
				wk = new Employee(id, name, did);
				break;
			case 2:
				wk = new Manager(id, name, did);
				break;
			case 3:
				wk = new Boss(id, name, did);
				break;
			default:
				break;
			}
			newSpace[this->m_EmpNum + i] = wk;
		}

		delete[] this->m_EmpArry;
		this->m_EmpArry = newSpace;
		this->m_EmpNum = newSize;

		cout << "成功添加了" << addNum << "名员工" << endl;

		this->save();

		this->m_FileIsEmpty = false;
	}
	else {
		cout << "输入数据有误！" << endl;
	}
	system("pause");
	system("cls");
}

void WorkerManager::save() {
	ofstream ofs;
	ofs.open(FILENAME, ios::out);

	for (int i = 0; i < this->m_EmpNum; i++) {
		ofs << this->m_EmpArry[i]->m_Id << " "
			<< this->m_EmpArry[i]->m_Name << " "
			<< this->m_EmpArry[i]->m_DeptId << endl;
	}
	ofs.close();
}

int WorkerManager::get_EmpNum() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id, did, num = 0;
	string name;

	while (ifs >> id && ifs >> name && ifs >> did) {
		num++;
	}
	return num;
}

void WorkerManager :: init_Emp() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	
	int id, did, index = 0;
	string name;

	while (ifs >> id && ifs >> name && ifs >> did) {
		Worker* wk = NULL;
		switch (did)
		{
		case 1:
			wk = new Employee(id, name, did);
			break;
		case 2:
			wk = new Manager(id, name, did);
			break;
		case 3:
			wk = new Boss(id, name, did);
			break;
		default:
			break;
		}
		this->m_EmpArry[index++] = wk;
	}

	ifs.close();
}

void WorkerManager::ShowEmp() {
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或记录为空！" << endl;
	}
	else {
		for (int i = 0; i < m_EmpNum; i++) {
			this->m_EmpArry[i]->showInfo();
		}
	}
	system("pause");
	system("cls");
}

void WorkerManager::Del_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或文件为空" << endl;
	}
	else {
		int id;
		cout << "请输入要删除的职工编号：";
		cin >> id;
		int index = this->isExist(id);
		if (index != -1) {
			for (int i = index; i < m_EmpNum; i++) {
				this->m_EmpArry[i] = this->m_EmpArry[i + 1];
			}
			this->m_EmpNum--;
			this->save();
			cout << "删除成功！" << endl;
		}
		else {
			cout << "删除失败，未找到该员工！" << endl;
		}
	}
	system("pause");
	system("cls");
}

int WorkerManager::isExist(int id) {
	int index = -1;
	for (int i = 0; i < this->m_EmpNum; i++) {
		if (this->m_EmpArry[i]->m_Id == id) {
			index = i;
			break;
		}
	}
	return index;
}

void WorkerManager::Mod_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或文件为空" << endl;
	}
	else {
		cout << "请输入修改职工的编号：";
		int id;
		cin >> id;
		int index = this->isExist(id);
		if (index != -1) {
			delete this->m_EmpArry[index];

			int newid = 0, newdid = 0;
			string newname;

			cout << "查到： " << id << "号职工，请输入新职工号： " << endl;
			cin >> newid;

			cout << "请输入新姓名： " << endl;
			cin >> newname;

			cout << "请输入岗位： " << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
			cin >> newdid;

			Worker* wk = NULL;
			switch (newdid)
			{
			case 1:
				wk = new Employee(newid, newname, newdid);
				break;
			case 2:
				wk = new Manager(newid, newname, newdid);
				break;
			case 3:
				wk = new Boss(newid, newname, newdid);
				break;
			default:
				break;
			}
			this->m_EmpArry[index] = wk;
			this->save();
			cout << "修改成功！" << endl;
		}
		else {
			cout << "修改失败，查无从人！" << endl;
		}
	}
	system("pause");
	system("cls");
}

void WorkerManager::Find_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或文件为空" << endl;
	}
	else {
		cout << "请输入查找的方式：" << endl;
		cout << "1、按职工编号查找" << endl;
		cout << "2、按姓名查找" << endl;

		int select = 0, index = 0;
		cin >> select;
		if (select == 1) {
			int id;
			cout << "请输入查找的职工编号：" << endl;
			cin >> id;

			index = this->isExist(id);
			if (index != -1) {
				cout << "查找成功！该职工信息如下：" << endl;
				this->m_EmpArry[index]->showInfo();
			}
			else {
				cout << "查找失败，查无此人" << endl;
			}
		}
		else if (select == 2) {
			string name;
			cout << "请输入查找的姓名：" << endl;
			cin >> name;

			bool flag = false;
			for (int i = 0; i < m_EmpNum; i++){
				if (m_EmpArry[i]->m_Name == name){
					cout << "查找成功,职工编号为："
						<< m_EmpArry[i]->m_Id
						<< " 号的信息如下：" << endl;

					flag = true;

					this->m_EmpArry[i]->showInfo();
				}
			}
			if (flag == false){
				cout << "查找失败，查无此人" << endl;
			}
		}
		else {
			cout << "输入选项有误" << endl;
		}
	}
	system("pause");
	system("cls");
}

void WorkerManager::Sort_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或文件为空" << endl;
	}
	else {
		cout << "请选择排序方式： " << endl;
		cout << "1、按职工号进行升序" << endl;
		cout << "2、按职工号进行降序" << endl;

		int select = 0;
		cin >> select;

		for (int i = 0; i < m_EmpNum; i++){
			int minOrMax = i;
			for (int j = i + 1; j < m_EmpNum; j++){
				if (select == 1){
					if (m_EmpArry[minOrMax]->m_Id > m_EmpArry[j]->m_Id)
						minOrMax = j;
				}
				else {
					if (m_EmpArry[minOrMax]->m_Id < m_EmpArry[j]->m_Id)
						minOrMax = j;
				}
			}

			if (i != minOrMax)
				swap(m_EmpArry[i], m_EmpArry[minOrMax]);
		}
		this->save();
		cout << "排序后结果如下：" << endl;
		this->ShowEmp();
	}
	system("pause");
	system("cls");
}

void WorkerManager::Clean_File() {
	cout << "确认清空？" << endl;
	cout << "1、确认" << endl;
	cout << "2、返回" << endl;

	int select = 0;
	cin >> select;

	if (select == 1) {
		ofstream ofs(FILENAME, ios::trunc);
		ofs.close();
		this->m_FileIsEmpty = true;

		if (this->m_EmpNum != NULL) {
			for (int i = 0; i < this->m_EmpNum; i++) {
				delete this->m_EmpArry[i];
				this->m_EmpArry[i] = NULL;
			}
			delete[] this->m_EmpArry;
			this->m_EmpArry = NULL;
			this->m_EmpNum = 0;
		}
		cout << "清空成功！" << endl;
	}
	system("pause");
	system("cls");
}

void WorkerManager::Show_Menu() {
	cout << "********************************************" << endl;
	cout << "*********  欢迎使用职工管理系统！ **********" << endl;
	cout << "*************  0.退出管理程序  *************" << endl;
	cout << "*************  1.增加职工信息  *************" << endl;
	cout << "*************  2.显示职工信息  *************" << endl;
	cout << "*************  3.删除离职职工  *************" << endl;
	cout << "*************  4.修改职工信息  *************" << endl;
	cout << "*************  5.查找职工信息  *************" << endl;
	cout << "*************  6.按照编号排序  *************" << endl;
	cout << "*************  7.清空所有文档  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

void WorkerManager::exitSystem() {
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}

void WorkerManager::choiceError() {
	cout << "您输入的选择有误请，重新输出" << endl;
}

WorkerManager::~WorkerManager() {

}


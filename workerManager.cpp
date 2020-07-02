#include "workerManager.h"

WorkerManager::WorkerManager() {

	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	if (!ifs.is_open()) {
		//cout << "�ļ�������!" << endl;
		this->m_EmpNum = 0;
		this->m_EmpArry = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		//cout << "�ļ�Ϊ�գ�" << endl;
		this->m_EmpNum = 0;
		this->m_EmpArry = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	int num = this->get_EmpNum();
	//cout << "��ǰ�ļ�����" << num << endl;
	this->m_EmpNum = num;

	this->m_EmpArry = new Worker* [this->m_EmpNum];
	this->init_Emp();
	/*for (int i = 0; i < this->m_EmpNum; i++) {
		cout << "ְ���ţ� " << this->m_EmpArry[i]->m_Id
			<< " ְ�������� " << this->m_EmpArry[i]->m_Name
			<< " ���ű�ţ� " << this->m_EmpArry[i]->m_DeptId << endl;
	}*/
}

void WorkerManager::Add_Emp() {
	cout << "���������ְ��������";
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
			cout << "������� " << i + 1 << " ����ְ����ţ�" << endl;
			cin >> id;

			cout << "������� " << i + 1 << " ����ְ��������" << endl;
			cin >> name;

			cout << "��ѡ���ְ���ĸ�λ��" << endl;
			cout << "1����ְͨ��" << endl;
			cout << "2������" << endl;
			cout << "3���ϰ�" << endl;
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

		cout << "�ɹ������" << addNum << "��Ա��" << endl;

		this->save();

		this->m_FileIsEmpty = false;
	}
	else {
		cout << "������������" << endl;
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
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
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
		cout << "�ļ������ڻ��ļ�Ϊ��" << endl;
	}
	else {
		int id;
		cout << "������Ҫɾ����ְ����ţ�";
		cin >> id;
		int index = this->isExist(id);
		if (index != -1) {
			for (int i = index; i < m_EmpNum; i++) {
				this->m_EmpArry[i] = this->m_EmpArry[i + 1];
			}
			this->m_EmpNum--;
			this->save();
			cout << "ɾ���ɹ���" << endl;
		}
		else {
			cout << "ɾ��ʧ�ܣ�δ�ҵ���Ա����" << endl;
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
		cout << "�ļ������ڻ��ļ�Ϊ��" << endl;
	}
	else {
		cout << "�������޸�ְ���ı�ţ�";
		int id;
		cin >> id;
		int index = this->isExist(id);
		if (index != -1) {
			delete this->m_EmpArry[index];

			int newid = 0, newdid = 0;
			string newname;

			cout << "�鵽�� " << id << "��ְ������������ְ���ţ� " << endl;
			cin >> newid;

			cout << "�������������� " << endl;
			cin >> newname;

			cout << "�������λ�� " << endl;
			cout << "1����ְͨ��" << endl;
			cout << "2������" << endl;
			cout << "3���ϰ�" << endl;
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
			cout << "�޸ĳɹ���" << endl;
		}
		else {
			cout << "�޸�ʧ�ܣ����޴��ˣ�" << endl;
		}
	}
	system("pause");
	system("cls");
}

void WorkerManager::Find_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "�ļ������ڻ��ļ�Ϊ��" << endl;
	}
	else {
		cout << "��������ҵķ�ʽ��" << endl;
		cout << "1����ְ����Ų���" << endl;
		cout << "2������������" << endl;

		int select = 0, index = 0;
		cin >> select;
		if (select == 1) {
			int id;
			cout << "��������ҵ�ְ����ţ�" << endl;
			cin >> id;

			index = this->isExist(id);
			if (index != -1) {
				cout << "���ҳɹ�����ְ����Ϣ���£�" << endl;
				this->m_EmpArry[index]->showInfo();
			}
			else {
				cout << "����ʧ�ܣ����޴���" << endl;
			}
		}
		else if (select == 2) {
			string name;
			cout << "��������ҵ�������" << endl;
			cin >> name;

			bool flag = false;
			for (int i = 0; i < m_EmpNum; i++){
				if (m_EmpArry[i]->m_Name == name){
					cout << "���ҳɹ�,ְ�����Ϊ��"
						<< m_EmpArry[i]->m_Id
						<< " �ŵ���Ϣ���£�" << endl;

					flag = true;

					this->m_EmpArry[i]->showInfo();
				}
			}
			if (flag == false){
				cout << "����ʧ�ܣ����޴���" << endl;
			}
		}
		else {
			cout << "����ѡ������" << endl;
		}
	}
	system("pause");
	system("cls");
}

void WorkerManager::Sort_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "�ļ������ڻ��ļ�Ϊ��" << endl;
	}
	else {
		cout << "��ѡ������ʽ�� " << endl;
		cout << "1����ְ���Ž�������" << endl;
		cout << "2����ְ���Ž��н���" << endl;

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
		cout << "����������£�" << endl;
		this->ShowEmp();
	}
	system("pause");
	system("cls");
}

void WorkerManager::Clean_File() {
	cout << "ȷ����գ�" << endl;
	cout << "1��ȷ��" << endl;
	cout << "2������" << endl;

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
		cout << "��ճɹ���" << endl;
	}
	system("pause");
	system("cls");
}

void WorkerManager::Show_Menu() {
	cout << "********************************************" << endl;
	cout << "*********  ��ӭʹ��ְ������ϵͳ�� **********" << endl;
	cout << "*************  0.�˳��������  *************" << endl;
	cout << "*************  1.����ְ����Ϣ  *************" << endl;
	cout << "*************  2.��ʾְ����Ϣ  *************" << endl;
	cout << "*************  3.ɾ����ְְ��  *************" << endl;
	cout << "*************  4.�޸�ְ����Ϣ  *************" << endl;
	cout << "*************  5.����ְ����Ϣ  *************" << endl;
	cout << "*************  6.���ձ������  *************" << endl;
	cout << "*************  7.��������ĵ�  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

void WorkerManager::exitSystem() {
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);
}

void WorkerManager::choiceError() {
	cout << "�������ѡ�������룬�������" << endl;
}

WorkerManager::~WorkerManager() {

}


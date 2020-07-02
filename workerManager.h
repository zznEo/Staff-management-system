#pragma once // ��ֹͷ�ļ��ظ�����
#include <iostream>  //�������������ͷ�ļ�
using namespace std; //ʹ�ñ�׼�����ռ�
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"

#include <fstream>
#define FILENAME "empFile.txt"

class WorkerManager {
public:
	WorkerManager();

	void Show_Menu();

	void exitSystem();

	void choiceError();

	void Add_Emp();

	void save();

	int get_EmpNum();

	void init_Emp();

	void ShowEmp();

	void Del_Emp();

	int isExist(int id);

	void Mod_Emp();

	void Find_Emp();

	void Sort_Emp();

	void Clean_File();

	~WorkerManager();

public:
	int m_EmpNum;
	Worker** m_EmpArry;
	bool m_FileIsEmpty;
	
};
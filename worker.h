#pragma once
#include <iostream>
#include <string>
using namespace std;

class Worker {
public:
	virtual void showInfo() = 0;
	virtual string getDeptName() = 0;

public:
	int m_Id = 0;
	string m_Name;
	int m_DeptId = 0;
};
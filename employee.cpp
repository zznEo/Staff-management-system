#include "employee.h"

Employee::Employee(int id, string name, int did) {
	this->m_Id = id;
	this->m_Name = name;
	this->m_DeptId = did;
}

void Employee::showInfo() {
	cout << "ְ����ţ� " << this->m_Id
		<< " \tְ�������� " << this->m_Name
		<< " \t��λ��" << this->getDeptName()
		<< " \t��λְ����ɾ�������������" << endl;
}

string Employee::getDeptName() {
	return string("Ա��");
}
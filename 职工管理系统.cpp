#include <iostream>
#include "workerManager.h"
using namespace std;


int main() {
	WorkerManager wm;
	int choice = 0;
	while (true) {
		wm.Show_Menu();
		cin >> choice;
		switch (choice)
		{
		case 0:  //�˳�ϵͳ
			wm.exitSystem();
			break;
		case 1:  //���ְ��
			wm.Add_Emp();
			break;
		case 2:  //��ʾְ��
			wm.ShowEmp();
			break;
		case 3:  //ɾ��ְ��
			wm.Del_Emp();
			break;
		case 4:  //�޸�ְ��
			wm.Mod_Emp();
			break;
		case 5:  //����ְ��
			wm.Find_Emp();
			break;
		case 6:  //����ְ��
			wm.Sort_Emp();
			break;
		case 7:  //����ĵ�
			wm.Clean_File();
			break;
		default:
			wm.choiceError();
			break;
		}
		system("cls");
	}
	return 0;
}
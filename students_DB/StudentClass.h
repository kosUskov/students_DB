#pragma once
#include <string>
#include "ExamsResultsClass.h"
#include "ClassMenu.h"
#include "ClassEdit.h"
#include "list.hpp"
#include "fileManager.h"

struct StudentNode {
	std::string surName;
	std::string name;
	std::string middleName;
	std::string faculty;
	std::string department;
	std::string group;
	std::string record�ardNumber;
	std::string birthDateString;
	bool sex;
	int startYear;
	ExamsRecords examsRecordsData[9][10];
	int id;
};

class StudentClass {
private:
	StudentNode* sn;
public:
	List <std::string> stringList;
	StudentClass() { sn = new StudentNode(); }
	StudentNode* getStudentNode() { return sn; }
	void UpdateMasString(StudentNode sn) {
		stringList.clear();
		StringBuilderClass sb = StringBuilderClass();
		stringList.push_back(sb.setParam("surName", sn.surName));
		stringList.push_back(sb.setParam("name", sn.name));
		stringList.push_back(sb.setParam("middleName", sn.middleName));
		stringList.push_back(sb.setParam("faculty", sn.faculty));
		stringList.push_back(sb.setParam("department", sn.department));
		stringList.push_back(sb.setParam("group", sn.group));
		stringList.push_back(sb.setParam("record�ardNumber", sn.record�ardNumber));
		int intSex = 1;
		if (sn.sex) { intSex = 1; }
		else { intSex = 0; }
		stringList.push_back(sb.setParam("sex", intSex));
		stringList.push_back(sb.setParam("startYear", sn.startYear));
		stringList.push_back(sb.setParam("birthDateString", sn.birthDateString));
		int sem = 0;
		int num = 0;
		for (int sem = 0; sem < 9; sem++)
			for (int num = 0; num < 10; num++)
				if (not sn.examsRecordsData[sem][num].isEmpty) {
					stringList.push_back(sb.setParam("examsResults_" + std::to_string(sem) + "_" + std::to_string(num) + "_n", sn.examsRecordsData[sem][num].name));
					stringList.push_back(sb.setParam("examsResults_" + std::to_string(sem) + "_" + std::to_string(num) + "_m", std::to_string(sn.examsRecordsData[sem][num].mark)));
				}
	}
	bool editSex(int col[]) {
		ClassMenu* sexMenu = new ClassMenu();
		int resultSelectedItem = 1;
		const int exitItem = 3;
		sexMenu->addTitleItem("�������� ���: ");
		sexMenu->addItem("�������:(");
		sexMenu->addItem("�������:(");
		while (resultSelectedItem != exitItem) {
			sexMenu->run(col);
			resultSelectedItem = sexMenu->getSelectedItem();
			if (resultSelectedItem == 0) {
				return true;
				resultSelectedItem = exitItem;
			}
			else if (resultSelectedItem == 1) {
				return false;
				resultSelectedItem = exitItem;
			}
		}
	}
	void showStudent(StudentNode sn, int col[]) {
		ClassMenu* studDataMenu = new ClassMenu();
		ClassEdit* ce = new  ClassEdit();
		studDataMenu->addItem("�����");
		studDataMenu->addItem("������");
		bool resultStudDataMenu = 1;
		int day, month, year;
		bool putSex;
		if (sn.group == "") { putSex = 1; }
		else { putSex = 0; }
		studDataMenu->addTitleItem("    �������� ������ � ��������:");
		studDataMenu->addTitleItem("�������: " + sn.surName);
		studDataMenu->addTitleItem("���: " + sn.name);
		studDataMenu->addTitleItem("��������: " + sn.middleName);
		std::string sexString = "";
		if (sn.sex) { sexString = "�������:("; }
		else { sexString = "�������;)"; }
		studDataMenu->addTitleItem("���: " + sexString);
		studDataMenu->addTitleItem("���� ��������: " + sn.birthDateString);
		studDataMenu->addTitleItem("��� �����������: " + std::to_string(sn.startYear));
		studDataMenu->addTitleItem("����� �������� ������: " + sn.record�ardNumber);
		studDataMenu->addTitleItem("������: " + sn.group);
		studDataMenu->addTitleItem("��������: " + sn.faculty);
		studDataMenu->addTitleItem("�������: " + sn.department);
		while (resultStudDataMenu != 0) {
			studDataMenu->run(col);
			resultStudDataMenu = studDataMenu->getSelectedItem();
			if (resultStudDataMenu) { showExamsResults(sn, col); }
		}
		delete ce;
		delete studDataMenu;
	}
	void editStudent(StudentNode* sn, int col[]) {
		ClassMenu* studDataMenu = new ClassMenu();
		int resultStudDataMenu = 1;
		int exitStudDataMenu = -1;
		ClassEdit* ce = new  ClassEdit();
		studDataMenu->addItem("�����");
		studDataMenu->addItem("��������/�������� �������");
		studDataMenu->addItem("��������/�������� ���");
		studDataMenu->addItem("��������/�������� ��������");
		studDataMenu->addItem("��������/�������� ��������");
		studDataMenu->addItem("��������/�������� �������");
		studDataMenu->addItem("��������/�������� ������");
		studDataMenu->addItem("��������/�������� ����� �������� ������");
		studDataMenu->addItem("��������/�������� ���");
		studDataMenu->addItem("��������/�������� ��� ����������� � ���");
		studDataMenu->addItem("��������/�������� ���� ��������");
		studDataMenu->addItem("��������/�������� ������");
		int day, month, year;
		bool putSex;
		if (sn->group == "") { putSex = 1; }
		else { putSex = 0; }
		while (resultStudDataMenu != exitStudDataMenu) {
			studDataMenu->eraseTitle();
			studDataMenu->addTitleItem("���������/���������� ������ � ��������:");
			studDataMenu->addTitleItem("�������: " + sn->surName + " ���: " + sn->name + " ��������: " + sn->middleName);
			std::string sexString = "";
			if (sn->sex) { sexString = "�������:("; }
			else { sexString = "�������;)"; }
			if (sn->startYear == 0) {
				studDataMenu->addTitleItem("���: " + sexString + " ���� ��������: " + sn->birthDateString + " ��� �����������: ");
			}
			else {
				studDataMenu->addTitleItem("���: " + sexString + " ���� ��������: " + sn->birthDateString + " ��� �����������: " + std::to_string(sn->startYear));
			}
			studDataMenu->addTitleItem("����� �������� ������: " + sn->record�ardNumber + " ������: " + sn->group);
			studDataMenu->addTitleItem("��������: " + sn->faculty);
			studDataMenu->addTitleItem("�������: " + sn->department);
			studDataMenu->run(col);
			resultStudDataMenu = studDataMenu->getSelectedItem();
			std::string tmpString = "";
			int year = 0;
			int startYear = 0;
			StringBuilderClass* sb = new StringBuilderClass();
			ExamsRecords oldExamsRecordsData[9][10];
			if (resultStudDataMenu == 0) {
				if (sn->record�ardNumber == "") {
					system("cls");
					std::cout << "������� ����� �������� ������";
					_getch();
				}
				else if (sn->group == "") {
					system("cls");
					std::cout << "������� ������ ��������";
					_getch();
				}
				else if (putSex) {
					system("cls");
					std::cout << "������� ��� ��������";
					_getch();
				}
				else if (sn->startYear == 0) {
					system("cls");
					std::cout << "������� ��� ����������� � ���";
					_getch();
				}
				else { exitStudDataMenu = 0; }
			}
			else if (resultStudDataMenu == 1) {
				ce->setLabel("������� �������. ");
				sn->surName = ce->setDataString(sn->surName);
			}
			else if (resultStudDataMenu == 2) {
				ce->setLabel("������� ���. ");
				sn->name = ce->setDataString(sn->name);
			}
			else if (resultStudDataMenu == 3) {
				ce->setLabel("������� ��������. ");
				sn->middleName = ce->setDataString(sn->middleName);
			}
			else if (resultStudDataMenu == 4) {
				ce->setLabel("������� �������� ���������. ");
				sn->faculty = ce->setDataString(sn->faculty);
			}
			else if (resultStudDataMenu == 5) {
				ce->setLabel("������� �������� �������. ");
				sn->department = ce->setDataString(sn->department);
			}
			else if (resultStudDataMenu == 6) {
				ce->setLabel("������� ������. ");
				sn->group = ce->setDataString(sn->group);
			}
			else if (resultStudDataMenu == 7) {
				ce->setLabel("������� ����� �������� ������. ");
				sn->record�ardNumber = ce->setDataString(sn->record�ardNumber);
			}
			else if (resultStudDataMenu == 8) {
				ce->setLabel("������� ���. ");
				sn->sex = editSex(col);
				putSex = 0;
			}
			else if (resultStudDataMenu == 9) {
				ce->setLabel("������� ��� ����������� � ���. ");
				startYear = ce->setDataInt(1900, 2021);
				tmpString = sb->split(sn->birthDateString.c_str(), '.', 3);
				year = atoi(tmpString.c_str());
				if (year == 0) { sn->startYear = startYear; }
				else {
					if (startYear - year >= 15) { sn->startYear = startYear; }
					else {
						std::cout << "������ ��� ����������� � �������� ������ ���� �� 15 ��� ������ ��� ��� ��������";
						_getch();
					}
				}
			}
			else if (resultStudDataMenu == 10) {
				ce->setLabel("������� ��� ��������. ");
				year = ce->setDataInt(1900, 2005);
				if (year == -1) { continue; }
				ce->setLabel("������� ����� ��������. ");
				month = ce->setDataInt(1, 12);
				if (month == -1) { continue; }
				ce->setLabel("������� ���� ��������. ");
				day = ce->setDataInt(year, month, 1);
				if (day == -1) { continue; }
				if (sn->startYear == 0)
					sn->birthDateString = std::to_string(day) + "." + std::to_string(month) + "." + std::to_string(year);
				else
				{
					if (sn->startYear - year >= 15) {
						sn->birthDateString = std::to_string(day) + "." + std::to_string(month) + "." + std::to_string(year);
					}
					else
					{
						std::cout << "������ ��� ����������� � �������� ������ ���� �� 15 ��� ������ ��� ��� ��������";
						_getch();
					}
				}
			}
			else if (resultStudDataMenu == 11) {
				ce->setLabel("�����������/ �������� ������.");
				for (int i = 0; i < 9; i++)
					for (int j = 0; j < 10; j++) {
						oldExamsRecordsData[i][j].name = sn->examsRecordsData[i][j].name;
						oldExamsRecordsData[i][j].isEmpty = sn->examsRecordsData[i][j].isEmpty;
						oldExamsRecordsData[i][j].mark = sn->examsRecordsData[i][j].mark;
					}

				editExamsResults(sn, col);
				if (isSameNameExamsResults(*sn)) {
					system("cls");
					std::cout << "������: ���� ���������� �������� ���������";
					std::cout << std::endl << "������ �������� �����������";
					for (int i = 0; i < 9; i++)
						for (int j = 0; j < 10; j++) {
							sn->examsRecordsData[i][j].name = oldExamsRecordsData[i][j].name;
							sn->examsRecordsData[i][j].isEmpty = oldExamsRecordsData[i][j].isEmpty;
							sn->examsRecordsData[i][j].mark = oldExamsRecordsData[i][j].mark;
						}
					_getch();
				}
			}
			delete sb;
		}
		delete studDataMenu;
		delete ce;
	}
	void editExamsResults(StudentNode* sn, int col[]) {
		ClassMenu* sesMenu = new ClassMenu();
		int result = 1;
		const int exit = 0;
		ClassMenu* msMenu = new ClassMenu();
		int resultS = 1;
		const int exitS = 0;
		ClassEdit* ce = new  ClassEdit();
		ExamsResultsClass* erc = new ExamsResultsClass();
		sesMenu->addItem("�����");
		for (int i = 1; i < 10; i++) {
			sesMenu->addItem("������ " + std::to_string(i));
		}
		while (result != exit) {
			sesMenu->eraseTitle();
			sesMenu->addTitleItem("��������/���������/���������� ������ � ������� �� ��� ������");
			sesMenu->addTitleItem("�������� ������ ��� ��������� � �������������� ���������� �� �������");
			sesMenu->run(col);
			result = sesMenu->getSelectedItem();
			if (result == exit) { result = exit; break; }
			int curSess = result;
			if ((curSess >= 1) and (curSess <= 10)) {
				msMenu->eraseAll();
				msMenu->addTitleItem("��������/���������/���������� ������ � �������");
				msMenu->addTitleItem("������ ������ �" + std::to_string(curSess));
				resultS = 1;
				while (resultS != exitS) {
					msMenu->eraseItem();
					msMenu->addItem("�����");
					msMenu->addItem("�������� ������");
					msMenu->addItem("������� ������");
					for (int i = 0; i < 10; i++)
						if (not sn->examsRecordsData[curSess - 1][i].isEmpty) {
							std::string markString = "";
							int markInt = sn->examsRecordsData[curSess - 1][i].mark;
							if (markInt == 0) markString = "�� �������";
							if (markInt == 1) markString = "�������";
							if ((markInt >= 2) and (markInt <= 5)) {
								markString = std::to_string(markInt);
							}
							msMenu->addItem("�������: " + sn->examsRecordsData[curSess - 1][i].name + " ������: " + markString);
						}
					msMenu->run(col);
					resultS = msMenu->getSelectedItem();
					if (resultS == 0) { resultS == exitS; }
					if (resultS == 1) {
						int itemNum = msMenu->getItemsCount() - 3;
						if (itemNum > 9) {
							system("cls");
							std::cout << "������ � ������ ������ ������ 10 ��������� ��� ������� ��� ���������";
							_getch();
						}
						else {
							addExamsResults(sn, curSess, itemNum, col);
						}
					}
					if (resultS == 2) {
						delExamsResults(sn, curSess, col);
					}
					if (resultS > 2) {
						addExamsResults(sn, curSess, resultS - 3, col);
					}
				}
			}
			result = curSess;
		}
	}
	void showExamsResults(StudentNode sn, int col[]) {
		ClassMenu* sesMenu = new ClassMenu();
		int result = 1;
		ClassMenu* msMenu = new ClassMenu();
		ClassEdit* ce = new  ClassEdit();
		ExamsResultsClass* erc = new ExamsResultsClass();
		sesMenu->addItem("�����");
		for (int i = 1; i < 10; i++) {
			sesMenu->addItem("������ " + std::to_string(i));
		}
		sesMenu->addTitleItem("�������� ������ � ������� �� ��� ������");
		sesMenu->addTitleItem("�������� ������ ��� ��������� � �������������� ���������� �� �������");
		while (1) {
			sesMenu->run(col);
			result = sesMenu->getSelectedItem();
			if (result == 0) { break; }
			else {
				msMenu->eraseAll();
				msMenu->addTitleItem("�������� ������ � �������");
				msMenu->addTitleItem("������ ������ �" + std::to_string(result));
				msMenu->addItem("�����");
				for (int i = 0; i < 10; i++)
					if (not sn.examsRecordsData[result - 1][i].isEmpty) {
						std::string markString = "";
						int markInt = sn.examsRecordsData[result - 1][i].mark;
						if (markInt == 0) markString = "�� �������";
						if (markInt == 1) markString = "�������";
						if ((markInt >= 2) and (markInt <= 5)) {
							markString = std::to_string(markInt);
						}
						msMenu->addTitleItem("�������: " + sn.examsRecordsData[result - 1][i].name + " ������: " + markString);
					}
				bool resultS = 1;
				while (resultS) {
					msMenu->run(col);
					resultS = msMenu->getSelectedItem();
				}
			}
		}
		delete sesMenu;
		delete msMenu;
		delete ce;
	}
	void addExamsResults(StudentNode* sn, int curSess, int curItem, int col[]) {
		ClassEdit* ce = new  ClassEdit();
		ce->setLabel("������� �������� ��������. ");
		sn->examsRecordsData[curSess - 1][curItem].name = ce->setDataString(sn->examsRecordsData[curSess - 1][curItem].name);
		int resultS = 1;
		const int exitS = 0;
		ClassMenu* msMenu = new ClassMenu();
		msMenu->addTitleItem("�������� ������");
		msMenu->addItem("�� �������");
		msMenu->addItem("�������");
		msMenu->addItem("2");
		msMenu->addItem("3");
		msMenu->addItem("4");
		msMenu->addItem("5");
		resultS = 1;
		while (resultS != exitS) {
			msMenu->run(col);
			resultS = msMenu->getSelectedItem();
			sn->examsRecordsData[curSess - 1][curItem].mark = resultS;
			resultS = exitS;
		}
		sn->examsRecordsData[curSess - 1][curItem].isEmpty = false;
		delete msMenu;
		delete ce;
	}
	void delExamsResults(StudentNode* sn, int curSess, int col[]) {
		ClassEdit* ce = new  ClassEdit();
		int resultS = 1;
		const int exitS = 0;
		ClassMenu* msMenu = new ClassMenu();
		msMenu->addTitleItem("�������� ������ ��� ��������");
		resultS = 1;
		while (resultS != exitS) {
			msMenu->eraseItem();
			msMenu->addItem("�����");
			for (int i = 0; i < 10; i++) {
				if (not sn->examsRecordsData[curSess - 1][i].isEmpty) {
					std::string markString = "";
					int markInt = sn->examsRecordsData[curSess - 1][i].mark;
					if (markInt == 0) markString = "�� �������";
					if (markInt == 1) markString = "�������";
					if ((markInt >= 2) and (markInt <= 5)) {
						markString = std::to_string(markInt);
					}
					msMenu->addItem("�������: " + sn->examsRecordsData[curSess - 1][i].name + " ������: " + markString);
				}
			}
			msMenu->run(col);
			resultS = msMenu->getSelectedItem();
			if (resultS == exitS) { resultS == exitS; }
			else {
				sn->examsRecordsData[curSess - 1][resultS - 1].isEmpty = true;
				ExamsResultsClass* er = new ExamsResultsClass();
				for (int i = 0; i < 10; i++)
					if (not sn->examsRecordsData[curSess - 1][i].isEmpty)
						er->add(0, sn->examsRecordsData[curSess - 1][i].name, sn->examsRecordsData[curSess - 1][i].mark);
				for (int i = 0; i < 10; i++)
					sn->examsRecordsData[curSess - 1][i].isEmpty = true;
				for (int i = 0; i < 10; i++)
					if (not er->data[0][i].isEmpty) {
						sn->examsRecordsData[curSess - 1][i].isEmpty = false;
						sn->examsRecordsData[curSess - 1][i].name = er->data[0][i].name;
						sn->examsRecordsData[curSess - 1][i].mark = er->data[0][i].mark;
					}
			}
		}
	}
	bool isSameNameExamsResults(StudentNode sn) {
		for (int curSess = 0; curSess < 9; curSess++) {
			for (int i = 0; i < 10; i++)
				for (int j = 0; j < 10; j++)
					if (sn.examsRecordsData[curSess][i].isEmpty == false and sn.examsRecordsData[curSess][j].isEmpty == false and i != j)
						if (strcmp(sn.examsRecordsData[curSess][i].name.c_str(), sn.examsRecordsData[curSess][j].name.c_str()) == 0)
							return true;
		}
		return false;
	}
};
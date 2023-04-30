#pragma once
#include "StudentClass.h"
#include <iostream>
#include <fstream>
#include "fileManager.h"
#include "list.hpp"

class StudentDBClass : public FileManagerClass {
public:
	List <StudentNode> dataBase;
	StudentDBClass() { dataBase.clear(); }
	~StudentDBClass() { dataBase.clear(); }
	void loadDataFromFile() {
		decFile(fileName);
		std::string line;
		int count = 0;
		std::ifstream inFile("forCrypto\\" + fileName);
		if (inFile.is_open()) {
			bool isRecord = false;
			StudentNode* sn = new StudentNode();
			for (int i = 0; i < 9; i++)
				for (int j = 0; j < 10; j++)
					sn->examsRecordsData[i][j].isEmpty = true;
			int studentId = 0;
			while (getline(inFile, line))
			{
				if (strcmp(startRecordString.c_str(), line.c_str()) == 0) {
					isRecord = true;
					continue;
				}
				else if (strcmp(endRecordString.c_str(), line.c_str()) == 0) {
					isRecord = false;
					studentId++;
					dataBase.push_back(*sn);
					for (int i = 0; i < 9; i++)
						for (int j = 0; j < 10; j++)
							sn->examsRecordsData[i][j].isEmpty = true;
					continue;
				}
				if (isRecord) {

					std::string valueName = getName(line);
					if (strcmp(getType(line).c_str(), "str") == 0)
					{
						std::string value = getValueStr(line);
						if (strcmp("surName", valueName.c_str()) == 0)
							sn->surName = value;
						else if (strcmp("name", valueName.c_str()) == 0)
							sn->name = value;
						else if (strcmp("middleName", valueName.c_str()) == 0)
							sn->middleName = value;
						else if (strcmp("faculty", valueName.c_str()) == 0)
							sn->faculty = value;
						else if (strcmp("department", valueName.c_str()) == 0)
							sn->department = value;
						else if (strcmp("group", valueName.c_str()) == 0)
							sn->group = value;
						else if (strcmp("record—ardNumber", valueName.c_str()) == 0)
							sn->record—ardNumber = value;
						else if (strcmp("birthDateString", valueName.c_str()) == 0)
							sn->birthDateString = value;
						else for (int i = 0; i < 9; i++)
							for (int j = 0; j < 10; j++) {
								std::string testNameString = "";
								testNameString = testNameString + "examsResults_" + std::to_string(i) + "_" + std::to_string(j) + "_n";
								std::string testMarkString = "";
								testMarkString = testMarkString + "examsResults_" + std::to_string(i) + "_" + std::to_string(j) + "_m";
								if (strcmp(testNameString.c_str(), valueName.c_str()) == 0) {
									sn->examsRecordsData[i][j].name = value;
									sn->examsRecordsData[i][j].isEmpty = false;
								}
								if (strcmp(testMarkString.c_str(), valueName.c_str()) == 0) {
									sn->examsRecordsData[i][j].mark = atoi(value.c_str());
									sn->examsRecordsData[i][j].isEmpty = false;
								}
							}
					}
					else {
						int value = getValueInt(line);
						if (strcmp("id", valueName.c_str()) == 0)
							sn->id = studentId;
						if (strcmp("startYear", valueName.c_str()) == 0)
							sn->startYear = value;
						if (strcmp("sex", valueName.c_str()) == 0)
							if (value == 0) sn->sex = false;
							else sn->sex = true;
					}
				}
			}
			inFile.close();
			delete sn;
			encFile(fileName);
		}
		else {
			std::cout << " \n ‘‡ÈÎ ¡ƒ ÌÂ Ì‡È‰ÂÌ \n";
			_getch();
		}
		inFile.close();
	}
	void saveDataToFile() {
		std::ofstream outFile;
		std::string tmpFile = fileName + ".enc";
		remove(tmpFile.c_str());
		outFile.open("forCrypto\\" + fileName, std::ios::app);
		if (outFile.is_open()) {
			StudentClass st = StudentClass();
			int recordsCount = getRecordCount();
			StudentNode* sn;
			for (int i = 0; i < recordsCount; i++) {
				outFile << startRecordString << std::endl;
				sn = &dataBase.at(i);
				st.UpdateMasString(*sn);
				while (!st.stringList.empty()) {
					outFile << st.stringList.at(0) << std::endl;
					st.stringList.erase(st.stringList.begin());
				}
				outFile << endRecordString << std::endl;
			}
		}
		outFile.close();
		encFile(fileName);
	}
	int getRecordCount() { return dataBase.size(); }
	int getSameRecord—ardNumber(std::string inString) {
		int count = 0;
		for (auto item : dataBase) {
			if (item.record—ardNumber == inString)
				count++;
		}
		return count;
	}
	List <StudentNode>::iterator getMinRecNum() {
		List<StudentNode>::iterator cur = dataBase.begin();
		List<StudentNode>::iterator iMin = cur;
		while (cur != dataBase.end()) {
			if (strcmp((*cur).record—ardNumber.c_str(), (*iMin).record—ardNumber.c_str()) < 0)
				iMin = cur;
			cur++;
		}
		return iMin;
	}
	void sortByRecNumMinToMax() {
		List <StudentNode> sortedLst;
		while (!dataBase.empty()) {
			List<StudentNode>::iterator pos = getMinRecNum();
			sortedLst.push_back(*pos);
			dataBase.erase(pos);
		}
		for (auto item : sortedLst) { dataBase.push_back(item); }
	}
};
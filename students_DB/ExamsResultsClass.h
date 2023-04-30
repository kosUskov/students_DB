#pragma once

struct ExamsRecords {
	std::string name;
	int mark;
	bool isEmpty;
};

class ExamsResultsClass {
	void emptpy() {
		for (int i = 0; i < 9; i++)
			for (int j = 0; j < 10; j++)
				data[i][j].isEmpty = true;
	}
public:
	ExamsRecords data[9][10];
	ExamsResultsClass() {
		emptpy();
	}
	bool add(int sess, std::string item, int mark) {
		int firstEmptyRow = getFirstEmptyRow(sess);
		if (firstEmptyRow < 9) {
			data[sess][firstEmptyRow].isEmpty = false;
			data[sess][firstEmptyRow].name = item;
			data[sess][firstEmptyRow].mark = mark;
			return true;
		}
		else { return false; }
	}
	bool add(int sess, std::string item, bool zach) {
		int mark = 0;
		if (zach) { mark = 1; }
		else { mark = 0; }
		int firstEmptyRow = getFirstEmptyRow(sess);
		if (firstEmptyRow < 9) {
			data[sess][firstEmptyRow].isEmpty = false;
			data[sess][firstEmptyRow].name = item;
			data[sess][firstEmptyRow].mark = mark;
			return true;
		}
		else { return false; }
	}
	int getFirstEmptyRow(int sessNum) {
		for (int i = 0; i < 10; i++)
			if (data[sessNum][i].isEmpty)
				return i;
		return -1;
	}
};
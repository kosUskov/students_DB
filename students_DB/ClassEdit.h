#pragma once
#include "windows.h"
#include <iostream>
#include <conio.h>
#include "ClassMenu.h"

class ClassEdit
{
private:
	std::string data;
	std::string label;
	int maxLength;
	bool isDigit(char ch) {
		if (ch >= 48 and ch <= 57) { return true; }
		else { return false; }

	}
	bool isAlpha(int ch) {
		if (ch >= 65 and ch <= 90) { return true; }
		else if (ch >= 97 and ch <= 122) { return true; }
		else if (ch >= -200 and ch <= -1) { return true; }
		else { return false; }
	}
	bool isSpace(char ch) {
		if (ch == 32) { return true; }
		else { return false; }
	}
	bool isSpec(char ch) {
		if (ch >= 33 and ch <= 47) { return true; }
		else { return false; }
	}
	bool isDigit(std::string inString) {
		for (int i = 0; i < inString.length(); i++) {
			if (not isDigit(inString[i])) { return false; }
		}
		return true;
	}
public:
	void setLabel(std::string inString) {
		label = inString;
		maxLength = label.length();
	}
	void draw() {
		system("cls");
		drawLineUp(maxLength + 6);
		std::string tmpString = "";
		tmpString = "|   ";
		tmpString = tmpString + label.c_str();
		while (tmpString.length() < maxLength + 7) { tmpString += " "; }
		tmpString += "|";
		std::cout << tmpString << std::endl;
		drawLineDown(maxLength + 7);
	}
	std::string setDataString(std::string dataString) {
		label = label + " Предыдущее значение: " + dataString;
		maxLength = label.length();
		draw();
		data = dataString;
		std::cout << data;
		char ch = 0;
		while (ch != 13) {
			ch = _getch();
			if (ch == 8) {
				std::string tmpString = "";
				tmpString = data;
				data = "";
				if (tmpString.length() > 0) {
					for (int i = 0; i < tmpString.length() - 1; i++)
						data = data + tmpString[i];
					draw();
					std::cout << data;
				}
				continue;
			}
			if (isDigit(ch) or isAlpha(ch) or isSpace(ch) or isSpec(ch)) {
				std::cout << ch;
				data = data + ch;
			}
		}
		return data;
	}
	int setDataInt(int startRange, int endRange) {
		std::string inString = "";
		while (inString.length() == 0) {
			draw();
			std::cin >> inString;
			if (!isDigit(inString)) {
				inString = "";
				std::cout << "Ошибка: Ожидалось число.";
				if (_getch() == 27) { return -1; }
				continue;
			}
			int tmpInt = atoi(inString.c_str());
			if ((tmpInt < startRange) or (tmpInt > endRange)) {
				inString = "";
				std::cout << "Ошибка: выход из заданного диапозона";
				if (_getch() == 27) { return -1; }
				continue;
			}
		}
		data = inString;
		return atoi(data.c_str());
	}
	int setDataInt(int year, int mon, bool peregruzka) {
		int startRange = 1;
		int endRange;
		if ((year % 4 == 0) && (mon == 2)) { endRange = 29; }
		else {
			if (mon == 2) { endRange = 28; }
			else if (mon <= 7) { endRange = 30 + mon % 2; }
			else { endRange = 30 + (mon + 1) % 2; }
		}
		std::string inString = "";
		while (inString.length() == 0) {
			draw();
			std::cin >> inString;
			if (not isDigit(inString)) {
				inString = "";
				std::cout << "Ошибка: Ожидалось число.";
				if (_getch() == 27) { return -1; }
				continue;
			}
			int tmpInt = atoi(inString.c_str());
			if ((tmpInt < startRange) or (tmpInt > endRange)) {
				inString = "";
				std::cout << "Ошибка: выход из заданного диапозона";
				if (_getch() == 27) { return -1; }
				continue;
			}
		}
		data = inString;
		return atoi(data.c_str());
	}
	friend void drawLineUp(int size);
	friend void drawLineDown(int size);
};
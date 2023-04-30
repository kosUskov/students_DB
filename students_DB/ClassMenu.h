#pragma once
#include "windows.h"
#include <iostream>
#include <conio.h>
#include "list.hpp"

void drawLineUp(int size) {
    std::string tmpString = " ";
    for (int i = 0; i < size; i++) { tmpString += "_"; }
    std::cout << tmpString << std::endl;
}
void drawLineDown(int size) {
    std::string tmpString = "|";
    for (int i = 0; i < size - 1; i++) { tmpString += "_"; }
    tmpString += "|";
    std::cout << tmpString << std::endl;
}
class ClassMenu {
    int selectedItem;
    int maxLength;
    bool copiright;
    int helpColMenu;
    std::string changeDate;
    List <std::string> items;
    List <std::string> titelStrings;
    void setMaxLength() {
        int tmpMax = 0;
        for (List<std::string>::iterator i = items.begin(); i != items.end(); i++) {
            if ((*i).length() > tmpMax) {
                tmpMax = (*i).length();
            }
        }
        for (List<std::string>::iterator i = titelStrings.begin(); i != titelStrings.end(); i++) {
            if ((*i).length() > tmpMax) {
                tmpMax = (*i).length();
            }
        }
        maxLength = tmpMax;
    }
    std::string getColName(int col) {
        if (col == 0) { return "Чёрный"; }
        else if (col == 1) { return "Синий цвет"; }
        else if (col == 2) { return "Зелёный цвет"; }
        else if (col == 3) { return "Голубой цвет"; }
        else if (col == 4) { return "Красный цвет"; }
        else if (col == 5) { return "Фиолетовый цвет"; }
        else if (col == 6) { return "Жёлтый цвет"; }
        else if (col == 7) { return "Белый цвет"; }
        else if (col == 8) { return "Серый цвет"; }
        else if (col == 9) { return "Тёмно-голубой цвет"; }
        else if (col == 10) { return "Светло-зелёный цвет"; }
        else if (col == 11) { return "Светло-голубой цвет"; }
        else if (col == 12) { return "Светло-красный цвет"; }
        else if (col == 13) { return "Ярко-фиолетовый цвет"; }
        else if (col == 14) { return "Светло-жёлтый цвет"; }
        else if (col == 15) { return "Ярко-белый цвет"; }
    }
    void setDown() {
        selectedItem++;
        if (selectedItem > items.size() - 1) { selectedItem = 0; }
    }
    void setUp() {
        selectedItem--;
        if (selectedItem < 0) { selectedItem = items.size() - 1; }
    }
public:
    const int colNum[16][16] = {
        {15, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
        {11, 0, 3, 4, 6, 7, 8, 9, 10, 11, 12, 14, 15},
        {9, 0, 4, 5, 6, 7, 11, 13, 14, 15},
        {9, 0, 1, 4, 5, 7, 12, 13, 14, 15},
        {13, 0, 1, 2, 3, 6, 7, 8, 9, 10, 11, 12, 14, 15},
        {12, 0, 2, 3, 6, 7, 8, 9, 10, 11, 12, 14, 15},
        {10, 0, 1, 2, 4, 5, 7, 11, 13, 14, 15},
        {12, 0, 1, 2, 3, 4, 5, 6, 8, 9, 10, 12, 13},
        {9, 0, 1, 4, 5, 7, 11, 13, 14, 15},
        {10, 0, 1, 4, 5, 7, 11, 12, 13, 14, 15},
        {10, 0, 1, 4, 5, 7, 11, 12, 13, 14, 15},
        {12, 0, 1, 2, 4, 5, 6, 8, 9, 10, 12, 13, 14},
        {11, 0, 1, 3, 4, 5, 7, 9, 10, 11, 14, 15},
        {11, 0, 2, 3, 6, 7, 8, 9, 10, 11, 14, 15},
        {13, 0, 1, 2, 3, 4, 5, 6, 8, 9, 10, 11, 12, 13},
        {11, 0, 1, 2, 3, 4, 5, 6, 8, 9, 10, 12, 13}
    };
    ClassMenu() {
        selectedItem = 0;
        maxLength = 0;
        copiright = 0;
        helpColMenu = 0;
        changeDate = "17:04:37  13.04.2021";
    }
    ~ClassMenu() {
        eraseAll();
    }
    void setCopiright(bool tmpB) { copiright = tmpB; }
    void setHelpColMenu(int tmpI) { helpColMenu = tmpI; }
    void setChangeDate(std::string date) { changeDate = date; }
    void eraseTitle() { titelStrings.clear(); }
    void eraseItem() { items.clear(); }
    void eraseAll() { eraseTitle();  eraseItem(); selectedItem = 0; }
    int getSelectedItem() { return selectedItem; }
    int getItemsCount() { return items.size(); }
    void addItem(std::string inString) {
        items.push_back(inString.c_str());
    }
    void addTitleItem(std::string inString) {
        titelStrings.push_back(inString.c_str());
    }
    void draw(int col[]) {
        setMaxLength();
        system("cls");
        void* dOut = GetStdHandle(STD_OUTPUT_HANDLE);
        drawLineUp(maxLength + 2);
        std::string tmpString = "| ";
        while (tmpString.length() < maxLength + 3) { tmpString += " "; }
        tmpString += "|";
        std::cout << tmpString << std::endl;
        for (List<std::string>::iterator i = titelStrings.begin(); i != titelStrings.end(); i++) {
            tmpString = "| ";
            tmpString = tmpString + (*i).c_str();
            while (tmpString.length() < maxLength + 3) { tmpString += " "; }
            tmpString += "|";
            std::cout << tmpString << std::endl;
        }
        drawLineDown(maxLength + 3);
        for (List<std::string>::iterator i = items.begin(); i != items.end(); i++) {
            if (std::distance(items.begin(), i) == selectedItem) {
                std::cout << "|";
                int color;
                if (helpColMenu == 1) {
                    color = 17 * colNum[col[5]][getSelectedItem() + 1];
                }
                else if (helpColMenu == 2) {
                    color = 17 * colNum[col[4]][getSelectedItem() + 1];
                }
                else if (helpColMenu == 3) {
                    color = 17 * colNum[col[7]][getSelectedItem() + 1];
                }
                else if (helpColMenu == 4) {
                    color = 17 * colNum[col[6]][getSelectedItem() + 1];
                }
                else { color = col[2] + 16 * col[3]; }
                SetConsoleTextAttribute(dOut, color);
                std::cout << " " << (*i).c_str();
                tmpString = "";
                while (tmpString.length() < maxLength - (*i).length() + 1) {
                    tmpString += " ";
                }
                std::cout << tmpString;
                color = col[0] + 16 * col[1];
                SetConsoleTextAttribute(dOut, color);
                std::cout << "|" << std::endl;
            }
            else {
                tmpString = "| ";
                tmpString += (*i).c_str();
                while (tmpString.length() < maxLength + 3) { tmpString += " "; }
                tmpString += "|";
                std::cout << tmpString << std::endl;
            }
        }
        if (items.size() != 0) { drawLineDown(maxLength + 3); }
        if (copiright) {
            int max_i = 14 - items.size() - titelStrings.size();
            for (int i = 0; i < max_i; i++) { std::cout << std::endl; }
            std::cout << "Последнее изменение настроек" << std::endl;
            std::string tmpString = changeDate;
            for (int i = 0; i < 45; i++) { tmpString += " "; }
            tmpString += (char)-87;
            tmpString += " Усков К.А., 2021";
            std::cout << tmpString << std::endl;
        }
    }
    void run(int col[]) {
        char ch = ' ';
        draw(col);
        if (items.size() != 0) {
            while (ch != 13) {
                ch = _getch();
                if ((ch == 80) || (ch == 77)) { setDown(); }
                if ((ch == 72) || (ch == 75)) { setUp(); }
                draw(col);
            }
        }
    }
    void addColor(int revCol, ClassMenu* menu) {
        int max_i = colNum[revCol][0];
        for (int i = 1; i <= max_i; i++) {
            menu->addItem(getColName(colNum[revCol][i]));
        }
    }
    friend  void drawLineUp(int size);
    friend  void drawLineDown(int size);
};
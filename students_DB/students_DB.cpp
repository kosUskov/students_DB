// students_DB.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "fileManager.h"
#include "ClassMenu.h"
#include "StudentDBClass.h"
#include "StudentClass.h"
#include "ClassEdit.h"
#include "list.hpp"
#include <ctime>

int main() {
    int colors[8] = { 15, 0, 14, 2, 0, 0, 0, 0 };
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    StudentDBClass* sdb = new StudentDBClass();
    sdb->fileName = "DB.txt";
    sdb->loadDataFromFile();
    ClassMenu* mainMenu = new ClassMenu();
    mainMenu->addTitleItem("Главное меню");
    mainMenu->addItem("Просмотреть список студетов (удалить или изменить данные)");
    mainMenu->addItem("Добавить данные о студенте в БД");
    mainMenu->addItem("Сохранить БД студентов в файл");
    mainMenu->addItem("Выполнить вариант 48");
    mainMenu->addItem("Изменить цвет");
    mainMenu->addItem("Выход");
    getSetting(colors, mainMenu);
    mainMenu->setCopiright(1);
    int resultSelectedItem = 0;
    const int exitIntStudentMenu = 0;
    StudentNode* sn;
    StudentClass* st = new StudentClass();
    while (1) {
        void* dOut = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(dOut, colors[0] + 16 * colors[1]);
        mainMenu->run(colors);
        resultSelectedItem = mainMenu->getSelectedItem();
        if (resultSelectedItem == 0) {
            int resultStudentSelectedItem = 1;
            ClassMenu* studentsMenu = new ClassMenu();
            studentsMenu->addTitleItem("Список студентов");
            while (resultStudentSelectedItem != exitIntStudentMenu) {
                studentsMenu->eraseItem();
                studentsMenu->addItem("Назад");
                studentsMenu->addItem("Удалить данные о студенте");
                for (int i = 0; i < sdb->dataBase.size(); i++) {
                    sn = &sdb->dataBase.at(i);
                    std::string tmpString = sn->surName + " " + sn->name + " " + sn->middleName + " " + sn->group;
                    studentsMenu->addItem(tmpString);
                }
                studentsMenu->run(colors);
                resultStudentSelectedItem = studentsMenu->getSelectedItem();
                if (resultStudentSelectedItem == exitIntStudentMenu) { break; }
                else if (resultStudentSelectedItem == 1) {
                    int resultDel = 1;
                    const int exitDel = 0;
                    while (resultDel != exitDel) {
                        ClassMenu* delStudentsMenu = new ClassMenu();
                        delStudentsMenu->eraseAll();
                        delStudentsMenu->addTitleItem("Выберите студента для удаления данных");
                        delStudentsMenu->addItem("Назад");
                        for (int i = 0; i < sdb->dataBase.size(); i++) {
                            sn = &sdb->dataBase.at(i);
                            std::string tmpString = sn->surName + " " + sn->name + " " + sn->middleName + " " + sn->group;
                            delStudentsMenu->addItem(tmpString);
                        }
                        delStudentsMenu->run(colors);
                        resultDel = delStudentsMenu->getSelectedItem();
                        if (resultDel == exitDel) {
                            delete delStudentsMenu;
                            break;
                        }
                        else {
                            int num = resultDel - 1;
                            sdb->dataBase.erase(std::next(sdb->dataBase.begin(), num));
                        }
                    }
                }
                else if (resultStudentSelectedItem > 1) {
                    int num = resultStudentSelectedItem - 2;
                    sn = &sdb->dataBase.at(num);
                    std::string oldRecordСardNumber = sn->recordСardNumber;
                    st->editStudent(sn, colors);
                    if (sdb->getSameRecordСardNumber(sn->recordСardNumber) > 1) {
                        sn->recordСardNumber = oldRecordСardNumber;
                        system("cls");
                        std::cout << "Ошибка введен номер зачетной книжки который уже есть в БД";
                        std::cout << std::endl << "Номер остался прежним";
                        _getch();
                    }
                }
            }
            delete studentsMenu;
        }
        else if (resultSelectedItem == 1) {
            sn = new StudentNode();
            for (int i = 0; i < 9; i++)
                for (int j = 0; j < 10; j++)
                    sn->examsRecordsData[i][j].isEmpty = true;
            st->editStudent(sn, colors);
            if (sdb->getSameRecordСardNumber(sn->recordСardNumber) >= 1) {
                system("cls");
                std::cout << "Ошибка введен номер зачетной книжки который уже есть в БД";
                std::cout << std::endl << "Данные не сохранятся";
                _getch();
            }
            else { sdb->dataBase.push_back(*sn); }
        }
        else if (resultSelectedItem == 2) {
            sdb->saveDataToFile();
        }
        else if (resultSelectedItem == 3) {
            StudentDBClass* sdb1 = new StudentDBClass();
            ClassMenu* varMenu = new ClassMenu();
            varMenu->addTitleItem("Укажите учебную группу");
            int checkGroup = 1;
            std::string tmpGroup;
            sdb1->dataBase.clear();
            while (checkGroup == 1) {
                varMenu->draw(colors);
                std::cin >> tmpGroup;
                for (auto item : sdb->dataBase) {
                    sn = &item;
                    if (sn->group == tmpGroup) {
                        sdb1->dataBase.push_back(*sn);
                        checkGroup = 0;
                    }
                }
                if (checkGroup == 1) {
                    std::cout << "Группа не найдёна";
                    if (_getch() == 27) { checkGroup = -1; }
                }
            }
            if (checkGroup == -1) {
                delete sdb1;
                continue;
            }
            StudentDBClass* sdb2 = new StudentDBClass();
            varMenu->eraseAll();
            varMenu->addTitleItem("Выберите пол");
            varMenu->addItem("Девочка");
            varMenu->addItem("Мальчик");
            int checkSex = 1;
            sdb2->dataBase.clear();
            bool tmpSex;
            while (checkSex == 1) {
                varMenu->run(colors);
                tmpSex = varMenu->getSelectedItem();
                for (auto item : sdb1->dataBase) {
                    sn = &item;
                    if (sn->sex == tmpSex) {
                        sdb2->dataBase.push_back(*sn);
                        checkSex = 0;
                    }
                }
                if (checkSex == 1) {
                    std::cout << "В группе \"" + tmpGroup + "\" не найдены ";
                    if (tmpSex) { std::cout << "мальчики"; }
                    else { std::cout << "девочки"; }
                    if (_getch() == 27) { checkSex = -1; }
                }
            }
            if (checkSex == -1) {
                delete sdb1;
                delete sdb2;
                continue;
            }
            sdb1->dataBase.clear();
            StudentDBClass* sdb3 = new StudentDBClass();
            ClassEdit* ce = new  ClassEdit();
            ce->setLabel("Введите год поступления в ВУЗ");
            int tmpStartYear = ce->setDataInt(1900, 2021);
            if (tmpStartYear == -1) {
                delete sdb3;
                delete ce;
                delete sdb2;
                continue;
            }
            for (auto item : sdb2->dataBase) {
                sn = &item;
                if (sn->startYear == tmpStartYear) { sdb1->dataBase.push_back(*sn); }
                else { sdb3->dataBase.push_back(*sn); }
            }
            delete ce;
            delete sdb2;
            sdb1->sortByRecNumMinToMax();
            sdb3->sortByRecNumMinToMax();
            varMenu->eraseAll();
            varMenu->addTitleItem("Выберите год постуления");
            varMenu->addItem(std::to_string(tmpStartYear));
            varMenu->addItem("Не " + std::to_string(tmpStartYear));
            varMenu->addItem("В главное меню");
            int yearSel = 0;
            std::string tmpString = "";
            tmpString += "Студенты группы " + tmpGroup + "; пол: ";
            if (tmpSex) { tmpString += "мальчик;"; }
            else { tmpString += "девочка;"; }
            while (yearSel != 2) {
                varMenu->run(colors);
                yearSel = varMenu->getSelectedItem();
                if (yearSel == 0) {
                    ClassMenu* finMenu = new ClassMenu();
                    finMenu->addTitleItem(tmpString);
                    finMenu->addTitleItem("поступили в " + std::to_string(tmpStartYear) + " году");
                    finMenu->addItem("Назад");
                    for (int i = 0; i < sdb1->dataBase.size(); i++) {
                        sn = &sdb1->dataBase.at(i);
                        std::string tmpString = sn->surName + " " + sn->name + " ";
                        tmpString += sn->middleName + " " + sn->recordСardNumber;
                        finMenu->addItem(tmpString);
                    }
                    int backVar = 1;
                    while (backVar != 0) {
                        finMenu->run(colors);
                        backVar = finMenu->getSelectedItem();
                        if (backVar != 0) {
                            sn = &sdb1->dataBase.at(backVar - 1);
                            std::string oldRecordСardNumber = sn->recordСardNumber;
                            st->showStudent(*sn, colors);
                        }
                    }
                    delete finMenu;
                }
                else if (yearSel == 1) {
                    ClassMenu* finMenu = new ClassMenu();
                    finMenu->addTitleItem(tmpString);
                    finMenu->addTitleItem("поступили не в " + std::to_string(tmpStartYear) + " году");
                    finMenu->addItem("Назад");
                    for (int i = 0; i < sdb3->dataBase.size(); i++) {
                        sn = &sdb3->dataBase.at(i);
                        std::string tmpString = sn->surName + " " + sn->name + " ";
                        tmpString += sn->middleName + " " + sn->recordСardNumber;
                        finMenu->addItem(tmpString);
                    }
                    int backVar = 1;
                    while (backVar != 0) {
                        finMenu->run(colors);
                        backVar = finMenu->getSelectedItem();
                        if (backVar != 0) {
                            sn = &sdb3->dataBase.at(backVar - 1);
                            std::string oldRecordСardNumber = sn->recordСardNumber;
                            st->showStudent(*sn, colors);
                        }
                    }
                    delete finMenu;
                }
            }
            delete sdb1;
            delete sdb3;
        }
        else if (resultSelectedItem == 4) {
            colors[4] = colors[0];
            colors[5] = colors[1];
            colors[6] = colors[2];
            colors[7] = colors[3];
            ClassMenu* tmpMenu = new ClassMenu();
            tmpMenu->addTitleItem("Изменение цветов");
            tmpMenu->addItem("Основной цвет");
            tmpMenu->addItem("Цвет выделения");
            tmpMenu->addItem("Сохранить настройки");
            int tmpSelectedItem = 0;
            while (tmpSelectedItem != 2) {
                tmpMenu->run(colors);
                tmpSelectedItem = tmpMenu->getSelectedItem();
                if (tmpSelectedItem == 0) {
                    ClassMenu* tmp2Menu = new ClassMenu();
                    tmp2Menu->addTitleItem("Выберите основной параметр");
                    tmp2Menu->addItem("Цвет текста");
                    tmp2Menu->addItem("Цвет фона");
                    tmp2Menu->addItem("Назад");
                    int tmp2SelectedItem = 0;
                    while (tmp2SelectedItem != 2) {
                        tmp2Menu->run(colors);
                        tmp2SelectedItem = tmp2Menu->getSelectedItem();
                        if (tmp2SelectedItem == 0) {
                            ClassMenu* tmp3Menu = new ClassMenu();
                            tmp3Menu->setHelpColMenu(1);
                            tmp3Menu->addTitleItem("Выберите цвет текста");
                            tmp3Menu->addColor(colors[5], tmp3Menu);
                            bool check = 1;
                            while (check) {
                                tmp3Menu->run(colors);
                                int checkColText = tmp3Menu->colNum[colors[5]][tmp3Menu->getSelectedItem() + 1];
                                if ((checkColText == colors[6]) & (colors[5] == colors[7])) {
                                    system("cls");
                                    std::cout << "\aОшибка, параметры выделенного пункта должны отличаться от основных";
                                    _getch();
                                }
                                else {
                                    colors[4] = checkColText;
                                    check = 0;
                                }
                            }
                            delete tmp3Menu;
                        }
                        else if (tmp2SelectedItem == 1) {
                            ClassMenu* tmp3Menu = new ClassMenu();
                            tmp3Menu->setHelpColMenu(2);
                            tmp3Menu->addTitleItem("Выберите цвет фона");
                            tmp3Menu->addColor(colors[4], tmp3Menu);
                            bool check = 1;
                            while (check) {
                                tmp3Menu->run(colors);
                                int checkColBack = tmp3Menu->colNum[colors[4]][tmp3Menu->getSelectedItem() + 1];
                                if ((checkColBack == colors[7]) & (colors[4] == colors[6])) {
                                    system("cls");
                                    std::cout << "\aОшибка, параметры выделенного пункта должны отличаться от основных";
                                    _getch();
                                }
                                else {
                                    colors[5] = checkColBack;
                                    check = 0;
                                }
                            }
                            delete tmp3Menu;
                        }
                    }
                    delete tmp2Menu;
                }
                else if (tmpSelectedItem == 1) {
                    ClassMenu* tmp2Menu = new ClassMenu();
                    tmp2Menu->addTitleItem("Выберите параметр выделенного пункта");
                    tmp2Menu->addItem("Цвет текста");
                    tmp2Menu->addItem("Цвет фона");
                    tmp2Menu->addItem("Назад");
                    int tmp2SelectedItem = 0;
                    while (tmp2SelectedItem != 2) {
                        tmp2Menu->run(colors);
                        tmp2SelectedItem = tmp2Menu->getSelectedItem();
                        if (tmp2SelectedItem == 0) {
                            ClassMenu* tmp3Menu = new ClassMenu();
                            tmp3Menu->setHelpColMenu(3);
                            tmp3Menu->addTitleItem("Выберите цвет текста");
                            tmp3Menu->addColor(colors[7], tmp3Menu);
                            bool check = 1;
                            while (check) {
                                tmp3Menu->run(colors);
                                int checkColSelText = tmp3Menu->colNum[colors[7]][tmp3Menu->getSelectedItem() + 1];
                                if ((checkColSelText == colors[4]) & (colors[5] == colors[7])) {
                                    system("cls");
                                    std::cout << "\aОшибка, параметры выделенного пункта должны отличаться от основных";
                                    _getch();
                                }
                                else {
                                    colors[6] = checkColSelText;
                                    check = 0;
                                }
                            }
                            delete tmp3Menu;
                        }
                        else if (tmp2SelectedItem == 1) {
                            ClassMenu* tmp3Menu = new ClassMenu();
                            tmp3Menu->setHelpColMenu(4);
                            tmp3Menu->addTitleItem("Выберите цвет фона");
                            tmp3Menu->addColor(colors[6], tmp3Menu);
                            bool check = 1;
                            while (check) {
                                tmp3Menu->run(colors);
                                int checkColSelBack = tmp3Menu->colNum[colors[6]][tmp3Menu->getSelectedItem() + 1];
                                if ((checkColSelBack == colors[5]) & (colors[4] == colors[6])) {
                                    system("cls");
                                    std::cout << "\aОшибка, параметры выделенного пункта должны отличаться от основных";
                                    _getch();
                                }
                                else {
                                    colors[7] = checkColSelBack;
                                    check = 0;
                                }
                            }
                            delete tmp3Menu;
                        }
                    }
                    delete tmp2Menu;
                }
                else if (tmpSelectedItem == 2) {
                    ClassMenu* tmp2Menu = new ClassMenu();
                    tmp2Menu->addTitleItem("Вы действительно хотите");
                    tmp2Menu->addTitleItem("сохранить настройки?");
                    tmp2Menu->addItem("Да");
                    tmp2Menu->addItem("Нет");
                    int tmp2SelectedItem = 0;
                    tmp2Menu->run(colors);
                    tmp2SelectedItem = tmp2Menu->getSelectedItem();
                    if (tmp2SelectedItem == 0) {
                        setSetting(colors, mainMenu);
                    }
                    delete tmp2Menu;
                }
            }
        }
        else if (resultSelectedItem == 5) {
            delete st;
            delete sdb;
            delete mainMenu;
            system("cls");
            break;
        }
    }
}
#pragma once
#include <string>
#include "ClassMenu.h"
#include <ctime>

class StringBuilderClass {
public:
    std::string setParam(std::string name, std::string value) {
        std::string outString = "name:00; value:str:00 -: ";
        std::string lengthName = std::to_string(name.length());
        if (lengthName.length() == 1) {
            outString[6] = lengthName[0];
        }
        if (lengthName.length() == 2) {
            outString[5] = lengthName[0];
            outString[6] = lengthName[1];
        }
        std::string lengthValue = std::to_string(value.length());
        if (lengthValue.length() == 1) {
            outString[20] = lengthValue[0];
        }
        if (lengthValue.length() == 2) {
            outString[19] = lengthValue[0];
            outString[20] = lengthValue[1];
        }
        outString = outString + name + "=" + value;
        return outString;
    }
    std::string setParam(std::string name, int intvalue) {
        std::string outString = "name:00; value:int:00 -: ";
        std::string value = std::to_string(intvalue);
        std::string lengthName = std::to_string(name.length());
        if (lengthName.length() == 1) {
            outString[6] = lengthName[0];
        }
        if (lengthName.length() == 2) {
            outString[5] = lengthName[0];
            outString[6] = lengthName[1];
        }
        std::string lengthValue = std::to_string(value.length());
        if (lengthValue.length() == 1) {
            outString[20] = lengthValue[0];
        }
        if (lengthValue.length() == 2) {
            outString[19] = lengthValue[0];
            outString[20] = lengthValue[1];
        }

        outString = outString + name + "=" + value;
        return outString;
    }
    std::string getName(std::string inString) {
        std::string tmpString = "00";
        int lengthName = 0;
        tmpString[0] = inString[5];
        tmpString[1] = inString[6];
        lengthName = atoi(tmpString.c_str());
        tmpString = "00";
        tmpString[0] = inString[19];
        tmpString[1] = inString[20];
        int lengthValue = 0;
        lengthValue = atoi(tmpString.c_str());
        int offset = 26;
        std::string valueString(lengthName, ' ');
        for (int i = 0; i < lengthName; i++) {
            valueString[i] = inString[i + offset - 1];
        }
        return valueString;
    }
    std::string getType(std::string inString) {
        std::string ch = " ";
        ch[0] = inString[15];
        if (ch.compare("i") == 0) {
            return "int";
        }
        else if (ch.compare("s") == 0) {
            return "str";
        }
        else { return ""; }
    }
    int getValueInt(std::string inString) {
        std::string tmpString = "00";
        int lengthName = 0;
        tmpString[0] = inString[5];
        tmpString[1] = inString[6];
        lengthName = atoi(tmpString.c_str());
        tmpString = "00";
        tmpString[0] = inString[19];
        tmpString[1] = inString[20];
        int lengthValue = 0;
        lengthValue = atoi(tmpString.c_str());
        int offset = 26;
        std::string valueString(lengthValue, '0');
        for (int i = 0; i < lengthValue; i++) {
            valueString[i] = inString[i + offset + lengthName];
        }
        return atoi(valueString.c_str());
    }
    std::string getValueStr(std::string inString) {
        std::string tmpString = "00";
        int lengthName = 0;
        tmpString[0] = inString[5];
        tmpString[1] = inString[6];
        lengthName = atoi(tmpString.c_str());
        tmpString = "00";
        tmpString[0] = inString[19];
        tmpString[1] = inString[20];
        int lengthValue = 0;
        lengthValue = atoi(tmpString.c_str());
        int offset = 26;
        std::string valueString(lengthValue, '0');
        for (int i = 0; i < lengthValue; i++) {
            valueString[i] = inString[i + offset + lengthName];
        }
        return valueString;
    }
    std::string split(std::string inString, char delimiter, int num) {
        std::string outString = "";
        int numDelimeter = 0;
        for (int i = 0; i <= inString.length(); i++) {
            if (inString[i] == delimiter) {
                numDelimeter++;
            }
            if ((numDelimeter == num) && (delimiter != inString[i])) {
                outString = outString + inString[i];
            }
        }
        return outString;
    }
};

const std::string startRecordString = "### Start Record";
const std::string endRecordString = "### End Record";

class FileManagerClass : public StringBuilderClass {
public:
    std::string fileName = "";
    FileManagerClass() {
        fileName = "";
    }
    FileManagerClass(std::string fileName) {
        this->fileName = fileName;
    }
};
std::string getDate(tm inDate) {
    std::string tmpDate = "";
    if (inDate.tm_hour < 10) { tmpDate += "0"; }
    tmpDate += std::to_string(inDate.tm_hour);
    tmpDate += ":";
    if (inDate.tm_min < 10) { tmpDate += "0"; }
    tmpDate += std::to_string(inDate.tm_min);
    tmpDate += ":";
    if (inDate.tm_sec < 10) { tmpDate += "0"; }
    tmpDate += std::to_string(inDate.tm_sec);
    tmpDate += "  ";
    if (inDate.tm_mday < 10) { tmpDate += "0"; }
    tmpDate += std::to_string(inDate.tm_mday);
    tmpDate += ".";
    if (inDate.tm_mon < 9) { tmpDate += "0"; }
    tmpDate += std::to_string(inDate.tm_mon + 1);
    tmpDate += ".";
    tmpDate += std::to_string(inDate.tm_year + 1900);
    return tmpDate;
}
void encFile(std::string file) {
    srand(time(0));
    char* password = new char[129];
    for (int i = 0; i < 128; ++i) {
        int rd = rand() % 6;
        if (rd == 0) { password[i] = rand() % 31 + 'Ў'; }
        else if (rd == 1) { password[i] = rand() % 32 + 'А'; }
        else if (rd == 1) { password[i] = rand() % 32 + 'а'; }
        else if (rd == 0) { password[i] = rand() % 10 + '0'; }
        else if (rd == 1) { password[i] = rand() % 26 + 'A'; }
        else if (rd == 2) { password[i] = rand() % 26 + 'a'; }
    }
    password[128] = '\0';
    std::string command = "forCrypto\\openssl.exe enc -aes-256-cbc -salt -in";
    command += " forCrypto\\" + file + " -out " + file + ".enc -pass pass:";
    command += password;
    FILE* fCheck1 = 0, * fCheck2 = 0, * fCheck3 = 0;
    fopen_s(&fCheck1, "forCrypto\\openssl.exe", "rb");
    std::string tmpFile = "forCrypto\\" + file;
    fopen_s(&fCheck2, tmpFile.c_str(), "rb");
    if ((fCheck1 != 0) & (fCheck2 != 0)) { system(command.c_str()); }
    fclose(fCheck1);
    fclose(fCheck2);
    if (remove(tmpFile.c_str())) {
        std::cout << "Ошибка: открытый текст не удалился" << std::endl;
    }
    FILE* fKey;
    fopen_s(&fKey, "forCrypto\\key", "wb");
    fwrite(password, 1, 129, fKey);
    fclose(fKey);
    command = "forCrypto\\openssl.exe rsautl -encrypt -inkey forCrypto\\rsa.public -pubin";
    command += " -in forCrypto\\key -out forCrypto\\key.enc";
    fCheck1 = 0; fCheck2 = 0;
    fopen_s(&fCheck1, "forCrypto\\openssl.exe", "rb");
    fopen_s(&fCheck2, "forCrypto\\rsa.public", "rb");
    fopen_s(&fCheck3, "forCrypto\\key", "rb");
    if ((fCheck1 != 0) & (fCheck2 != 0) & (fCheck3 != 0)) { system(command.c_str()); }
    fclose(fCheck1);
    fclose(fCheck2);
    fclose(fCheck3);
    if (remove("forCrypto\\key")) {
        std::cout << "Ошибка: ключ не удалился" << std::endl;
    }
    delete[] password;
}
void decFile(std::string file) {
    std::string command = "forCrypto\\openssl.exe rsautl -decrypt -inkey";
    command += " forCrypto\\rsa.private -in forCrypto\\key.enc -out forCrypto\\key";
    FILE* fCheck1 = 0, * fCheck2 = 0, * fCheck3 = 0;
    fopen_s(&fCheck1, "forCrypto\\openssl.exe", "rb");
    fopen_s(&fCheck2, "forCrypto\\rsa.private", "rb");
    fopen_s(&fCheck3, "forCrypto\\key.enc", "rb");
    if ((fCheck1 != 0) & (fCheck2 != 0) & (fCheck2 != 0)) { system(command.c_str()); }
    fclose(fCheck1);
    fclose(fCheck2);
    fclose(fCheck3);
    if (remove("forCrypto\\key.enc")) {
        std::cout << "Ошибка: зашифрованный ключ не удалился" << std::endl;
    }
    char* password = new char[129];
    FILE* fKey;
    fopen_s(&fKey, "forCrypto\\key", "rb");
    fread(password, 1, 129, fKey);
    fclose(fKey);
    if (remove("forCrypto\\key")) {
        std::cout << "Ошибка: ключ не удалился" << std::endl;
    }
    command = "forCrypto\\openssl.exe enc -aes-256-cbc -d -in " + file;
    command += ".enc -out forCrypto\\" + file + " -pass pass:";
    command += password;
    fCheck1 = 0; fCheck2 = 0;
    fopen_s(&fCheck1, "forCrypto\\openssl.exe", "rb");
    std::string tmpFile = file + ".enc";
    fopen_s(&fCheck2, tmpFile.c_str(), "rb");
    if ((fCheck1 != 0) & (fCheck2 != 0)) { system(command.c_str()); }
    fclose(fCheck1);
    fclose(fCheck2);
    if (remove(tmpFile.c_str()) != 0) {
        std::cout << "Ошибка: закрытый текст не удалился" << std::endl;
    }
    delete[] password;
}
void getSetting(int* col, ClassMenu* menu) {
    FILE* takeSetting = 0;
    fopen_s(&takeSetting, "programSettings", "rb");
    if (takeSetting != 0) {
        char date[21];
        fread(&date, 21, 1, takeSetting);
        menu->setChangeDate(date);
        int tmpInt;
        fread(&tmpInt, 4, 1, takeSetting);
        col[0] = tmpInt;
        fread(&tmpInt, 4, 1, takeSetting);
        col[1] = tmpInt;
        fread(&tmpInt, 4, 1, takeSetting);
        col[2] = tmpInt;
        fread(&tmpInt, 4, 1, takeSetting);
        col[3] = tmpInt;
        fclose(takeSetting);
    }
}
void setSetting(int* col, ClassMenu* menu) {
    struct tm curTime;
    long sec;
    _time32(&sec);
    _localtime32_s(&curTime, &sec);
    FILE* putSetting = 0;
    fopen_s(&putSetting, "programSettings", "wb");
    std::string tmpDate = getDate(curTime);
    menu->setChangeDate(tmpDate);
    char date[21];
    strcpy_s(date, 21, tmpDate.c_str());
    fwrite(&date, 21, 1, putSetting);
    int tmpI = col[4];
    fwrite(&tmpI, 4, 1, putSetting);
    col[0] = tmpI;
    tmpI = col[5];
    fwrite(&tmpI, 4, 1, putSetting);
    col[1] = tmpI;
    tmpI = col[6];
    fwrite(&tmpI, 4, 1, putSetting);
    col[2] = tmpI;
    tmpI = col[7];
    fwrite(&tmpI, 4, 1, putSetting);
    col[3] = tmpI;
    fclose(putSetting);
}
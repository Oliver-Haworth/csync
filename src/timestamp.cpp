#include "timestamp.h"
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>

using namespace std;

void writeTimestamp(string filepath) {
    time_t timestamp = time(&timestamp);

    ofstream MyFile(filepath);
    MyFile << timestamp;
    MyFile.close();
}

int readTimestamp(string filepath) {
    string myText;
    int timestamp = 0;

    ifstream MyReadFile(filepath);
    if (getline(MyReadFile, myText)) {
        timestamp = stoi(myText);
    }
    MyReadFile.close();
    return timestamp;
}

string compareTimestamp(string filepath1, string filepath2) {
    string timeStr1, timeStr2;

    ifstream file1(filepath1);
    if (getline(file1, timeStr1)) {
        file1.close();
    }

    ifstream file2(filepath2);
    if (getline(file2, timeStr2)) {
        file2.close();
    }

    if (timeStr1 == timeStr2) {
        return "identical timestamps\n";
    } else {
        return "different timestamps\n";
    }
}
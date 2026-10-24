#include <iostream>
#include <string>
#include <fstream>
#include <ctime>

using namespace std;

void askiiLogo() {
    // logo generated using https://asciigenerators.com/#app
    string myText;

    ifstream MyReadFile("askii.txt");
    while (getline (MyReadFile, myText)) {
        cout << myText << "\n";
    }
    MyReadFile.close();
}

void writeTimestamp(string filename) {
    time_t timestamp = time(&timestamp);

    ofstream MyFile(filename);
    MyFile << timestamp;
    MyFile.close();
}

void readTimestamp(string filename) {
    string myText;

    ifstream MyReadFile(filename);
    while (getline (MyReadFile, myText)) {
        cout << myText << "\n";
    }
    MyReadFile.close();
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

    if (timeStr1 != timeStr2) {
        return "identical";
    } else {
        return "different";
    }
}

int main() {

    askiiLogo();

    writeTimestamp("timestamp1.txt");
    writeTimestamp("timestamp2.txt");

    readTimestamp("timestamp1.txt");
    readTimestamp("timestamp2.txt");

    cout << compareTimestamp("timestamp1.txt", "timestamp2");
    
    return 0;
}
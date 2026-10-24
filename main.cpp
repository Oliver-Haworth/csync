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

void writeTimestamp(string filepath) {
    time_t timestamp = time(&timestamp);

    ofstream MyFile(filepath);
    MyFile << timestamp;
    MyFile.close();
}

void readTimestamp(string filepath) {
    string myText;

    ifstream MyReadFile(filepath);
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

void readSavedFilepaths(string filename, string filepaths[2]) {
    string myText;
    int i = 0;

    ifstream MyReadFile(filename);
    while (getline(MyReadFile, myText) && i < 2) {
        filepaths[i] = myText;
        i++;
    }
    MyReadFile.close();
}

int main() {

    askiiLogo();

    string filepaths[2];
    
    readSavedFilepaths("filepaths.txt", filepaths);

    writeTimestamp(filepaths[0]);
    writeTimestamp(filepaths[1]);

    readTimestamp(filepaths[0]);
    readTimestamp(filepaths[1]);

    cout << compareTimestamp("timestamp1.txt", "timestamp2");
    
    return 0;
}
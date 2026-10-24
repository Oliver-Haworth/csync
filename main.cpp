#include <iostream>
#include <string>
#include <fstream>

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

void writeTimestamp(string write) {
    ofstream MyFile("timestamp.txt");
    MyFile << write;
    MyFile.close();
}

void readTimestamp() {
    string myText;

    ifstream MyReadFile("timestamp.txt");
    while (getline (MyReadFile, myText)) {
        cout << myText << "\n";
    }
    MyReadFile.close();
}

int main() {

    askiiLogo();

    writeTimestamp("Hello World");

    readTimestamp();
    
    return 0;
}
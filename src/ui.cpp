#include "ui.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void askiiLogo() {
    // logo generated using https://asciigenerators.com/#app
    string myText;

    ifstream MyReadFile("data/askii.txt");
    while (getline (MyReadFile, myText)) {
        cout << myText << "\n";
    }
    MyReadFile.close();
}
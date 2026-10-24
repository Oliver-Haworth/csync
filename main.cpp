#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <filesystem>

using namespace std;
namespace fs = filesystem;

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

    if (timeStr1 == timeStr2) {
        return "identical timestamps\n";
    } else {
        return "different timestamps\n";
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

// AI gen function, i have no idea how to measure directory sizes
uintmax_t getDirSize(const string &dirPath) {
    uintmax_t totalSize = 0;
    try {
        for (const auto &entry : fs::recursive_directory_iterator(dirPath, fs::directory_options::skip_permission_denied)) {
            if (entry.is_regular_file()) {
                totalSize += entry.file_size();
            }
        }
    } catch (const fs::filesystem_error &e) {
        cerr << "Error measuring " << dirPath << ": " << e.what() << endl;
    }
    return totalSize;
}

void readDirSize(const string &dirPath) {
    uintmax_t size = getDirSize(dirPath);
    cout << "Size of " << dirPath << ": " << size << " bytes" << endl;
}


int main() {
    askiiLogo();

    string filepaths[2];
    
    readSavedFilepaths("filepaths.txt", filepaths);

    writeTimestamp(filepaths[0] + "/.csync/timestamp.txt");
    writeTimestamp(filepaths[1] + "/.csync/timestamp.txt");

    readTimestamp(filepaths[0] + "/.csync/timestamp.txt");
    readTimestamp(filepaths[1] + "/.csync/timestamp.txt");
    readDirSize(filepaths[0]);
    readDirSize(filepaths[1]);
    readTimestamp(filepaths[0]);
    readTimestamp(filepaths[1]);

    cout << compareTimestamp(filepaths[0] + "/.csync/timestamp.txt",filepaths[1] + "timestamp.txt");
    
    return 0;
}
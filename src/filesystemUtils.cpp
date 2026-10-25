#include "filesystemUtils.h"
#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <cstdint>

using namespace std;
namespace fs = filesystem;

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

uintmax_t readDirSize(const string &dirPath) {
    return getDirSize(dirPath);
}

string compareDirSize(string dirPath1, string dirPath2) {
    uintmax_t dir1Size = readDirSize(dirPath1);
    uintmax_t dir2Size = readDirSize(dirPath2);

    if (dir1Size == dir2Size) {
        return "identical sizes\n";
    } else {
        return "different sizes\n";
    }
}

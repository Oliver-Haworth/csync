#include <iostream>
#include <string>
#include "ui.h"
#include "timestamp.h"
#include "filesystemUtils.h"

using namespace std;

int main() {
    askiiLogo();

    string filepaths[2];
    
    readSavedFilepaths("data/filepaths.txt", filepaths);

    writeTimestamp(filepaths[0] + "/.csync/timestamp.txt");
    writeTimestamp(filepaths[1] + "/.csync/timestamp.txt");

    cout << "dir1 timestamp: " << readTimestamp(filepaths[0] + "/.csync/timestamp.txt") << "\n";
    cout << "dir2 timestamp: " << readTimestamp(filepaths[1] + "/.csync/timestamp.txt") << "\n";
    cout << compareTimestamp(filepaths[0] + "/.csync/timestamp.txt", filepaths[1] + "/.csync/timestamp.txt") << "\n";
    cout << compareTimestamp(filepaths[0] + "/.csync/timestamp.txt", filepaths[1] + "/.csync/timestamp.txt") << "\n";

    cout << "dir1 size: " << readDirSize(filepaths[0]) << "\n";
    cout << "dir2 size: " << readDirSize(filepaths[1]) << "\n";
    // cout << compareDirSize(filepaths[0], filepaths[1]);
    
    return 0;
}
#include <iostream>
#include <string>
#include "ui.h"
#include "timestamp.h"
#include "filesystemUtils.h"
#include "hash.h"

using namespace std;

int main() {
    askiiLogo();

    // hash single file
    string fileHash = hashFile("./dir1/test.txt");
    if (!fileHash.empty()) {
        cout << "test.txt hash: " << fileHash << "\n";
    } else {
        cerr << "Could not hash ./dir1/test.txt\n";
    }

    // pull filepaths
    string filepaths[2];
    readSavedFilepaths("data/filepaths.txt", filepaths);

    // write and read timestamps
    writeTimestamp(filepaths[0] + "/.csync/timestamp.txt");
    writeTimestamp(filepaths[1] + "/.csync/timestamp.txt");

    cout << "dir1 timestamp: " << readTimestamp(filepaths[0] + "/.csync/timestamp.txt") << "\n";
    cout << "dir2 timestamp: " << readTimestamp(filepaths[1] + "/.csync/timestamp.txt") << "\n";
    cout << compareTimestamp(filepaths[0] + "/.csync/timestamp.txt", filepaths[1] + "/.csync/timestamp.txt") << "\n";

    // hash dir and compare
    string hash1 = hashDirectory(filepaths[0]);
    string hash2 = hashDirectory(filepaths[1]);

    cout << "dir1 hash: " << hash1 << "\n";
    cout << "dir2 hash: " << hash2 << "\n";

    if (hash1 == hash2 && !hash1.empty()) {
        cout << "Directories are identical in content and structure.\n";
    } else {
        cout << "Directories differ.\n";
    }

    return 0;
}
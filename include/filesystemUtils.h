#pragma once
#include <string>
#include <cstdint>

void readSavedFilepaths(std::string filename, std::string filepaths[2]);
uintmax_t getDirSize(const std::string &dirPath);
uintmax_t readDirSize(const std::string &dirPath);
std::string compareDirSize(std::string dirPath1, std::string dirPath2);
#pragma once
#include <string>

void writeTimestamp(std::string filepath);
int readTimestamp(std::string filepath);
std::string compareTimestamp(std::string filepath1, std::string filepath2);
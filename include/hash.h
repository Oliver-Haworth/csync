#pragma once
#include <string>
#include <filesystem>

std::string hashFile(const std::filesystem::path& filepath);
std::string hashDirectory(const std::filesystem::path& dirpath);
std::string hashPath(const std::filesystem::path& path);
#include "../include/FileReadWrite.hpp"
#include <fstream>
#include <sstream>
#include <filesystem>
#include <spdlog/spdlog.h>

bool FileReadWrite::exists(const std::string& file) const {
    return std::filesystem::exists(file);
}

bool FileReadWrite::createDirectory(const std::string& dir) {
    return std::filesystem::create_directory(dir);
}

bool FileReadWrite::createFile(const std::string& file, const std::string& content) {

    std::ofstream outFile(file, std::ios::out | std::ios::trunc);
    if (!outFile)
    {
        outFile = std::ofstream(file, std::ios::out | std::ios::app);
        outFile << content;
        return false;
    }
    outFile << content;
    return true;
}

std::string FileReadWrite::readFile(const std::string& file) {
    std::ifstream inFile(file);
    if (!inFile)
    {
        return "";
    }

    std::stringstream buffer;
    buffer << inFile.rdbuf();
    return buffer.str();
}

bool FileReadWrite::copy(const std::string& src, const std::string& dest) {
    try
    {
        std::filesystem::copy_file(src, dest, std::filesystem::copy_options::overwrite_existing);
        return true;
    }
    catch (const std::filesystem::filesystem_error&)
    {
        return false;
    }
}

bool FileReadWrite::remove(const std::string& p) {
    return std::filesystem::remove(p);
}

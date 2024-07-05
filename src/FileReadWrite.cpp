#include "../include/FileReadWrite.hpp"
#include <fstream>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <spdlog/spdlog.h>

namespace fs = boost::filesystem;

bool FileReadWrite::exists(const std::string& file) const {
    fs::path filePath = file;
    return fs::exists(filePath);
}

bool FileReadWrite::createDirectory(const std::string& dir) {
    fs::path dirPath = dir;
    try {
        return fs::create_directory(dirPath);
    }
    catch (const fs::filesystem_error& err) {
        spdlog::error("Error creating directory {}: {}", dir, err.what());
        return false;
    }
}

bool FileReadWrite::createFile(const std::string& file, const std::string& content) {
    fs::path filePath = file;
    try {
        boost::filesystem::ofstream ofs(filePath, std::ios::binary);
        if (!ofs) {
            spdlog::error("Error creating file {}", file);
            return false;
        }
        ofs << content;
        ofs.close();
        return true;
    }
    catch (const fs::filesystem_error& err) {
        spdlog::error("Error creating file {}: {}", file, err.what());
        return false;
    }
}

std::string FileReadWrite::readFile(const std::string& file) {
    fs::path filePath = file;
    try {
        boost::filesystem::ifstream ifs(filePath, std::ios::binary);
        if (!ifs) {
            spdlog::error("Error opening file for reading {}", file);
            return "";
        }
        std::string content((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
        return content;
    }
    catch (const fs::filesystem_error& err) {
        spdlog::error("Error reading file {}: {}", file, err.what());
        return "";
    }
}

bool FileReadWrite::copy(const std::string& src, const std::string& dest) {
    fs::path srcPath = src;
    fs::path destPath = dest;
    try {
        fs::copy(srcPath, destPath);
        return true;
    }
    catch (const fs::filesystem_error& err) {
        spdlog::error("Error copying {} to {}: {}", src, dest, err.what());
        return false;
    }
}

bool FileReadWrite::remove(const std::string& p) {
    fs::path filePath = p;
    try {
        return fs::remove_all(filePath);
    }
    catch (const fs::filesystem_error& err) {
        spdlog::error("Error removing {}: {}", p, err.what());
        return false;
    }
}

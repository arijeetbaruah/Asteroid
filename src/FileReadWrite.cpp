#include "../include/FileReadWrite.hpp"
#include <fstream>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <spdlog/spdlog.h>

#include "../include/SettingData.hpp"

const std::string m_basePath = "../save/";
namespace fs = boost::filesystem;

bool FileReadWrite::exists(const std::string& file) const {
    fs::path filePath = m_basePath + file;
    return fs::exists(filePath);
}

bool FileReadWrite::createDirectory(const std::string& dir) {
    fs::path dirPath = m_basePath + dir;
    try {
        return fs::create_directory(dirPath);
    }
    catch (const fs::filesystem_error& err) {
        spdlog::error("Error creating directory {}: {}", dir, err.what());
        return false;
    }
}

bool FileReadWrite::createFile(const std::string& file, const std::string& content) {
    fs::path filePath = m_basePath + file;
    try {
        boost::filesystem::ofstream ofs(filePath);
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
    fs::path filePath = m_basePath + file;
    try {
        boost::filesystem::ifstream ifs(filePath);
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
    fs::path srcPath = m_basePath + src;
    fs::path destPath = m_basePath + dest;
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
    fs::path filePath = m_basePath + p;
    try {
        return fs::remove_all(filePath);
    }
    catch (const fs::filesystem_error& err) {
        spdlog::error("Error removing {}: {}", p, err.what());
        return false;
    }
}

template <typename T>
bool FileReadWrite::serializeObject(const std::string& file, const T& object) {
    fs::path filePath = m_basePath + file;
    try {
        boost::filesystem::ofstream ofs(filePath, std::ios::binary);
        if (!ofs) {
            spdlog::error("Error creating file {}", file);
            return false;
        }
        boost::archive::text_oarchive oa(ofs);
        oa << object;
        ofs.close();
        return true;
    }
    catch (const std::exception& e) {
        spdlog::error("Error serializing object {}: {}", file, e.what());
        return false;
    }
}

template <typename T>
bool FileReadWrite::deserializeObject(const std::string& file, T& object) {
    fs::path filePath = m_basePath + file;
    try {
        boost::filesystem::ifstream ifs(filePath, std::ios::binary);
        if (!ifs) {
            spdlog::error("Error opening file for deserialization {}", file);
            return false;
        }
        boost::archive::text_iarchive ia(ifs);
        ia >> object;
        ifs.close();
        return true;
    }
    catch (const std::exception& e) {
        spdlog::error("Error deserializing object {}: {}", file, e.what());
        return false;
    }
}

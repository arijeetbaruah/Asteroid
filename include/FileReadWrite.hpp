#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class FileReadWrite
{
public:
    bool exists(const std::string& file) const;
    bool createDirectory(const std::string& dir);
    bool createFile(const std::string& file, const std::string& content);
    std::string readFile(const std::string& file);
    bool copy(const std::string& src, const std::string& dest);
    bool remove(const std::string& p);

    // Serialize object to file
    template <typename T>
    bool serializeObject(const std::string& file, const T& object);

    // Deserialize object from file
    template <typename T>
    bool deserializeObject(const std::string& file, T& object);
};


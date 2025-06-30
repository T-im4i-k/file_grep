#pragma once

#include <string>
#include <fstream>

class FileManip
{
public:
    using OpenMods = std::initializer_list<std::ios_base::openmode>;
    
    FileManip(const std::string &file_name, OpenMods mods);

    void close();

    const std::string &fileName() const;

    bool fail() const;

    bool isOpen() const;

    ~FileManip() = default;

protected:
    std::fstream file_stream_;
    std::string file_name_;
};

#pragma once

#include <string>
#include <fstream>

class FileManip
{
public:
    using OpenMods = std::initializer_list<std::ios_base::openmode>;
    
    FileManip(const std::string &file_name, OpenMods mods);

    void close();

    [[nodiscard]] const std::string &fileName() const;

    [[nodiscard]] bool fail() const;

    [[nodiscard]] bool isOpen() const;

    ~FileManip() = default;

protected:
    std::fstream file_stream_;
    std::string file_name_;
};

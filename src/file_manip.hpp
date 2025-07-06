#pragma once

#include <string>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

class FileManip
{
public:
    using OpenMods = std::initializer_list<std::ios_base::openmode>;
    
    FileManip(const fs::path &file_path, OpenMods mods);

    void close();

    [[nodiscard]] const fs::path &filePath() const;

    [[nodiscard]] bool fail() const;

    [[nodiscard]] bool isOpen() const;

    ~FileManip() = default;

protected:
    std::fstream file_stream_;
    fs::path file_path_;
};

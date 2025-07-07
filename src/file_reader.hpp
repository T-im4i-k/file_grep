#pragma once

#include "file_manip.hpp"

#include <optional>
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

class FileReader : public FileManip
{
public:
    FileReader(const fs::path &file_path);

    void seekg(const size_t pos);

    [[nodiscard]] size_t tellg();

    [[nodiscard]] std::optional<std::string> readToString(const size_t string_size);

    [[nodiscard]] std::optional<char> readChar();
};
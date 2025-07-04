#pragma once

#include "file_manip.hpp"

#include <optional>

class FileReader : public FileManip
{
public:
    FileReader(const std::string &file_name);

    void seekg(const size_t pos);

    [[nodiscard]] size_t tellg();

    [[nodiscard]] std::optional<std::string> readToString(const size_t string_size);

    [[nodiscard]] std::optional<char> readChar();
};
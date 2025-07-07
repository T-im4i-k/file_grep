#pragma once

#include <filesystem>

namespace fs = std::filesystem;

class DirIterator
{
public:
    DirIterator(const fs::path &dir_path);

    [[nodiscard]] const fs::directory_entry &curr() const;

    void next();

    [[nodiscard]] bool end() const;

    [[nodiscard]] bool fail() const;

    [[nodiscard]] fs::path dirPath() const;

    void reset();

private:
    std::error_code ec_;
    fs::recursive_directory_iterator dir_it_;
    fs::path dir_path_;
};
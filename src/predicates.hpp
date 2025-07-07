#pragma once

#include <filesystem>

namespace fs = std::filesystem;

class Tautology
{
public:
    template <typename... Args>
    bool operator()(Args &&...args) const
    {
        return true;
    }
};

class IsRegularFile
{
public:
    bool operator()(const fs::directory_entry &entry) const
    {
        return entry.is_regular_file();
    }
};

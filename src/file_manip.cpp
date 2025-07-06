#include "file_manip.hpp"

FileManip::FileManip(const fs::path &file_path, OpenMods mods) : file_path_(file_path)
{
    auto open_mode = std::ios_base::openmode(0);
    for (auto mode : mods)
    {
        open_mode |= mode;
    }
    file_stream_.open(file_path, open_mode);

    if (fail())
    {
        throw std::ios_base::failure(
            "Failed To Open The File: " + filePath().string());
    }
}

void FileManip::close()
{
    file_stream_.close();
    if (fail())
    {
        throw std::ios_base::failure(
            "Failed To Close The File: " + filePath().string());
    }
}

const fs::path &FileManip::filePath() const
{
    return file_path_;
}

bool FileManip::fail() const
{
    return file_stream_.fail();
}

bool FileManip::isOpen() const
{
    return file_stream_.is_open();
}

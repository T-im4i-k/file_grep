#include "file_manip.hpp"

FileManip::FileManip(const std::string &file_name, OpenMods mods) : file_name_(file_name)
{
    auto open_mode = std::ios_base::openmode(0);
    for (auto mode : mods)
    {
        open_mode |= mode;
    }
    file_stream_.open(file_name, open_mode);

    if (fail())
    {
        throw std::ios_base::failure(
            "Failed To Open The File: " + fileName());
    }
}

void FileManip::close()
{
    file_stream_.close();
    if (fail())
    {
        throw std::ios_base::failure(
            "Failed To Close The File: " + fileName());
    }
}

const std::string &FileManip::fileName() const
{
    return file_name_;
}

bool FileManip::fail() const
{
    return file_stream_.fail();
}

bool FileManip::isOpen() const
{
    return file_stream_.is_open();
}

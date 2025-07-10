#include "dir_iterator.hpp"

DirIterator::DirIterator(const fs::path &dir_path) : ec_(), dir_it_(dir_path, ec_), dir_path_(dir_path)
{
    if (fail())
    {
        throw fs::filesystem_error(
            "DirIterator::DirIterator: Failed To Construct Directory Iterator For Directory \"" + dirPath().string() + "\"", ec_);
    }
}

void DirIterator::next()
{
    if (end())
    {
        throw std::out_of_range(
            "DirIterator::next: Failed To Increment Directory Iterator For Directory \"" + dirPath().string() + "\"");
    }

    dir_it_.increment(ec_);

    if (fail())
    {
        throw fs::filesystem_error(
            "DirIterator::next: Failed To Increment Directory Iterator For Directory \"" + dirPath().string() + "\"", ec_);
    }
}

[[nodiscard]] const fs::directory_entry &DirIterator::curr() const
{
    if (end())
    {
        throw std::out_of_range(
            "DirIterator::curr: Failed To Access Current Entry Of Directory Iterator For Directory \"" + dirPath().string() + "\"");
    }
    return *dir_it_;
}

[[nodiscard]] bool DirIterator::end() const
{
    static const fs::recursive_directory_iterator end_it;
    return dir_it_ == end_it;
}

[[nodiscard]] bool DirIterator::fail() const
{
    return static_cast<bool>(ec_);
}

[[nodiscard]] fs::path DirIterator::dirPath() const
{
    return dir_path_;
}

void DirIterator::reset()
{
    ec_.clear();
    dir_it_ = fs::recursive_directory_iterator(dir_path_, ec_);

    if (fail())
    {
        throw fs::filesystem_error(
            "DirIterator::reset: Failed To Reset Directory Iterator For Directory \"" + dirPath().string() + "\"", ec_);
    }
}
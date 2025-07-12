#include "file_reader.hpp"

FileReader::FileReader(const fs::path &file_path) : FileManip(file_path, {std::ios_base::in})
{
}

void FileReader::seekg(const size_t pos)
{
    file_stream_.seekg(static_cast<long>(pos));
    if (fail())
    {
        throw std::ios_base::failure(
            "FileReader::seekg: Failed To Set Read Position In File \"" + filePath().string() + "\"");
    }
}

[[nodiscard]] size_t FileReader::tellg()
{
    long pos = file_stream_.tellg();
    if (fail() || pos < 0)
    {
        throw std::ios_base::failure(
            "FileReader::tellg: Failed To Get Read Position In File >" + filePath().string() + "\"");
    }

    return static_cast<size_t>(pos);
}

[[nodiscard]] std::optional<std::string> FileReader::readToString(const size_t string_size)
{
    std::string buff(string_size, '\0');
    file_stream_.read(buff.data(), string_size);

    if (fail() || file_stream_.gcount() != static_cast<long>(string_size))
    {
        if (!eof())
        {
            throw std::ios_base::failure(
                "FileReader::readToString: Failed To Read String From File \"" + filePath().string() + "\"");
        }
        return {};
    }

    return buff;
}

[[nodiscard]] std::optional<char> FileReader::readChar()
{
    char c = '\0';
    file_stream_.get(c);

    if (fail())
    {
        if (!eof())
        {
            throw std::ios_base::failure(
                "FileReader::readChar: Failed To Read Char From File \"" + filePath().string() + "\"");
        }
        return {};
    }
    return c;
}
#include "roll_str.hpp"

#include <stdexcept>

RollStr::RollStr(std::string str) : str_(std::move(str)), begin_offset_(0)
{
}

RollStr &RollStr::operator=(std::string str)
{
    str_ = std::move(str);
    begin_offset_ = 0;

    return *this;
}

RollStr::operator std::string() const
{
    std::string buff(size(), '\0');

    for (size_t i = 0; i < size(); ++i)
    {
        buff[i] = (*this)[i];
    }

    return buff;
}

void RollStr::roll_forward(const char new_char)
{
    if (empty())
    {
        return;
    }

    (*this)[0] = new_char;
    begin_offset_ = (begin_offset_ + 1) % size();
}

[[nodiscard]] const char &RollStr::atImpl(const size_t idx) const
{
    if (idx >= size())
    {
        throw std::out_of_range(
            "RollStr::operator[]: Failed To Access Field Of RollStr. Index Is Out Of Range");
    }

    const size_t real_idx = (idx + begin_offset_) % size();
    return str_[real_idx];
}

[[nodiscard]] char &RollStr::operator[](const size_t idx)
{
    return const_cast<char &>(atImpl(idx));
}

[[nodiscard]] const char &RollStr::operator[](const size_t idx) const
{
    return atImpl(idx);
}

[[nodiscard]] size_t RollStr::size() const
{
    return str_.size();
}

[[nodiscard]] bool RollStr::empty() const
{
    return str_.empty();
}

std::ostream &operator<<(std::ostream &os, const RollStr &roll_str)
{
    for (size_t i = 0; i < roll_str.size(); ++i)
    {
        os << roll_str[i];
    }

    return os;
}

[[nodiscard]] bool RollStr::operator==(const std::string &rhs) const
{
    if (size() != rhs.size())
    {
        return false;
    }

    for (size_t i = 0; i < size(); ++i)
    {
        if ((*this)[i] != rhs[i])
        {
            return false;
        }
    }

    return true;
}

[[nodiscard]] bool RollStr::operator==(const RollStr &rhs) const
{
    if (size() != rhs.size())
    {
        return false;
    }

    for (size_t i = 0; i < size(); ++i)
    {
        if ((*this)[i] != rhs[i])
        {
            return false;
        }
    }

    return true;
}
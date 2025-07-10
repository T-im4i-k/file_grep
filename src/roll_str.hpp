#pragma once

#include <string>
#include <iostream>

class RollStr
{
public:
    explicit RollStr(std::string str = "");

    RollStr &operator=(std::string str);

    explicit operator std::string() const;

    void roll_forward(const char new_char);

    [[nodiscard]] char &operator[](const size_t idx);

    [[nodiscard]] const char &operator[](const size_t idx) const;

    [[nodiscard]] size_t size() const;

    [[nodiscard]] bool empty() const;

    friend std::ostream &operator<<(std::ostream &os, const RollStr &roll_str);

private:
    [[nodiscard]] const char &atImpl(const size_t idx) const;

    std::string str_;
    size_t begin_offset_;
};

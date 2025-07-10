#pragma once

#include "../string_utils/roll_str.hpp"

#include <string>

class RollStrHash
{
public:
    static constexpr size_t DEFAULT_BASE = 257;
    static constexpr size_t DEFAULT_MOD = 1'000'000'007;

    explicit RollStrHash(size_t mod = DEFAULT_MOD, size_t base = DEFAULT_BASE);

    void init(std::string str);

    void init(RollStr roll_str);

    void roll(const char new_char);

    [[nodiscard]] size_t getHash() const;

private:
    RollStr roll_str_;

    size_t mod_;
    size_t base_;
    size_t base_pow_ = 1;

    size_t curr_hash_ = 0;
};
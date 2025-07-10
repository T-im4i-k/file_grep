#include "roll_str_hash.hpp"

RollStrHash::RollStrHash(size_t mod, size_t base) : mod_(mod), base_(base)
{
    if (mod_ == 0)
    {
        throw std::invalid_argument(
            "RollStrHash::RollStrHash: \"mod\" Argument Cannot Be Equal To 0");
    }
}

void RollStrHash::init(std::string str)
{
    init(RollStr(std::move(str)));
}

void RollStrHash::init(RollStr roll_str)
{
    roll_str_ = std::move(roll_str);
    curr_hash_ = 0;
    base_pow_ = 1;

    for (size_t i = 0; i < roll_str_.size(); ++i)
    {
        curr_hash_ = (curr_hash_ * base_ + roll_str_[i]) % mod_;
        base_pow_ = (base_pow_ * base_) % mod_;
    }
}

void RollStrHash::roll(const char new_char)
{
    if (roll_str_.empty())
    {
        return;
    }

    curr_hash_ = (curr_hash_ + mod_ - (base_pow_ * roll_str_[0]) % mod_) % mod_;
    curr_hash_ = (curr_hash_ * base_ + new_char) % mod_;

    roll_str_.roll_forward(new_char);
}

[[nodiscard]] size_t RollStrHash::getHash() const
{
    return curr_hash_;
}
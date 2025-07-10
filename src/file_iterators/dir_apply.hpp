#pragma once

#include "dir_iterator.hpp"
#include "../helper/predicates.hpp"

#include <filesystem>
#include <concepts>
#include <utility>

namespace fs = std::filesystem;

template <typename Fun, typename... Args>
concept CallableTrait = requires {
    { std::declval<Fun>()(std::declval<Args>()...) };
};

template <typename Pred, typename... Args>
concept PredicateTrait = requires {
    { std::declval<Pred>()(std::declval<Args>()...) } -> std::same_as<bool>;
};

template <typename Fun, typename Pred = Tautology>
    requires CallableTrait<Fun, const fs::directory_entry &> &&
             PredicateTrait<Pred, const fs::directory_entry &>
class DirApply
{
public:
    DirApply(Fun fun = {}, Pred pred = {}) : fun_(std::move(fun)), pred_(std::move(pred))
    {
    }

    void apply(const fs::path &dir_path)
    {
        DirIterator dir_it(dir_path);
        apply(dir_it);
    }

    void apply(DirIterator &dir_it)
    {
        for (; !dir_it.end(); dir_it.next())
        {
            if (pred_(dir_it.curr()))
            {
                fun_(dir_it.curr());
            }
        }
    }

private:
    Fun fun_;
    Pred pred_;
};
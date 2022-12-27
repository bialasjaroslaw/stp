#pragma once

#include "common.hpp"
#include "join.hpp"
#include "split.hpp"

namespace Text {
constexpr int all = -1;

template <typename TextT, typename NeedleSrc, typename ReplaceSrc, typename NeedleT = container_type_t<NeedleSrc>,
          typename ReplaceT = container_type_t<ReplaceSrc>,
          std::enable_if_t<std::is_same_v<TextT, NeedleT> && std::is_same_v<TextT, ReplaceT>, int> = 0>
int replace(std::basic_string<TextT>& t, const NeedleSrc& n, const ReplaceSrc& r, int start = 0, int end = -1)
{
    if (sanitize_index(start, t.length()) == npos || sanitize_index(end, t.length()) == npos)
        return npos;
    auto splitted = split(t, n, SplitBehavior::KeepEmpty, start, end);
    auto operations = splitted.size() - 1;
    t = join(splitted, r);
    return operations;
}

template <typename TextT, typename Predicate, typename ReplaceSrc, typename ReplaceT = container_type_t<ReplaceSrc>,
          std::enable_if_t<std::is_same_v<TextT, ReplaceT>, int> = 0>
int replace_if(std::basic_string<TextT>& t, Predicate pred, const ReplaceSrc& r, int start = 0, int end = -1)
{
    if (sanitize_index(start, t.length()) == npos || sanitize_index(end, t.length()) == npos)
        return npos;
    auto splitted = split_if(t, pred, SplitBehavior::KeepEmpty, start, end);
    auto operations = splitted.size() - 1;
    t = join(splitted, r);
    return operations;
}

template <typename TextT, typename NeedleSrc, typename ReplaceSrc, typename NeedleT = container_type_t<NeedleSrc>,
          typename ReplaceT = container_type_t<ReplaceSrc>,
          std::enable_if_t<std::is_same_v<TextT, NeedleT> && std::is_same_v<TextT, ReplaceT>, int> = 0>
int replace_any(std::basic_string<TextT>& t, const NeedleSrc& d, const ReplaceSrc& r, int start = 0, int end = -1)
{
    if (sanitize_index(start, t.length()) == npos || sanitize_index(end, t.length()) == npos)
        return npos;
    auto splitted = split_any(t, d, SplitBehavior::KeepEmpty, start, end);
    auto operations = splitted.size() - 1;
    t = join(splitted, r);
    return operations;
}
} // namespace Text
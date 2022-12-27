#pragma once

#include "common.hpp"
#include "join.hpp"
#include "split.hpp"

namespace Text {
template <typename TextSrc, typename NeedleSrc, typename TextT = container_type_t<TextSrc>,
          typename NeedleT = container_type_t<NeedleSrc>, std::enable_if_t<std::is_same_v<TextT, NeedleT>, int> = 0>
int remove_impl(TextSrc& t, const NeedleSrc& n, int start = 0, int end = -1)
{
    Text txt(t);
    if (sanitize_index(start, txt.length) == npos || sanitize_index(end, txt.length) == npos)
        return npos;
    auto splitted = split(t, n, SplitBehavior::KeepEmpty, start, end);
    auto operations = splitted.size() - 1;
    t = join(splitted, std::basic_string_view<TextT>{});
    return operations;
}

template <typename TextSrc, typename NeedleSrc, typename TextT = container_type_t<TextSrc>,
          typename NeedleT = container_type_t<NeedleSrc>, std::enable_if_t<std::is_same_v<TextT, NeedleT>, int> = 0>
int remove(TextSrc& t, const NeedleSrc& n, int start = 0)
{
    return remove_impl(t, n, start);
}

template <typename TextSrc, typename Predicate, typename TextT = container_type_t<TextSrc>>
int remove_if_impl(TextSrc& t, Predicate pred, int start = 0, int end = -1)
{
    Text txt(t);
    if (sanitize_index(start, txt.length) == npos || sanitize_index(end, txt.length) == npos)
        return npos;
    auto splitted = split_if(t, pred, SplitBehavior::KeepEmpty, start, end);
    auto operations = splitted.size() - 1;
    t = join(splitted, std::basic_string_view<TextT>{});
    return operations;
}

template <typename TextSrc, typename Predicate, typename TextT = container_type_t<TextSrc>>
int remove_if(TextSrc& t, Predicate pred, int start = 0)
{
    return remove_if_impl(t, pred, start);
}

template <typename TextSrc, typename Predicate, typename TextT = container_type_t<TextSrc>>
int rremove_if(TextSrc& t, Predicate pred, int start = 0)
{
    return remove_if_impl(t, pred, 0, -start - 1);
}

template <typename TextSrc, typename NeedleSrc, typename TextT = container_type_t<TextSrc>,
          typename NeedleT = container_type_t<NeedleSrc>, std::enable_if_t<std::is_same_v<TextT, NeedleT>, int> = 0>
int rremove(TextSrc& t, const NeedleSrc& n, int start = 0)
{
    return remove_impl(t, n, 0, -start - 1);
}

template <typename TextSrc, typename NeedleSrc, typename TextT = container_type_t<TextSrc>,
          typename NeedleT = container_type_t<NeedleSrc>, std::enable_if_t<std::is_same_v<TextT, NeedleT>, int> = 0>
int remove_any_impl(TextSrc& t, const NeedleSrc& d, int start = 0, int end = -1)
{
    Text txt(t);
    if (sanitize_index(start, txt.length) == npos || sanitize_index(end, txt.length) == npos)
        return npos;
    auto splitted = split_any(t, d, SplitBehavior::KeepEmpty, start, end);
    auto operations = splitted.size() - 1;
    t = join(splitted, std::basic_string_view<TextT>{});
    return operations;
}

template <typename TextSrc, typename NeedleSrc, typename TextT = container_type_t<TextSrc>,
          typename NeedleT = container_type_t<NeedleSrc>, std::enable_if_t<std::is_same_v<TextT, NeedleT>, int> = 0>
int remove_any(TextSrc& t, const NeedleSrc& d, int start = 0)
{
    return remove_any_impl(t, d, start);
}

template <typename TextSrc, typename NeedleSrc, typename TextT = container_type_t<TextSrc>,
          typename NeedleT = container_type_t<NeedleSrc>, std::enable_if_t<std::is_same_v<TextT, NeedleT>, int> = 0>
int rremove_any(TextSrc& t, const NeedleSrc& d, int start = 0)
{
    return remove_any_impl(t, d, 0, -start - 1);
}

} // namespace Text
#pragma once

#include "common.hpp"
#include "find.hpp"
#include "sub.hpp"

namespace Text {
template <typename TextSrc, typename NeedleSrc, typename TextT = container_type_t<TextSrc>,
          typename NeedleT = container_type_t<NeedleSrc>, std::enable_if_t<std::is_same_v<TextT, NeedleT>, int> = 0>
int count(const TextSrc& t, const NeedleSrc& n, int start = Start, int end = End)
{
    int cnt = 0;
    --start;
    while((start = find(left_view(t, end), n, start + 1)) != End)
        ++cnt;
    return cnt;
}

template <typename TextSrc, typename Predicate, typename TextT = container_type_t<TextSrc>>
int count_if(const TextSrc& t, Predicate pred, int start = Start, int end = End)
{
    int cnt = 0;
    --start;
    while((start = find_if(left_view(t, end), pred, start + 1)) != End)
        ++cnt;
    return cnt;
}

template <typename TextSrc, typename NeedleSrc, typename TextT = container_type_t<TextSrc>,
          typename NeedleT = container_type_t<NeedleSrc>, std::enable_if_t<std::is_same_v<TextT, NeedleT>, int> = 0>
int count_any(const TextSrc& t, const NeedleSrc& d, int start = Start, int end = End)
{
    int cnt = 0;
    --start;
    while((start = find_any(left_view(t, end), d, start + 1)) != End)
        ++cnt;
    return cnt;
}

} // namespace Text
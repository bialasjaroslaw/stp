#pragma once

#include "common.hpp"
#include "find.hpp"
#include "sub.hpp"

namespace Text {
template <typename TextSrc, typename NeedleSrc>
    requires CanBeDelimiterOf<NeedleSrc, TextSrc>
int count(const TextSrc& t, const NeedleSrc& n, int start = Start, int end = End, int step = Step,
          Case sensitivity = Case::Sensitive)
{
    int cnt = 0;
    start -= step;
    while ((start = find(t, n, start + step, end, step, sensitivity)) != End)
        ++cnt;
    return cnt;
}

template <typename TextSrc, typename Predicate>
int count_if(const TextSrc& t, Predicate pred, int start = Start, int end = End, int step = Step)
{
    int cnt = 0;
    start -= step;
    while ((start = find_if(t, pred, start + step, end, step)) != End)
        ++cnt;
    return cnt;
}

template <typename TextSrc, typename NeedleSrc>
    requires CanBeDelimiterOf<NeedleSrc, TextSrc>
int count_any(const TextSrc& t, const NeedleSrc& d, int start = Start, int end = End, int step = Step,
              Case sensitivity = Case::Sensitive)
{
    int cnt = 0;
    start -= step;
    while ((start = find_any(t, d, start + step, end, step, sensitivity)) != End)
        ++cnt;
    return cnt;
}

} // namespace Text
#pragma once

#include "common.hpp"

namespace Text {
template <typename TextSrc, typename NeedleSrc>
    requires CanBeDelimiterOf<NeedleSrc, TextSrc> && std::equality_comparable<container_type_t<TextSrc>>
int find_impl(const TextSrc& t, const NeedleSrc& n, int start, int end, int step, Case sensitivity)
{
    if (step == 0)
        return End;

    Text text(t);
    Delimiter needle(n);

    if (needle.length == 0)
        return End;

    if (sanitize_index(start, text.length) == End || sanitize_index(end, text.length) == End)
        return End;

    auto current = step < 0 ? text.ptr + end - needle.length : text.ptr + start;
    while (current + needle.length <= text.ptr + end && current >= text.ptr)
    {
        if (!are_equal(current, needle.ptr, needle.length, sensitivity))
        {
            current += step;
            continue;
        }
        return static_cast<int>(current - text.ptr);
    }
    return End;
}

template <typename TextSrc, typename NeedleSrc>
    requires CanBeDelimiterOf<NeedleSrc, TextSrc>
int find(const TextSrc& t, const NeedleSrc& n, int start = Start, int end = End, int step = Step,
         Case sensitivity = Case::Sensitive)
{
    return find_impl(t, n, start, end, step, sensitivity);
}

template <typename TextSrc, typename NeedleSrc>
    requires CanBeDelimiterOf<NeedleSrc, TextSrc>
int rfind(const TextSrc& t, const NeedleSrc& n, int start = Start, int end = End, int step = Step,
          Case sensitivity = Case::Sensitive)
{
    return find_impl(t, n, start, end, -step, sensitivity);
}

template <typename TextSrc, typename Predicate>
int find_if_impl(const TextSrc& t, Predicate pred, int start, int end, int step)
{
    if (step == 0)
        return End;

    Text text(t);

    if (sanitize_index(start, text.length) == End || sanitize_index(end, text.length) == End)
        return End;

    auto current = step < 0 ? text.ptr + end - 1 : text.ptr + start;
    while (current < text.ptr + text.length && current >= text.ptr)
    {
        if (!pred(*current))
        {
            current += step;
            continue;
        }
        return static_cast<int>(current - text.ptr);
    }
    return End;
}

template <typename TextSrc, typename Predicate>
int find_if(const TextSrc& t, Predicate pred, int start = Start, int end = End, int step = Step)
{
    return find_if_impl(t, pred, start, end, step);
}

template <typename TextSrc, typename Predicate>
int rfind_if(const TextSrc& t, Predicate pred, int start = Start, int end = End, int step = Step)
{
    return find_if_impl(t, pred, start, end, -step);
}

template <typename TextSrc, typename NeedleSrc>
    requires CanBeDelimiterOf<NeedleSrc, TextSrc>
int find_any_impl(const TextSrc& t, const NeedleSrc& d, int start, int end, int step, Case sensitivity)
{
    if (step == 0)
        return End;

    Text text(t);
    Delimiters delimiters(d, sensitivity);

    if (sanitize_index(start, text.length) == End || sanitize_index(end, text.length) == End)
        return End;

    auto current = step < 0 ? text.ptr + end - 1 : text.ptr + start;
    while (current < text.ptr + text.length && current >= text.ptr)
    {
        if (!delimiters.contains(*current, sensitivity))
        {
            current += step;
            continue;
        }
        return static_cast<int>(current - text.ptr);
    }
    return End;
}

template <typename TextSrc, typename NeedleSrc>
    requires CanBeDelimiterOf<NeedleSrc, TextSrc>
int find_any(const TextSrc& t, const NeedleSrc& d, int start = Start, int end = End, int step = Step,
             Case sensitivity = Case::Sensitive)
{
    return find_any_impl(t, d, start, end, step, sensitivity);
}

template <typename TextSrc, typename NeedleSrc>
    requires CanBeDelimiterOf<NeedleSrc, TextSrc>
int rfind_any(const TextSrc& t, const NeedleSrc& d, int start = Start, int end = End, int step = Step,
              Case sensitivity = Case::Sensitive)
{
    return find_any_impl(t, d, start, end, -step, sensitivity);
}

} // namespace Text
#pragma once

#include "common.hpp"

namespace Text {
template <typename TextSrc, typename NeedleSrc, typename TextT = container_type_t<TextSrc>,
          typename NeedleT = container_type_t<NeedleSrc>, std::enable_if_t<std::is_same_v<TextT, NeedleT>, int> = 0>
int find_impl(const TextSrc& t, const NeedleSrc& n, int start = 0, int step = 1)
{
    if (step == 0)
        return npos;

    Text text(t);
    Delimiter needle(n);

    if (needle.length == 0)
        return npos;

    auto current = text.ptr + start;

    while (current + needle.length <= text.ptr + text.length && current >= text.ptr)
    {
        if (!are_equal(current, needle.ptr, needle.length))
        {
            current += step;
            continue;
        }
        return static_cast<int>(current - text.ptr);
    }
    return npos;
}

template <typename TextSrc, typename NeedleSrc, typename TextT = container_type_t<TextSrc>,
          typename NeedleT = container_type_t<NeedleSrc>, std::enable_if_t<std::is_same_v<TextT, NeedleT>, int> = 0>
int find(const TextSrc& t, const NeedleSrc& n, int start = 0, int step = 1)
{
    Text text(t);
    if (sanitize_index(start, text.length) == npos)
        return npos;
    return find_impl(t, n, start, step);
}

template <typename TextSrc, typename NeedleSrc, typename TextT = container_type_t<TextSrc>,
          typename NeedleT = container_type_t<NeedleSrc>, std::enable_if_t<std::is_same_v<TextT, NeedleT>, int> = 0>
int rfind(const TextSrc& t, const NeedleSrc& n, int start = 0, int step = 1)
{
    Text text(t);
    Delimiter needle(n);
    if (sanitize_index(start, text.length) == npos)
        return npos;
    start = std::max(start, static_cast<int>(needle.length - 1));
    return find_impl(t, n, static_cast<int>(text.length - start - 1), -step);
}

template <typename TextSrc, typename Predicate, typename TextT = container_type_t<TextSrc>>
int find_if_impl(const TextSrc& t, Predicate pred, int start = 0, int step = 1)
{
    if (step == 0)
        return npos;

    Text text(t);

    auto current = text.ptr + start;

    while (current < text.ptr + text.length && current >= text.ptr)
    {
        if (!pred(*current))
        {
            current += step;
            continue;
        }
        return static_cast<int>(current - text.ptr);
    }
    return npos;
}

template <typename TextSrc, typename Predicate, typename TextT = container_type_t<TextSrc>>
int find_if(const TextSrc& t, Predicate pred, int start = 0, int step = 1)
{
    Text text(t);
    if (sanitize_index(start, text.length) == npos)
        return npos;
    return find_if_impl(t, pred, start, step);
}

template <typename TextSrc, typename Predicate, typename TextT = container_type_t<TextSrc>>
int rfind_if(const TextSrc& t, Predicate pred, int start = 0, int step = 1)
{
    Text text(t);
    if (sanitize_index(start, text.length) == npos)
        return npos;
    return find_if_impl(t, pred, static_cast<int>(text.length - start - 1), -step);
}

template <typename TextSrc, typename NeedleSrc, typename TextT = container_type_t<TextSrc>,
          typename NeedleT = container_type_t<NeedleSrc>, std::enable_if_t<std::is_same_v<TextT, NeedleT>, int> = 0>
int find_any_impl(const TextSrc& t, const NeedleSrc& d, int start = 0, int step = 1)
{
    if (step == 0)
        return npos;

    Text text(t);
    Delimiters delimiters(d);

    auto current = text.ptr + start;

    while (current < text.ptr + text.length && current >= text.ptr)
    {
        if (!delimiters.contains(*current))
        {
            current += step;
            continue;
        }
        return static_cast<int>(current - text.ptr);
    }
    return npos;
}

template <typename TextSrc, typename NeedleSrc, typename TextT = container_type_t<TextSrc>,
          typename NeedleT = container_type_t<NeedleSrc>, std::enable_if_t<std::is_same_v<TextT, NeedleT>, int> = 0>
int find_any(const TextSrc& t, const NeedleSrc& d, int start = 0, int step = 1)
{
    Text text(t);
    if (sanitize_index(start, text.length) == npos)
        return npos;
    return find_any_impl(t, d, start, step);
}

template <typename TextSrc, typename NeedleSrc, typename TextT = container_type_t<TextSrc>,
          typename NeedleT = container_type_t<NeedleSrc>, std::enable_if_t<std::is_same_v<TextT, NeedleT>, int> = 0>
int rfind_any(const TextSrc& t, const NeedleSrc& d, int start = 0, int step = 1)
{
    Text text(t);
    if (sanitize_index(start, text.length) == npos)
        return npos;
    return find_any_impl(t, d, static_cast<int>(text.length - start - 1), -step);
}

} // namespace Text
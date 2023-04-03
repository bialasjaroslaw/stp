#pragma once

#include "common.hpp"

namespace Text {

enum class SplitBehavior
{
    KeepEmpty,
    DropEmpty
};

template <typename TextSrc, typename DelimSrc, typename TextT = container_type_t<TextSrc>,
          typename DelimT = container_type_t<DelimSrc>, std::enable_if_t<std::is_same_v<TextT, DelimT>, int> = 0>
auto split(const TextSrc& t, const DelimSrc& d, SplitBehavior beh = SplitBehavior::KeepEmpty, int start = 0,
           int end = -1)
{
    Text text(t);
    Delimiter delimiter(d);
    std::vector<std::basic_string_view<TextT>> results;

    if (text.length == 0)
        return results;

    if (delimiter.length == 0)
    {
        results.reserve(text.length);
        for (size_t idx = 0; idx < text.length; ++idx)
            results.emplace_back(text.ptr + idx, 1);
        return results;
    }

    if (sanitize_index(start, text.length) == npos || sanitize_index(end, text.length) == npos)
    {
        results.emplace_back(text.ptr, text.length);
        return results;
    }

    auto start_ptr = text.ptr;
    auto current = text.ptr + start;

    while (current + delimiter.length <= text.ptr + end + 1)
    {
        if (!are_equal(current, delimiter.ptr, delimiter.length))
        {
            ++current;
            continue;
        }
        if (start_ptr != current || beh == SplitBehavior::KeepEmpty)
            results.emplace_back(start_ptr, current - start_ptr);
        current += std::max(delimiter.length, size_t{1});
        start_ptr = current;
    }
    if (start_ptr != current || beh == SplitBehavior::KeepEmpty)
        results.emplace_back(start_ptr, text.ptr + text.length - start_ptr);
    return results;
}

template <typename TextSrc, typename DelimSrc, typename TextT = container_type_t<TextSrc>,
          typename DelimT = container_type_t<DelimSrc>, std::enable_if_t<std::is_same_v<TextT, DelimT>, int> = 0>
auto split_any(const TextSrc& t, const DelimSrc& d, SplitBehavior beh = SplitBehavior::KeepEmpty, int start = 0,
               int end = -1)
{
    Text text(t);
    Delimiters delimiters(d);
    std::vector<std::basic_string_view<TextT>> results;

    if (text.length == 0)
        return results;

    if (sanitize_index(start, text.length) == npos || sanitize_index(end, text.length) == npos)
    {
        results.emplace_back(text.ptr, text.length);
        return results;
    }

    auto start_ptr = text.ptr;
    auto current = text.ptr + start;

    while (current <= text.ptr + end)
    {
        if (!delimiters.contains(*current))
        {
            ++current;
            continue;
        }
        if (start_ptr != current || beh == SplitBehavior::KeepEmpty)
            results.emplace_back(start_ptr, current - start_ptr);
        ++current;
        start_ptr = current;
    }
    if (start_ptr != current || beh == SplitBehavior::KeepEmpty)
        results.emplace_back(start_ptr, text.ptr + text.length - start_ptr);
    return results;
}

template <typename TextSrc, typename Predicate, typename TextT = container_type_t<TextSrc>>
auto split_if(const TextSrc& t, Predicate pred, SplitBehavior beh = SplitBehavior::KeepEmpty, int start = 0,
              int end = -1)
{
    Text text(t);
    std::vector<std::basic_string_view<TextT>> results;

    if (text.length == 0)
        return results;

    if (sanitize_index(start, text.length) == npos || sanitize_index(end, text.length) == npos)
    {
        results.emplace_back(text.ptr, text.length);
        return results;
    }

    auto start_ptr = text.ptr;
    auto current = text.ptr + start;

    while (current < text.ptr + end)
    {
        if (!pred(*current))
        {
            ++current;
            continue;
        }
        if (start_ptr != current || beh == SplitBehavior::KeepEmpty)
            results.emplace_back(start_ptr, current - start_ptr);
        ++current;
        start_ptr = current;
    }
    if (start_ptr != current || beh == SplitBehavior::KeepEmpty)
        results.emplace_back(start_ptr, text.ptr + text.length - start_ptr);
    return results;
}
} // namespace Text

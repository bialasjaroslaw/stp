#pragma once

#include "common.hpp"

namespace Text {

enum class SplitBehavior
{
    KeepEmpty,
    DropEmpty
};

template <typename TextSrc, typename DelimSrc>
    requires CanBeDelimiterOf<DelimSrc, TextSrc>
auto split(const TextSrc& t, const DelimSrc& d, SplitBehavior beh = SplitBehavior::KeepEmpty, int start = Start,
           int end = End, int step = Step, Case sensitivity = Case::Sensitive)
{
    Text text(t);
    Delimiter delimiter(d);
    std::vector<std::basic_string_view<container_type_t<TextSrc>>> results;

    if (text.length == 0 || step <= 0)
        return results;
    auto unsigned_step = static_cast<unsigned int>(step);

    if (sanitize_index(start, text.length) == End || sanitize_index(end, text.length) == End)
    {
        results.emplace_back(text.ptr, text.length);
        return results;
    }

    if (delimiter.length == 0)
    {
        results.reserve((text.length + unsigned_step - 1) / unsigned_step);
        for (; start < end; start += step)
            results.emplace_back(text.ptr + start, std::min(end - start, step));
        return results;
    }

    auto start_ptr = text.ptr;
    auto current = start_ptr + start;
    auto skip_after_match = unsigned_step;
    while (skip_after_match < delimiter.length)
        skip_after_match += unsigned_step;

    while (current + delimiter.length <= text.ptr + end)
    {
        if (!are_equal(current, delimiter.ptr, delimiter.length, sensitivity))
        {
            current += step;
            continue;
        }
        if (start_ptr != current || beh == SplitBehavior::KeepEmpty)
            results.emplace_back(start_ptr, current - start_ptr);
        start_ptr = current + delimiter.length;
        current += skip_after_match;
    }
    current = std::min(current, text.ptr + end);
    start_ptr = std::min(start_ptr, text.ptr + end);
    if (start_ptr != current || beh == SplitBehavior::KeepEmpty)
        results.emplace_back(start_ptr, text.ptr + text.length - start_ptr);
    return results;
}

template <typename TextSrc, typename DelimSrc>
    requires CanBeDelimiterOf<DelimSrc, TextSrc>
auto split_any(const TextSrc& t, const DelimSrc& d, SplitBehavior beh = SplitBehavior::KeepEmpty, int start = Start,
               int end = End, int step = Step, Case sensitivity = Case::Sensitive)
{
    Text text(t);
    Delimiters delimiters(d, sensitivity);
    std::vector<std::basic_string_view<container_type_t<TextSrc>>> results;

    if (text.length == 0 || step <= 0)
        return results;

    if (sanitize_index(start, text.length) == End || sanitize_index(end, text.length) == End)
    {
        results.emplace_back(text.ptr, text.length);
        return results;
    }

    auto start_ptr = text.ptr;
    auto current = start_ptr + start;

    while (current < text.ptr + end)
    {
        if (!delimiters.contains(*current, sensitivity))
        {
            current += step;
            continue;
        }
        if (start_ptr != current || beh == SplitBehavior::KeepEmpty)
            results.emplace_back(start_ptr, current - start_ptr);
        start_ptr = current + 1;
        current += step;
    }
    current = std::min(current, text.ptr + end);
    start_ptr = std::min(start_ptr, text.ptr + end);
    if (start_ptr != current || beh == SplitBehavior::KeepEmpty)
        results.emplace_back(start_ptr, text.ptr + text.length - start_ptr);
    return results;
}

template <typename TextSrc, typename Predicate>
auto split_if(const TextSrc& t, Predicate pred, SplitBehavior beh = SplitBehavior::KeepEmpty, int start = Start,
              int end = End, int step = Step)
{
    Text text(t);
    std::vector<std::basic_string_view<container_type_t<TextSrc>>> results;

    if (text.length == 0 || step <= 0)
        return results;

    if (sanitize_index(start, text.length) == End || sanitize_index(end, text.length) == End)
    {
        results.emplace_back(text.ptr, text.length);
        return results;
    }

    auto start_ptr = text.ptr;
    auto current = start_ptr + start;

    while (current < text.ptr + end)
    {
        if (!pred(*current))
        {
            current += step;
            continue;
        }
        if (start_ptr != current || beh == SplitBehavior::KeepEmpty)
            results.emplace_back(start_ptr, current - start_ptr);
        start_ptr = current + 1;
        current += step;
    }
    current = std::min(current, text.ptr + end);
    start_ptr = std::min(start_ptr, text.ptr + end);
    if (start_ptr != current || beh == SplitBehavior::KeepEmpty)
        results.emplace_back(start_ptr, text.ptr + text.length - start_ptr);
    return results;
}
} // namespace Text

#pragma once

#include "common.hpp"
#include "join.hpp"
#include "split.hpp"

namespace Text {
constexpr int all = -1;

template <typename T>
struct ReplaceResult
{
    std::basic_string<T> text;
    int operations = 0;
};

template <typename TextSrc, typename NeedleSrc, typename ReplaceSrc, typename TextT = container_type_t<TextSrc>>
    requires CanBeDelimiterOf<NeedleSrc, TextSrc> &&
             SameDataType<NeedleSrc, ReplaceSrc>
             auto replace_impl(const TextSrc& t, const NeedleSrc& n, const ReplaceSrc& r, int start, int end, int step,
                               Case sensitivity) -> ReplaceResult<TextT>
{
    if (sanitize_index(start, t.length()) == End || sanitize_index(end, t.length()) == End)
        return {std::basic_string(t)};
    auto splitted = split(t, n, SplitBehavior::KeepEmpty, start, end, step, sensitivity);
    return {join(splitted, r), static_cast<int>(splitted.size()) - 1};
}

template <typename TextT, typename NeedleSrc, typename ReplaceSrc>
    requires CanBeDelimiterOf<NeedleSrc, TextT> && SameDataType<NeedleSrc, ReplaceSrc>
int replace(std::basic_string<TextT>& t, const NeedleSrc& n, const ReplaceSrc& r, int start = Start, int end = End,
            int step = Step, Case sensivity = Case::Insensitive)
{
    auto result = replace_impl(t, n, r, start, end, step, sensivity);
    t = std::move(result.text);
    return result.operations;
}

template <typename TextSrc, typename NeedleSrc, typename ReplaceSrc, typename TextT = container_type_t<TextSrc>>
    requires CanBeDelimiterOf<NeedleSrc, TextSrc> &&
             SameDataType<NeedleSrc, ReplaceSrc>
             auto replaced(const TextSrc& t, const NeedleSrc& n, const ReplaceSrc& r, int start = Start, int end = End,
                           int step = Step, Case sensitivity = Case::Sensitive) -> std::basic_string<TextT>
{
    return replace_impl(t, n, r, start, end, step, sensitivity).text;
}

template <typename TextSrc, typename Predicate, typename ReplaceSrc, typename TextT = container_type_t<TextSrc>>
    requires SameDataType<TextSrc, ReplaceSrc>
auto replace_if_impl(const TextSrc& t, Predicate pred, const ReplaceSrc& r, int start, int end, int step)
    -> ReplaceResult<TextT>
{
    if (sanitize_index(start, t.length()) == End || sanitize_index(end, t.length()) == End)
        return {std::basic_string(t)};
    auto splitted = split_if(t, pred, SplitBehavior::KeepEmpty, start, end, step);
    return {join(splitted, r), static_cast<int>(splitted.size()) - 1};
}

template <typename TextT, typename Predicate, typename ReplaceSrc>
    requires SameDataType<TextT, ReplaceSrc>
int replace_if(std::basic_string<TextT>& t, Predicate pred, const ReplaceSrc& r, int start = Start, int end = End,
               int step = Step)
{
    auto result = replace_if_impl(t, pred, r, start, end, step);
    t = std::move(result.text);
    return result.operations;
}

template <typename TextSrc, typename Predicate, typename ReplaceSrc, typename TextT = container_type_t<TextSrc>>
    requires SameDataType<TextSrc, ReplaceSrc>
auto replaced_if(const TextSrc& t, Predicate pred, const ReplaceSrc& r, int start = Start, int end = End,
                 int step = Step) -> std::basic_string<TextT>
{
    return replace_if_impl(t, pred, r, start, end, step).text;
}

template <typename TextSrc, typename NeedleSrc, typename ReplaceSrc, typename TextT = container_type_t<TextSrc>>
    requires CanBeDelimiterOf<NeedleSrc, TextSrc> &&
             SameDataType<NeedleSrc, ReplaceSrc>
             auto replace_any_impl(const TextSrc& t, const NeedleSrc& d, const ReplaceSrc& r, int start, int end,
                                   int step, Case sensitivity) -> ReplaceResult<TextT>
{
    if (sanitize_index(start, t.length()) == End || sanitize_index(end, t.length()) == End)
        return {std::basic_string(t)};
    auto splitted = split_any(t, d, SplitBehavior::KeepEmpty, start, end, step, sensitivity);
    return {join(splitted, r), static_cast<int>(splitted.size()) - 1};
}

template <typename TextT, typename NeedleSrc, typename ReplaceSrc>
    requires CanBeDelimiterOf<NeedleSrc, TextT> && SameDataType<NeedleSrc, ReplaceSrc>
int replace_any(std::basic_string<TextT>& t, const NeedleSrc& d, const ReplaceSrc& r, int start = Start, int end = End,
                int step = Step, Case sensitivity = Case::Sensitive)
{
    auto result = replace_any_impl(t, d, r, start, end, step, sensitivity);
    t = std::move(result.text);
    return result.operations;
}

template <typename TextSrc, typename NeedleSrc, typename ReplaceSrc, typename TextT = container_type_t<TextSrc>>
    requires CanBeDelimiterOf<NeedleSrc, TextSrc> &&
             SameDataType<NeedleSrc, ReplaceSrc>
             auto replaced_any(const TextSrc& t, const NeedleSrc& d, const ReplaceSrc& r, int start = Start,
                               int end = End, int step = Step, Case sensitivity = Case::Sensitive)
                 -> std::basic_string<TextT>
{
    return replace_any_impl(t, d, r, start, end, step, sensitivity).text;
}
} // namespace Text
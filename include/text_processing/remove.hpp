#pragma once

#include "common.hpp"
#include "join.hpp"
#include "split.hpp"

namespace Text {
template <typename T>
struct RemoveResult
{
    std::basic_string<T> text;
    int operations = 0;
};

template <typename TextSrc, typename NeedleSrc, typename TextT = container_type_t<TextSrc>>
    requires CanBeDelimiterOf<NeedleSrc, TextSrc>
auto remove_impl(const TextSrc& t, const NeedleSrc& n, int start, int end, int step, Case sensitivity)
    -> RemoveResult<TextT>
{
    Text txt(t);
    if (sanitize_index(start, txt.length) == End || sanitize_index(end, txt.length) == End)
        return {std::basic_string(t)};
    auto splitted = split(t, n, SplitBehavior::KeepEmpty, start, end, step, sensitivity);
    return {join(splitted, std::basic_string_view<TextT>{}), static_cast<int>(splitted.size()) - 1};
}

template <typename TextT, typename NeedleSrc>
    requires CanBeDelimiterOf<NeedleSrc, TextT>
int remove(std::basic_string<TextT>& t, const NeedleSrc& n, int start = Start, int end = End, int step = Step,
           Case sensitivity = Case::Sensitive)
{
    auto result = remove_impl(t, n, start, end, step, sensitivity);
    t = std::move(result.text);
    return result.operations;
}

template <typename TextSrc, typename NeedleSrc, typename TextT = container_type_t<TextSrc>>
    requires CanBeDelimiterOf<NeedleSrc, TextSrc>
[[nodiscard]] auto removed(const TextSrc& t, const NeedleSrc& n, int start = Start, int end = End, int step = Step,
                           Case sensitivity = Case::Sensitive) -> std::basic_string<TextT>
{
    return remove_impl(t, n, start, end, step, sensitivity).text;
}

template <typename TextSrc, typename Predicate, typename TextT = container_type_t<TextSrc>>
auto remove_if_impl(const TextSrc& t, Predicate pred, int start = Start, int end = End, int step = Step)
    -> RemoveResult<TextT>
{
    Text txt(t);
    if (sanitize_index(start, txt.length) == End || sanitize_index(end, txt.length) == End)
        return {std::basic_string(t)};
    auto splitted = split_if(t, pred, SplitBehavior::KeepEmpty, start, end, step);
    return {join(splitted, std::basic_string_view<TextT>{}), static_cast<int>(splitted.size()) - 1};
}

template <typename TextT, typename Predicate>
int remove_if(std::basic_string<TextT>& t, Predicate pred, int start = Start, int end = End, int step = Step)
{
    auto result = remove_if_impl(t, pred, start, end, step);
    t = std::move(result.text);
    return result.operations;
}

template <typename TextSrc, typename Predicate, typename TextT = container_type_t<TextSrc>>
[[nodiscard]] auto removed_if(const TextSrc& t, Predicate pred, int start = Start, int end = End, int step = Step)
    -> std::basic_string<TextT>
{
    return remove_if_impl(t, pred, start, end, step).text;
}

template <typename TextSrc, typename NeedleSrc, typename TextT = container_type_t<TextSrc>>
    requires CanBeDelimiterOf<NeedleSrc, TextSrc>
auto remove_any_impl(const TextSrc& t, const NeedleSrc& d, int start = Start, int end = End, int step = Step,
                     Case sensitivity = Case::Sensitive) -> RemoveResult<TextT>
{
    Text txt(t);
    if (sanitize_index(start, txt.length) == End || sanitize_index(end, txt.length) == End)
        return {std::basic_string(t)};
    auto splitted = split_any(t, d, SplitBehavior::KeepEmpty, start, end, step, sensitivity);
    return {join(splitted, std::basic_string_view<TextT>{}), static_cast<int>(splitted.size()) - 1};
}

template <typename TextT, typename NeedleSrc>
    requires CanBeDelimiterOf<NeedleSrc, TextT>
int remove_any(std::basic_string<TextT>& t, const NeedleSrc& d, int start = Start, int end = End, int step = Step,
               Case sensitivity = Case::Sensitive)
{
    auto result = remove_any_impl(t, d, start, end, step, sensitivity);
    t = std::move(result.text);
    return result.operations;
}

template <typename TextSrc, typename NeedleSrc, typename TextT = container_type_t<TextSrc>>
    requires CanBeDelimiterOf<NeedleSrc, TextSrc>
[[nodiscard]] auto removed_any(const TextSrc& t, const NeedleSrc& d, int start = Start, int end = End, int step = Step,
                               Case sensitivity = Case::Sensitive) -> std::basic_string<TextT>
{
    return remove_any_impl(t, d, start, end, step, sensitivity).text;
}

} // namespace Text
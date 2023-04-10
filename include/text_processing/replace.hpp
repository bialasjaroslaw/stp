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

template <typename TextSrc, typename NeedleSrc, typename ReplaceSrc, typename TextT = container_type_t<TextSrc>,
          typename NeedleT = container_type_t<NeedleSrc>, typename ReplaceT = container_type_t<ReplaceSrc>,
          std::enable_if_t<std::is_same_v<TextT, NeedleT> && std::is_same_v<TextT, ReplaceT>, int> = 0>
auto replace_impl(const TextSrc& t, const NeedleSrc& n, const ReplaceSrc& r, int start = Start, int end = End)
    -> ReplaceResult<TextT>
{
    if (sanitize_index(start, t.length()) == End || sanitize_index(end, t.length()) == End)
        return {std::basic_string(t)};
    auto splitted = split(t, n, SplitBehavior::KeepEmpty, start, end);
    return {join(splitted, r), static_cast<int>(splitted.size()) - 1};
}

template <typename TextT, typename NeedleSrc, typename ReplaceSrc, typename NeedleT = container_type_t<NeedleSrc>,
          typename ReplaceT = container_type_t<ReplaceSrc>,
          std::enable_if_t<std::is_same_v<TextT, NeedleT> && std::is_same_v<TextT, ReplaceT>, int> = 0>
int replace(std::basic_string<TextT>& t, const NeedleSrc& n, const ReplaceSrc& r, int start = Start, int end = End)
{
    auto result = replace_impl(t, n, r, start, end);
    t = std::move(result.text);
    return result.operations;
}

template <typename TextSrc, typename NeedleSrc, typename ReplaceSrc, typename TextT = container_type_t<TextSrc>,
          typename NeedleT = container_type_t<NeedleSrc>, typename ReplaceT = container_type_t<ReplaceSrc>,
          std::enable_if_t<std::is_same_v<TextT, NeedleT> && std::is_same_v<TextT, ReplaceT>, int> = 0>
auto replaced(const TextSrc& t, const NeedleSrc& n, const ReplaceSrc& r, int start = Start, int end = End)
    -> std::basic_string<TextT>
{
    return replace_impl(t, n, r, start, end).text;
}

template <typename TextSrc, typename Predicate, typename ReplaceSrc, typename TextT = container_type_t<TextSrc>,
          typename ReplaceT = container_type_t<ReplaceSrc>, std::enable_if_t<std::is_same_v<TextT, ReplaceT>, int> = 0>
auto replace_if_impl(const TextSrc& t, Predicate pred, const ReplaceSrc& r, int start = Start, int end = End)
    -> ReplaceResult<TextT>
{
    if (sanitize_index(start, t.length()) == End || sanitize_index(end, t.length()) == End)
        return {std::basic_string(t)};
    auto splitted = split_if(t, pred, SplitBehavior::KeepEmpty, start, end);
    return {join(splitted, r), static_cast<int>(splitted.size()) - 1};
}

template <typename TextT, typename Predicate, typename ReplaceSrc, typename ReplaceT = container_type_t<ReplaceSrc>,
          std::enable_if_t<std::is_same_v<TextT, ReplaceT>, int> = 0>
int replace_if(std::basic_string<TextT>& t, Predicate pred, const ReplaceSrc& r, int start = Start, int end = End)
{
    auto result = replace_if_impl(t, pred, r, start, end);
    t = std::move(result.text);
    return result.operations;
}

template <typename TextSrc, typename Predicate, typename ReplaceSrc, typename TextT = container_type_t<TextSrc>,
          typename ReplaceT = container_type_t<ReplaceSrc>, std::enable_if_t<std::is_same_v<TextT, ReplaceT>, int> = 0>
auto replaced_if(const TextSrc& t, Predicate pred, const ReplaceSrc& r, int start = Start, int end = End)
    -> std::basic_string<TextT>
{
    return replace_if_impl(t, pred, r, start, end).text;
}

template <typename TextSrc, typename NeedleSrc, typename ReplaceSrc, typename TextT = container_type_t<TextSrc>,
          typename NeedleT = container_type_t<NeedleSrc>, typename ReplaceT = container_type_t<ReplaceSrc>,
          std::enable_if_t<std::is_same_v<TextT, NeedleT> && std::is_same_v<TextT, ReplaceT>, int> = 0>
auto replace_any_impl(const TextSrc& t, const NeedleSrc& d, const ReplaceSrc& r, int start = Start, int end = End)
    -> ReplaceResult<TextT>
{
    if (sanitize_index(start, t.length()) == End || sanitize_index(end, t.length()) == End)
        return {std::basic_string(t)};
    auto splitted = split_any(t, d, SplitBehavior::KeepEmpty, start, end);
    return {join(splitted, r), static_cast<int>(splitted.size()) - 1};
}

template <typename TextT, typename NeedleSrc, typename ReplaceSrc, typename NeedleT = container_type_t<NeedleSrc>,
          typename ReplaceT = container_type_t<ReplaceSrc>,
          std::enable_if_t<std::is_same_v<TextT, NeedleT> && std::is_same_v<TextT, ReplaceT>, int> = 0>
int replace_any(std::basic_string<TextT>& t, const NeedleSrc& d, const ReplaceSrc& r, int start = Start, int end = End)
{
    auto result = replace_any_impl(t, d, r, start, end);
    t = std::move(result.text);
    return result.operations;
}

template <typename TextSrc, typename NeedleSrc, typename ReplaceSrc, typename TextT = container_type_t<TextSrc>,
          typename NeedleT = container_type_t<NeedleSrc>, typename ReplaceT = container_type_t<ReplaceSrc>,
          std::enable_if_t<std::is_same_v<TextT, NeedleT> && std::is_same_v<TextT, ReplaceT>, int> = 0>
auto replaced_any(const TextSrc& t, const NeedleSrc& d, const ReplaceSrc& r, int start = Start, int end = End)
    -> std::basic_string<TextT>
{
    return replace_any_impl(t, d, r, start, end).text;
}
} // namespace Text
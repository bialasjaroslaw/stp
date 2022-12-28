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

template <typename TextSrc, typename NeedleSrc, typename TextT = container_type_t<TextSrc>,
          typename NeedleT = container_type_t<NeedleSrc>, std::enable_if_t<std::is_same_v<TextT, NeedleT>, int> = 0>
auto remove_impl(const TextSrc& t, const NeedleSrc& n, int start = 0, int end = -1) -> RemoveResult<TextT>
{
    Text txt(t);
    if (sanitize_index(start, txt.length) == npos || sanitize_index(end, txt.length) == npos)
        return {std::basic_string(t)};
    auto splitted = split(t, n, SplitBehavior::KeepEmpty, start, end);
    return {join(splitted, std::basic_string_view<TextT>{}), static_cast<int>(splitted.size()) - 1};
}

template <typename TextT, typename NeedleSrc, typename NeedleT = container_type_t<NeedleSrc>,
          std::enable_if_t<std::is_same_v<TextT, NeedleT>, int> = 0>
int remove(std::basic_string<TextT>& t, const NeedleSrc& n, int start = 0)
{
    auto result = remove_impl(t, n, start);
    t = std::move(result.text);
    return result.operations;
}

template <typename TextSrc, typename NeedleSrc, typename TextT = container_type_t<TextSrc>,
          typename NeedleT = container_type_t<NeedleSrc>, std::enable_if_t<std::is_same_v<TextT, NeedleT>, int> = 0>
[[nodiscard]] auto removed(const TextSrc& t, const NeedleSrc& n, int start = 0) -> std::basic_string<TextT>
{
    return remove_impl(t, n, start).text;
}

template <typename TextT, typename NeedleSrc, typename NeedleT = container_type_t<NeedleSrc>,
          std::enable_if_t<std::is_same_v<TextT, NeedleT>, int> = 0>
int rremove(std::basic_string<TextT>& t, const NeedleSrc& n, int start = 0)
{
    auto result = remove_impl(t, n, 0, -start - 1);
    t = std::move(result.text);
    return result.operations;
}

template <typename TextSrc, typename NeedleSrc, typename TextT = container_type_t<TextSrc>,
          typename NeedleT = container_type_t<NeedleSrc>, std::enable_if_t<std::is_same_v<TextT, NeedleT>, int> = 0>
[[nodiscard]] auto rremoved(const TextSrc& t, const NeedleSrc& n, int start = 0) -> std::basic_string<TextT>
{
    return remove_impl(t, n, 0, -start - 1).text;
}

template <typename TextSrc, typename TextT = container_type_t<TextSrc>, typename Predicate>
auto remove_if_impl(const TextSrc& t, Predicate pred, int start = 0, int end = -1) -> RemoveResult<TextT>
{
    Text txt(t);
    if (sanitize_index(start, txt.length) == npos || sanitize_index(end, txt.length) == npos)
        return {std::basic_string(t)};
    auto splitted = split_if(t, pred, SplitBehavior::KeepEmpty, start, end);
    return {join(splitted, std::basic_string_view<TextT>{}), static_cast<int>(splitted.size()) - 1};
}

template <typename TextT, typename Predicate>
int remove_if(std::basic_string<TextT>& t, Predicate pred, int start = 0)
{
    auto result = remove_if_impl(t, pred, start);
    t = std::move(result.text);
    return result.operations;
}

template <typename TextSrc, typename TextT = container_type_t<TextSrc>, typename Predicate>
[[nodiscard]] auto removed_if(const TextSrc& t, Predicate pred, int start = 0) -> std::basic_string<TextT>
{
    return remove_if_impl(t, pred, start).text;
}

template <typename TextT, typename Predicate>
int rremove_if(std::basic_string<TextT>& t, Predicate pred, int start = 0)
{
    auto result = remove_if_impl(t, pred, 0, -start - 1);
    t = std::move(result.text);
    return result.operations;
}

template <typename TextSrc, typename TextT = container_type_t<TextSrc>, typename Predicate>
[[nodiscard]] auto rremoved_if(const TextSrc& t, Predicate pred, int start = 0) -> std::basic_string<TextT>
{
    return remove_if_impl(t, pred, 0, -start - 1).text;
}

template <typename TextSrc, typename NeedleSrc, typename TextT = container_type_t<TextSrc>,
          typename NeedleT = container_type_t<NeedleSrc>, std::enable_if_t<std::is_same_v<TextT, NeedleT>, int> = 0>
auto remove_any_impl(const TextSrc& t, const NeedleSrc& d, int start = 0, int end = -1) -> RemoveResult<TextT>
{
    Text txt(t);
    if (sanitize_index(start, txt.length) == npos || sanitize_index(end, txt.length) == npos)
        return {std::basic_string(t)};
    auto splitted = split_any(t, d, SplitBehavior::KeepEmpty, start, end);
    return {join(splitted, std::basic_string_view<TextT>{}), static_cast<int>(splitted.size()) - 1};
}

template <typename TextT, typename NeedleSrc, typename NeedleT = container_type_t<NeedleSrc>,
          std::enable_if_t<std::is_same_v<TextT, NeedleT>, int> = 0>
int remove_any(std::basic_string<TextT>& t, const NeedleSrc& d, int start = 0)
{
    auto result = remove_any_impl(t, d, start);
    t = std::move(result.text);
    return result.operations;
}

template <typename TextSrc, typename NeedleSrc, typename TextT = container_type_t<TextSrc>,
          typename NeedleT = container_type_t<NeedleSrc>, std::enable_if_t<std::is_same_v<TextT, NeedleT>, int> = 0>
[[nodiscard]] auto removed_any(const TextSrc& t, const NeedleSrc& d, int start = 0) -> std::basic_string<TextT>
{
    return remove_any_impl(t, d, start).text;
}

template <typename TextT, typename NeedleSrc, typename NeedleT = container_type_t<NeedleSrc>,
          std::enable_if_t<std::is_same_v<TextT, NeedleT>, int> = 0>
int rremove_any(std::basic_string<TextT>& t, const NeedleSrc& d, int start = 0)
{
    auto result = remove_any_impl(t, d, 0, -start - 1);
    t = std::move(result.text);
    return result.operations;
}

template <typename TextSrc, typename NeedleSrc, typename TextT = container_type_t<TextSrc>,
          typename NeedleT = container_type_t<NeedleSrc>, std::enable_if_t<std::is_same_v<TextT, NeedleT>, int> = 0>
[[nodiscard]] auto rremoved_any(const TextSrc& t, const NeedleSrc& d, int start = 0) -> std::basic_string<TextT>
{
    return remove_any_impl(t, d, 0, -start - 1).text;
}

} // namespace Text
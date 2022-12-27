#pragma once

#include "common.hpp"

namespace Text {

template <typename T, typename E = container_type_t<T>>
auto left_view(const T& text, int length)
{
    Text t(text);
    length = std::min(static_cast<int>(t.length), length);
    if (sanitize_index(length, t.length) == npos)
        return std::basic_string_view<E>{};
    return std::basic_string_view<E>(t.ptr, length);
}

template <typename T, typename E = container_type_t<T>>
auto left(const T& text, int length)
{
    return std::basic_string<E>(left_view(text, length));
}

template <typename T, typename E = container_type_t<T>>
auto right_view(const T& text, int length)
{
    Text t(text);
    length = std::min(static_cast<int>(t.length), length);
    if (sanitize_index(length, t.length) == npos)
        return std::basic_string_view<E>{};
    return std::basic_string_view<E>(t.ptr + t.length - length, length);
}

template <typename T, typename E = container_type_t<T>>
auto right(const T& text, int length)
{
    return std::basic_string<E>(right_view(text, length));
}

template <typename T, typename E = container_type_t<T>>
auto mid_view(const T& text, int start, int length = def_length)
{
    Text t(text);
    if (sanitize_index(start, t.length) == npos)
        return std::basic_string_view<E>{};

    length = std::min(static_cast<int>(t.length) - start, length);
    auto end = length < 0 ? length - 1 : start + length - 1;
    if (sanitize_index(end, t.length) == npos)
        return std::basic_string_view<E>("");
    return std::basic_string_view<E>(t.ptr + start, end - start + 1);
}

template <typename T, typename E = container_type_t<T>>
auto mid(const T& text, int start, int length = def_length)
{
    return std::basic_string<E>(mid_view(text, start, length));
}

} // namespace Text
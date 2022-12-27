#pragma once

#include <limits>
#include <set>
#include <string>
#include <string_view>
#include <vector>

template <class CharType>
using StringType = std::basic_string<CharType>;
template <class CharType>
using StringViewType = std::basic_string_view<CharType>;

namespace Text {
constexpr int npos = -1;
constexpr int def_length = std::numeric_limits<int>::max();

template <typename T>
struct remove_all_const : std::remove_const<T>
{};

template <typename T>
struct remove_all_const<T*>
{
    typedef typename remove_all_const<T>::type* type;
};

template <typename T>
struct remove_all_const<T* const>
{
    typedef typename remove_all_const<T>::type* type;
};

template <typename T>
using remove_all_const_t = typename remove_all_const<T>::type;

template <typename E>
struct container_type_detail
{
    using value_type = typename E::value_type;
};

template <>
struct container_type_detail<char*>
{
    using value_type = char;
};

template <>
struct container_type_detail<char>
{
    using value_type = char;
};

template <>
struct container_type_detail<wchar_t*>
{
    using value_type = wchar_t;
};

template <>
struct container_type_detail<wchar_t>
{
    using value_type = wchar_t;
};

template <typename T>
using container_type = container_type_detail<remove_all_const_t<std::decay_t<T>>>;

template <typename T>
using container_type_t = typename container_type_detail<remove_all_const_t<std::decay_t<T>>>::value_type;

template <typename E>
constexpr std::size_t strlen(const E* start)
{
    const auto* end = start;
    for (; *end != 0; ++end)
        ;
    return end - start;
}

template <typename T>
T* strncpy(T* dest, const T* src, size_t n)
{
    for (; n; ++dest, ++src, --n)
        *dest = *src;
    return dest;
}

template <typename T>
constexpr bool are_equal(const T* lhs, const T* rhs, size_t len)
{
    while (len-- > 0)
        if (*lhs++ != *rhs++)
            return false;
    return true;
}

template <typename T>
constexpr T clamp(T value, T low_value, T high_value)
{
    if (value < low_value)
        return low_value;
    if (value > high_value)
        return high_value;
    return value;
}

template <typename T>
constexpr T sanitize_index(T& index, size_t text_size)
{
    if (index < T{0})
        index = index + static_cast<T>(text_size);
    if (text_size == 0 || index != clamp(index, T{0}, static_cast<T>(text_size - 1)))
        return npos;
    return index;
}

template <typename E>
struct Text
{
    using value_type = E;
    const E* ptr = nullptr;
    size_t length = 0;
    explicit constexpr Text(const std::basic_string<E>& str)
    {
        ptr = str.data();
        length = str.size();
    }
    explicit constexpr Text(std::basic_string_view<E> str)
    {
        ptr = str.data();
        length = str.size();
    }
    explicit constexpr Text(const std::vector<E>& str)
    {
        ptr = str.data();
        length = str.size();
    }
    explicit constexpr Text(const E* str)
    {
        ptr = str;
        length = strlen(str);
    }
};

template <typename E>
struct Delimiter
{
    E elem = {};
    const E* ptr = nullptr;
    size_t length = 0;
    explicit constexpr Delimiter(const std::basic_string<E>& str)
    {
        ptr = str.data();
        length = str.size();
    }
    explicit constexpr Delimiter(std::basic_string_view<E> str)
    {
        ptr = str.data();
        length = str.size();
    }
    explicit constexpr Delimiter(const std::vector<E>& str)
    {
        ptr = str.data();
        length = str.size();
    }
    explicit constexpr Delimiter(const E* str)
    {
        ptr = str;
        length = strlen(str);
    }
    explicit constexpr Delimiter(E str)
        : elem(str)
        , ptr(&elem)
        , length(1)
    {}
};

template <typename E>
struct Delimiters
{
    std::set<E> delimiters;
    explicit constexpr Delimiters(const std::basic_string<E>& str)
        : delimiters{str.cbegin(), str.cend()}
    {}
    explicit constexpr Delimiters(std::basic_string_view<E> str)
        : delimiters{str.cbegin(), str.cend()}
    {}
    explicit constexpr Delimiters(const E* str)
        : delimiters{str, str + strlen(str)}
    {}

    constexpr bool contains(E ch) const
    {
        return delimiters.contains(ch);
    }
};
} // namespace Text
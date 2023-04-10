#pragma once

#include <array>
#include <limits>
#include <set>
#include <string>
#include <string_view>
#include <type_traits>
#include <vector>

template <class CharType>
using StringType = std::basic_string<CharType>;
template <class CharType>
using StringViewType = std::basic_string_view<CharType>;

template <typename T>
concept DataContainer = requires(T x) {
                            x.data();
                            x.size();
                            typename std::remove_reference_t<T>::value_type;
                        };

template <class T>
concept CStyleArray = std::is_array_v<T>;

namespace detail {
template <typename T>
struct container_type
{
    using value_type = std::remove_cvref_t<T>;
};

template <typename T>
    requires std::is_pointer_v<T>
struct container_type<T>
{
    using value_type = std::remove_cv_t<std::remove_pointer_t<T>>;
};

template <typename T>
    requires std::is_array_v<T>
struct container_type<T>
{
    using value_type = std::remove_cv_t<std::remove_extent_t<T>>;
};

template <typename T>
    requires requires(T) { typename std::remove_reference_t<T>::value_type; }
struct container_type<T>
{
    using value_type = typename std::remove_reference_t<T>::value_type;
};
} // namespace detail

template <typename T>
using container_type_t = typename detail::container_type<T>::value_type;

namespace Text {
constexpr int Start = 0;
constexpr int End = std::numeric_limits<int>::max();
constexpr int Step = 1;

template <typename T>
auto to_vector(const std::basic_string_view<T>& container)
{
    return std::vector<T>(container.cbegin(), container.cend());
}

template <typename T>
auto to_vector(const std::vector<std::basic_string_view<T>>& container)
{
    std::vector<std::vector<T>> result;
    result.reserve(container.size());
    for (const auto& elem : container)
        result.emplace_back(elem.cbegin(), elem.cend());
    return result;
}

template <typename E>
constexpr std::size_t strlen(const E* start)
{
    const auto* end = start;
    for (; *end != 0; ++end)
        ;
    return static_cast<size_t>(end - start);
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

template <typename T, typename Value = std::remove_cvref_t<T>>
constexpr Value sanitize_index(T&& index, size_t text_size)
{
    if (index < Value{0})
        index = index + static_cast<Value>(text_size);
    else if (index == Text::End)
        index = text_size;

    if (text_size == 0 || index != clamp(index, Value{0}, static_cast<Value>(text_size)))
        return Text::End;
    return index;
}

template <typename E>
struct Text
{
    using value_type = E;
    const E* ptr = nullptr;
    size_t length = 0;
    explicit constexpr Text(const E* str)
    {
        ptr = str;
        length = strlen(str);
    }
    template <DataContainer T>
    explicit constexpr Text(const T& container)
    {
        ptr = container.data();
        length = container.size();
    }
};
template <DataContainer T>
Text(const T& container) -> Text<typename std::remove_reference_t<T>::value_type>;
template <CStyleArray T>
Text(const T& array) -> Text<typename std::remove_pointer_t<std::decay_t<T>>>;


template <typename E>
struct Delimiter
{
    E elem = {};
    const E* ptr = nullptr;
    size_t length = 0;
    explicit constexpr Delimiter(const E* str)
    {
        ptr = str;
        length = strlen(str);
    }
    template <typename N = void>
        requires(!std::is_pointer_v<E>)
    explicit constexpr Delimiter(E str)
        : elem(str)
        , ptr(&elem)
        , length(1)
    {}
    template <DataContainer T>
    explicit constexpr Delimiter(const T& container)
    {
        ptr = container.data();
        length = container.size();
    }
};

template <DataContainer T>
Delimiter(const T& container) -> Delimiter<typename std::remove_reference_t<T>::value_type>;
template <CStyleArray T>
Delimiter(const T& array) -> Delimiter<typename std::remove_pointer_t<std::decay_t<T>>>;

template <typename E>
struct Delimiters
{
    std::set<E> delimiters;
    explicit constexpr Delimiters(const E* str)
        : delimiters{str, str + strlen(str)}
    {}
    template <typename T>
    explicit constexpr Delimiters(const T& container)
        : delimiters{container.cbegin(), container.cend()}
    {}

    constexpr bool contains(E ch) const
    {
        return delimiters.contains(ch);
    }
};

template <DataContainer T>
Delimiters(const T& container) -> Delimiters<typename std::remove_reference_t<T>::value_type>;
} // namespace Text

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

template <typename T>
concept RegularChar = (std::same_as<std::remove_cvref_t<T>, char> || std::same_as<std::remove_cvref_t<T>, wchar_t>);

template <typename T>
inline T caseless(const T& val)
{
    return val;
}

template <RegularChar T>
inline T caseless(const T& val)
{
    return val >= 'A' && val <= 'Z' ? val + ('a' - 'A') : val;
}

template <typename T>
bool caseless_compare(const T& lhs, const T& rhs)
{
    return caseless(lhs) == caseless(rhs);
}

} // namespace detail

template <typename T>
using container_type_t = typename detail::container_type<T>::value_type;

template <class D, class T>
concept CanBeDelimiterOf = std::same_as<container_type_t<D>, container_type_t<T>>;

template <class T, class U>
concept SameDataType = std::same_as<container_type_t<T>, container_type_t<U>>;

namespace Text {
constexpr int Start = 0;
constexpr int End = std::numeric_limits<int>::max();
constexpr int Step = 1;

enum class Case
{
    Sensitive,
    Insensitive,
};

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

template <typename T>
auto to_string_vector(const std::vector<std::basic_string_view<T>>& container)
{
    std::vector<std::basic_string<T>> result;
    result.reserve(container.size());
    for (const auto& elem : container)
        result.emplace_back(std::basic_string<T>(elem.cbegin(), elem.cend()));
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
constexpr bool are_equal(const T* lhs, const T* rhs, size_t len, Case sensitivity)
{
    while (len-- > 0)
        if (sensitivity == Case::Sensitive)
        {
            if (*lhs++ != *rhs++)
                return false;
        }
        else
        {
            if (!detail::caseless_compare<T>(*lhs++, *rhs++))
                return false;
        }
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
        index = static_cast<Value>(text_size);

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
    explicit constexpr Delimiters(const E* str, Case sensitivity = Case::Sensitive)
        : delimiters{init_delimiters(str, str + strlen(str), sensitivity)}
    {}
    template <typename T>
    explicit constexpr Delimiters(const T& container, Case sensitivity = Case::Sensitive)
        : delimiters{init_delimiters(container.cbegin(), container.cend(), sensitivity)}
    {}

    std::set<E> init_delimiters(auto begin, auto end, Case sensitivity)
    {
        if (sensitivity == Case::Sensitive)
            return std::set<E>(begin, end);
        std::set<E> insensitive;
        for (; begin != end; ++begin)
            insensitive.insert(detail::caseless(*begin));
        return insensitive;
    }

    constexpr bool contains(E ch, Case sensitivity = Case::Sensitive) const
    {
        return delimiters.contains(sensitivity == Case::Sensitive ? ch : detail::caseless(ch));
    }
};

template <DataContainer T>
Delimiters(const T& container, Case c) -> Delimiters<typename std::remove_reference_t<T>::value_type>;
} // namespace Text

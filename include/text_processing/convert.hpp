#pragma once

#include "common.hpp"

#include <charconv>
#include <stdexcept>
#include <iostream>

namespace Text {
template <typename R, typename TextSrc>
auto convert(const std::vector<TextSrc>& container)
{
    using namespace std::literals;
    std::vector<R> result;
    result.reserve(container.size());
    for (const auto& elem : container)
    {
        R val{};
        Text t{elem};
        auto [ptr, ec] = std::from_chars(t.ptr, t.ptr + t.length, val);
        if (ec != std::errc())
            throw std::runtime_error("Invalid value passed to convert: "s + std::string(elem));
        std::cout << "Converting " << std::string_view(t.ptr, t.length) << "Got " << val << std::endl;
        result.emplace_back(val);
    }
    return result;
}

template <typename R, typename TextSrc>
auto convert(const TextSrc& element)
{
    using namespace std::literals;
    R result{};
    Text t{element};
    auto [ptr, ec] = std::from_chars(t.ptr, t.ptr + t.length, result);
    if (ec != std::errc())
        throw std::runtime_error("Invalid value passed to convert: "s + std::string(element));
    return result;
}

}
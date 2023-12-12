#pragma once

#include "common.hpp"

#include <charconv>
#include <stdexcept>

namespace Text{

template <typename R, typename T>
auto convert(const std::vector<T>& container)
{
    using namespace std::literals;
    std::vector<R> result;
    result.reserve(container.size());
    for (const auto& elem : container)
    {
    	R val{};
    	auto [ptr, ec] = std::from_chars(elem.data(), elem.data() + elem.size(), val);
        if (ec != std::errc())
        	throw std::runtime_error("Invalid value passed to convert: "s + std::string(elem));
        result.emplace_back(val);
    }
    return result;
}

}
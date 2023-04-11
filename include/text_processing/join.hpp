#pragma once

#include "common.hpp"

namespace Text {
template <typename TextSrc, typename DelimSrc>
    requires CanBeDelimiterOf<DelimSrc, TextSrc>
auto join(const std::vector<TextSrc>& views, DelimSrc d)
{
    std::basic_string<container_type_t<TextSrc>> result;
    if (views.empty())
        return result;

    Delimiter delimiter(d);
    auto size = delimiter.length * (views.size() - 1);
    for (const auto& item : views)
        size += item.length();

    result.resize(size);
    auto ptr = result.data();
    auto end = result.data() + result.length();
    for (const auto& item : views)
    {
        strncpy(ptr, item.data(), item.length());
        ptr += item.length();
        if (ptr == end)
            break;
        strncpy(ptr, delimiter.ptr, delimiter.length);
        ptr += delimiter.length;
    }
    return result;
}
} // namespace Text
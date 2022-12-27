#include "replace.hpp"

#include <gtest/gtest.h>

TEST(Replace, SimpleWithViews)
{
    using namespace std::literals;
    std::string simple("simple string with words");
    auto result = Text::replace(simple, " "sv, "_"sv);
    EXPECT_EQ(result, 3);
    EXPECT_EQ(simple, "simple_string_with_words"s);
}

TEST(Replace, WideView)
{
    using namespace std::literals;
    std::wstring simple(L"simple string with words");
    auto result = Text::replace(simple, L" "sv, L"_"sv);
    EXPECT_EQ(result, 3);
    EXPECT_EQ(simple, L"simple_string_with_words"s);
}

TEST(Replace, SimpleWithViewsAndStart)
{
    using namespace std::literals;
    std::string simple("simple string with words");
    auto result = Text::replace(simple, " "sv, "_"sv, 7);
    EXPECT_EQ(result, 2);
    EXPECT_EQ(simple, "simple string_with_words"s);
}

TEST(ReplaceIf, ValueLargerThan)
{
    using namespace std::literals;
    std::string simple("simple string with words");
    auto result = Text::replace_if(
        simple, [](auto ch) { return ch > 'u'; }, "_"sv, 7);
    EXPECT_EQ(result, 2);
    EXPECT_EQ(simple, "simple string _ith _ords"s);
}

TEST(ReplaceAny, ValueLargerThan)
{
    using namespace std::literals;
    std::string simple("simple string with words");
    auto result = Text::replace_any(simple, "tg"sv, "_"sv);
    EXPECT_EQ(result, 3);
    EXPECT_EQ(simple, "simple s_rin_ wi_h words"s);
}

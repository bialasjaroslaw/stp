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

TEST(Replace, ConstVersion)
{
    using namespace std::literals;
    std::string_view simple("simple string with words");
    auto result = Text::replaced(simple, " "sv, "_"sv);
    EXPECT_EQ(result, "simple_string_with_words");
    EXPECT_EQ(simple, "simple string with words");
}

TEST(Replace, OutOfBoundsStart)
{
    using namespace std::literals;
    std::string simple("simple string with words");
    auto result = Text::replace(simple, " "sv, "_"sv, 100);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(simple, "simple string with words");
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

TEST(ReplaceIf, ConstVersion)
{
    using namespace std::literals;
    std::string_view simple("simple string with words");
    auto result = Text::replaced_if(
        simple, [](auto ch) { return ch > 'u'; }, "_"sv, 7);
    EXPECT_EQ(result, "simple string _ith _ords");
    EXPECT_EQ(simple, "simple string with words");
}

TEST(ReplaceIf, OutOfBoundsStart)
{
    using namespace std::literals;
    std::string simple("simple string with words");
    auto result = Text::replace_if(
        simple, [](auto ch) { return ch > 'u'; }, "_"sv, 100);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(simple, "simple string with words");
}

TEST(ReplaceAny, ValueLargerThan)
{
    using namespace std::literals;
    std::string simple("simple string with words");
    auto result = Text::replace_any(simple, "tg"sv, "_"sv);
    EXPECT_EQ(result, 3);
    EXPECT_EQ(simple, "simple s_rin_ wi_h words"s);
}

TEST(ReplaceAny, ConstVersion)
{
    using namespace std::literals;
    std::string_view simple("simple string with words");
    auto result = Text::replaced_any(simple, "tg"sv, "_"sv);
    EXPECT_EQ(result, "simple s_rin_ wi_h words");
    EXPECT_EQ(simple, "simple string with words");
}

TEST(ReplaceAny, OutOfBoundsStart)
{
    using namespace std::literals;
    std::string simple("simple string with words");
    auto result = Text::replace_any(simple, "tg"sv, "_"sv, 100);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(simple, "simple string with words");
}

#include "remove.hpp"

#include <gtest/gtest.h>

TEST(Remove, SimpleWithViews)
{
    using namespace std::literals;
    std::string simple("simple string with words");
    auto result = Text::remove(simple, " "sv);
    EXPECT_EQ(result, 3);
    EXPECT_EQ(simple, "simplestringwithwords"s);
}

TEST(Remove, ConstVersion)
{
    using namespace std::literals;
    std::string_view simple("simple string with words");
    auto result = Text::removed(simple, " "sv);
    EXPECT_EQ(result, "simplestringwithwords"s);
    EXPECT_EQ(simple, "simple string with words"s);
}

TEST(Remove, WideView)
{
    using namespace std::literals;
    std::wstring simple(L"simple string with words");
    auto result = Text::remove(simple, L" "sv);
    EXPECT_EQ(result, 3);
    EXPECT_EQ(simple, L"simplestringwithwords"s);
}

TEST(Remove, OutOfBoundsStart)
{
    using namespace std::literals;
    std::string simple("simple string with words");
    auto result = Text::remove(simple, " "sv, 100);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(simple, "simple string with words");
}

TEST(Remove, SimpleWithViewsAndText)
{
    using namespace std::literals;
    std::string simple("simple string with words");
    auto result = Text::remove(simple, "string "sv);
    EXPECT_EQ(result, 1);
    EXPECT_EQ(simple, "simple with words"s);
}

TEST(Remove, SimpleWithViewsAndStart)
{
    using namespace std::literals;
    std::string simple("simple string with words");
    auto result = Text::remove(simple, " "sv, 7);
    EXPECT_EQ(result, 2);
    EXPECT_EQ(simple, "simple stringwithwords"s);
}

TEST(Remove, SimpleWithViewsAndStartNegative)
{
    using namespace std::literals;
    std::string simple("simple string with words");
    auto result = Text::remove(simple, " "sv, -7);
    EXPECT_EQ(result, 1);
    EXPECT_EQ(simple, "simple string withwords"s);
}

TEST(Remove, CaseInsensitive)
{
    using namespace std::literals;
    std::string simple("simple String with words");
    auto result = Text::remove(simple, "s"sv, Text::Start, Text::End, Text::Step, Text::Case::Insensitive);
    EXPECT_EQ(result, 3);
    EXPECT_EQ(simple, "imple tring with word"s);
}

TEST(Remove, WithSteps)
{
    using namespace std::literals;
    std::string simple("simple string with words");
    auto result = Text::remove(simple, "s"sv, 1, Text::End, 2);
    EXPECT_EQ(result, 2);
    EXPECT_EQ(simple, "simple tring with word"s);
}

TEST(RemoveIf, ConstVersion)
{
    using namespace std::literals;
    std::string_view simple("simple string with words");
    auto result = Text::removed_if(simple, [](auto ch) { return ch > 'u'; });
    auto expected = "simple string ith ords"s;
    EXPECT_EQ(result, expected);
    EXPECT_EQ(simple, "simple string with words");
}

TEST(RemoveIf, ValueLargerThan)
{
    using namespace std::literals;
    std::string simple("simple string with words");
    auto result = Text::remove_if(simple, [](auto ch) { return ch > 'u'; });
    auto expected = "simple string ith ords"s;
    EXPECT_EQ(result, 2);
    EXPECT_EQ(simple, expected);
}

TEST(RemoveIf, OutOfBoundsStart)
{
    using namespace std::literals;
    std::string simple("simple string with words");
    auto result = Text::remove_if(simple, [](auto ch) { return ch > 'u'; }, 100);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(simple, "simple string with words");
}

TEST(RemoveAny, SimpleWithViews)
{
    using namespace std::literals;
    std::string simple("simple string with words");
    auto result = Text::remove_any(simple, "tg"sv);
    EXPECT_EQ(result, 3);
    EXPECT_EQ(simple, "simple srin wih words"s);
}

TEST(RemoveAny, SimpleWithViewsAndStart)
{
    using namespace std::literals;
    std::string simple("simple string with words");
    auto result = Text::remove_any(simple, "tg"sv, 9);
    EXPECT_EQ(result, 2);
    EXPECT_EQ(simple, "simple strin wih words"s);
}

TEST(RemoveAny, OutOfBoundsStart)
{
    using namespace std::literals;
    std::string simple("simple string with words");
    auto result = Text::remove_any(simple, "tg"sv, 100);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(simple, "simple string with words");
}

TEST(RemoveAny, SimpleWithViewsAndStartNegative)
{
    using namespace std::literals;
    std::string simple("simple string with words");
    auto result = Text::remove_any(simple, "tg"sv, -9);
    EXPECT_EQ(result, 1);
    EXPECT_EQ(simple, "simple string wih words"s);
}

TEST(RemoveAny, ConstVersion)
{
    using namespace std::literals;
    std::string_view simple("simple string with words");
    auto result = Text::removed_any(simple, "tg"sv);
    EXPECT_EQ(result, "simple srin wih words"s);
    EXPECT_EQ(simple, "simple string with words");
}

TEST(RemoveAny, CaseInsensitive)
{
    using namespace std::literals;
    std::string simple("simple String With words");
    auto result = Text::remove_any(simple, "Sw"sv, Text::Start, Text::End, Text::Step, Text::Case::Insensitive);
    EXPECT_EQ(result, 5);
    EXPECT_EQ(simple, "imple tring ith ord");
}


//Add steps for replace/split
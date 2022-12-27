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

TEST(Remove, WideView)
{
    using namespace std::literals;
    std::wstring simple(L"simple string with words");
    auto result = Text::remove(simple, L" "sv);
    EXPECT_EQ(result, 3);
    EXPECT_EQ(simple, L"simplestringwithwords"s);
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

TEST(RemoveIf, ValueLargerThan)
{
    using namespace std::literals;
    std::string simple("simple string with words");
    auto result = Text::remove_if(simple, [](auto ch) { return ch > 'u'; });
    auto expected = "simple string ith ords"s;
    EXPECT_EQ(result, 2);
    EXPECT_EQ(simple, expected);
}

TEST(RRemove, SimpleWithViews)
{
    using namespace std::literals;
    std::string simple("simple string with words");
    auto result = Text::rremove(simple, " "sv);
    EXPECT_EQ(result, 3);
    EXPECT_EQ(simple, "simplestringwithwords"s);
}

TEST(RRemove, SimpleWithViewsAndStart)
{
    using namespace std::literals;
    std::string simple("simple string with words");
    auto result = Text::rremove(simple, " "sv, 7);
    EXPECT_EQ(result, 2);
    EXPECT_EQ(simple, "simplestringwith words"s);
}

TEST(RRemove, SimpleWithViewsAndStartNegative)
{
    using namespace std::literals;
    std::string simple("simple string with words");
    auto result = Text::rremove(simple, " "sv, -7);
    EXPECT_EQ(result, 1);
    EXPECT_EQ(simple, "simplestring with words"s);
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

TEST(RemoveAny, SimpleWithViewsAndStartNegative)
{
    using namespace std::literals;
    std::string simple("simple string with words");
    auto result = Text::remove_any(simple, "tg"sv, -9);
    EXPECT_EQ(result, 1);
    EXPECT_EQ(simple, "simple string wih words"s);
}

TEST(RRemoveAny, SimpleWithViews)
{
    using namespace std::literals;
    std::string simple("simple string with words");
    auto result = Text::rremove_any(simple, "tg"sv);
    EXPECT_EQ(result, 3);
    EXPECT_EQ(simple, "simple srin wih words"s);
}

TEST(RRemoveAny, SimpleWithViewsAndStart)
{
    using namespace std::literals;
    std::string simple("simple string with words");
    auto result = Text::rremove_any(simple, "tg"sv, 9);
    EXPECT_EQ(result, 2);
    EXPECT_EQ(simple, "simple srin with words"s);
}

TEST(RRemoveAny, SimpleWithViewsAndStartNegative)
{
    using namespace std::literals;
    std::string simple("simple string with words");
    auto result = Text::rremove_any(simple, "tg"sv, -9);
    EXPECT_EQ(result, 1);
    EXPECT_EQ(simple, "simple sring with words"s);
}
